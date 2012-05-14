template<typename T> 
inline void GeometryResource::ParseIndexData(GeometryParser* Parser, char* Data)
{
	T* IndexData = (T*)Data;
	for(ulong Index = 0; Index < m_FaceCount; ++Index)
	{
		IndexData[0] = (T)Parser->GetFaceIndex(Index, 0);
		IndexData[1] = (T)Parser->GetFaceIndex(Index, 1);
		IndexData[2] = (T)Parser->GetFaceIndex(Index, 2);

		IndexData += 3;
	}
}