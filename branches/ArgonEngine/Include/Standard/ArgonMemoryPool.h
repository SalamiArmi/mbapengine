#ifndef _ARGONMEMORYPOOL_HEADER_
#define _ARGONMEMORYPOOL_HEADER_

namespace Argon
{
	class MemoryPool2
	{
	public:
		MemoryPool2(size_t BlockSize) 
			: m_BlockSize(BlockSize),
			m_DataBlock(NULL),
			m_FreeBlockLocations(NULL),
			m_CurrentBlockCount(0),
			m_FreeBlockCount(0),
			m_AllBlockLocations(NULL)
		{
			AllocateDataBlock(1000);
		}

		~MemoryPool2()
		{
			delete[] m_DataBlock;
			delete[] m_FreeBlockLocations;
			delete[] m_AllBlockLocations;
		}

		void* GetDataBlock(size_t DataSize)
		{
			size_t RequiredBlocks = (size_t)ceil((float)DataSize / (float)m_BlockSize);

			if(m_FreeBlockCount == 0 || m_FreeBlockCount < RequiredBlocks)
			{
				AllocateDataBlock(m_CurrentBlockCount * 2 * m_BlockSize); //Double the memory Usage
			}

			if(RequiredBlocks > 0)
			{
				assert(m_FreeBlockLocations[0] <= m_CurrentBlockCount);

				//Get the First available Block
				size_t FirstFreeBlock = m_FreeBlockLocations[0];
				size_t Offset = m_AllBlockLocations[FirstFreeBlock];
				m_FreeBlockCount -= RequiredBlocks;

				//Remove the Amount of required blocks
				Erase(m_FreeBlockLocations + 0, RequiredBlocks);

				return &m_DataBlock[Offset];
			}
			return NULL;
		}

		void* ReleaseDataBlock(void*& DataBlock, size_t DataBlockSize)
		{
			for(size_t Index = 0; Index < m_CurrentBlockCount; ++Index)
			{
				//Get the Data
				size_t Offset = m_AllBlockLocations[Index];

				char* CompareDataBlock = &m_DataBlock[Offset];

				//Compare the Data
				if(memcmp(DataBlock, CompareDataBlock, DataBlockSize) == 0)
				{
					memset(CompareDataBlock, -51, DataBlockSize);

					//Add back the freed blocks
					size_t RequiredBlocks = (size_t)ceil((float)DataBlockSize / (float)m_BlockSize);
					Add(Index, RequiredBlocks, m_FreeBlockCount, (m_FreeBlockCount + RequiredBlocks));
					m_FreeBlockCount += RequiredBlocks;

					DataBlock = NULL;

					return NULL;
				}
			}
			return NULL;
		}

	protected:

		void AllocateDataBlock(size_t AllocationSize)
		{
			size_t BlockCount = (size_t)ceil((float)AllocationSize / (float)m_BlockSize);
			size_t AllocatedBlocks = 0;

			if(m_CurrentBlockCount == 0)
			{
				AllocatedBlocks = BlockCount;
			}
			else
			{
				AllocatedBlocks = BlockCount - m_CurrentBlockCount;
			}


			char* NewDataBlock = NULL;
			if(m_DataBlock == NULL)
			{
				//Create a new Block of data
				NewDataBlock = new char[AllocationSize];
			}
			else
			{
				NewDataBlock = new (m_DataBlock) char[AllocationSize];
			}

			//if any old data exists move across
			if(m_DataBlock != NULL)
			{
				//Copy the old data
				memmove(NewDataBlock, m_DataBlock, m_Size);
			}

			//Create a new block locations
			size_t* BlockLocations = new size_t[BlockCount - m_FreeBlockCount];
			size_t* BlockSizes = new size_t[BlockCount];

			if(m_FreeBlockLocations != NULL)
			{
				//Copy all old block locations across
				memcpy(BlockLocations, m_FreeBlockLocations, (BlockCount - m_FreeBlockCount) * sizeof(size_t));
				delete[] m_FreeBlockLocations;
			}

			if(m_AllBlockLocations != NULL)
			{
				//Copy all old block sizes across
				memcpy(BlockSizes, m_AllBlockLocations, m_CurrentBlockCount * sizeof(size_t));
				delete[] m_AllBlockLocations;
			}

			for(size_t Index = m_FreeBlockCount; Index < (BlockCount - m_CurrentBlockCount); ++Index)
			{
				assert(Index < BlockCount - m_FreeBlockCount);
				BlockLocations[Index] = m_CurrentBlockCount + Index;
			}

			for(size_t Index = m_CurrentBlockCount; Index < BlockCount; ++Index)
			{
				BlockSizes[Index] = m_BlockSize * Index;
			}

			m_CurrentBlockCount = BlockCount;
			m_FreeBlockLocations = BlockLocations;
			m_AllBlockLocations = BlockSizes;
			m_DataBlock = NewDataBlock;
			m_Size = AllocationSize;
			m_FreeBlockCount = AllocatedBlocks + m_FreeBlockCount;
		}

		void DeAllocateDataBlock()
		{
			//Free the Data Block
			delete[] m_DataBlock;
			delete[] m_FreeBlockLocations;

			//Set both to null
			m_DataBlock = NULL;
			m_FreeBlockLocations = NULL;
		}

		void Erase(size_t* Begin, size_t Count)
		{
			if(m_FreeBlockCount == 0)
			{
				delete[] m_FreeBlockLocations;
				m_FreeBlockLocations = NULL;
				return;
			}

			//Copy the block
			size_t* Data = new size_t[m_FreeBlockCount];
			size_t* OldData = m_FreeBlockLocations;

			size_t DataIndex = 0, OldDataIndex = 0;

			for(size_t Index = 0; Index < m_FreeBlockCount + Count; Index) //Copy the old data into the new buffer
			{
				if(memcmp(OldData + OldDataIndex, Begin, Count * sizeof(size_t)) != 0)
				{
					assert(DataIndex<m_FreeBlockCount);
					Data[DataIndex] = OldData[OldDataIndex]; //Copy Data across
					++DataIndex;
					++OldDataIndex;
					++Index;
				}
				else
				{
					Index += Count;
					OldDataIndex += Count;
				}
			}

			//delete[] m_FreeBlockLocations; //Delete the old data
			m_FreeBlockLocations = Data;
		}

		void Add(size_t Start, size_t Count, size_t CurrentBlocks, size_t NewBlockCount)
		{
			size_t* Data = new size_t[NewBlockCount];
			size_t* OldData = m_FreeBlockLocations;

			memcpy(Data, OldData, CurrentBlocks);

			for(size_t Index = 0; Index < Count; ++Index) //Copy the old data into the new buffer
			{
				Data[Start + Index] = Index;
			}

			delete[] m_FreeBlockLocations; //Delete the old data
			m_FreeBlockLocations = Data;
		}

		__forceinline void Defrag()
		{
		}

	private:

		size_t	m_Size;
		char*	m_DataBlock;
		size_t*	m_FreeBlockLocations;
		size_t*	m_AllBlockLocations;
		size_t	m_BlockSize;
		size_t	m_CurrentBlockCount;
		size_t	m_FreeBlockCount;
	};
} //Namespace

#endif //_ARGONMEMORYPOOL_HEADER_