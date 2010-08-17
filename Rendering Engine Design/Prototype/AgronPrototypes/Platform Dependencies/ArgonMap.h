////////////////////////////////////////////////////////////////
//
//	ArgonMap.h : Argon Map Container
//
//	Copyright ©2010 Argon. All rights reserved.
//	Removal of this copyright notice is not permitted.
//
///////////////////////////////////////////////////////////////

#ifndef _MAP_HEADER_
#define _MAP_HEADER_

namespace Argon
{
	template < typename _Type >
	class Less
	{
		bool operator()(const _Type &left, const _Type &right) const
		{
			return (left < right);
		}
	};

	template < typename _Key, typename _Data, typename _Compare = Less<_Key> >
	class Map
	{
		template < typename _Key, typename _Data >
		class ContainerT
		{
			friend Map <_Key, _Data>;

		public:
			inline const bool IsValid() const
			{
				return !(!m_Parent && colour);
			}

			void operator = (const ContainerT &copy)
			{
				m_Key = copy.m_Key;
				m_Children[0] = copy.m_Children[0];
				m_Children[1] = copy.m_Children[1];
				m_Data = copy.m_Data;
				m_Parent = copy.m_Parent;
				colour = copy.colour;
			}

			inline const bool operator == (const ContainerT &copy) const
			{
				return m_Key == copy.m_Key;
			}

			inline const bool operator != (const ContainerT &copy) const
			{
				return m_Key != copy.m_Key;
			}

			inline void operator ++ ()
			{
				increment();
			}

			inline void operator ++ (int)
			{
				increment();
			}

			inline void operator -- ()
			{
				deincrement();
			}

			inline void operator -- (int)
			{
				deincrement();
			}

		protected:
			ContainerT()
			{
			}

			void Increment()
			{
				ContainerT *iterator = this;

				if (iterator->m_Children[1])
				{
					iterator = iterator->m_Children[1];
				}
				else if (iterator->m_Parent->m_Children[0])
				{
					_Key comparisonValue = iterator->m_Data;
					do
					{
						iterator = iterator->m_Parent;
					} while (iterator->m_Data < comparisonValue);
				}
				else
				{
					do
					{
						iterator = iterator->m_Parent;
					} while (!iterator->m_Children[1]);
				}

				while (iterator->m_Children[0])
				{
					iterator = iterator->m_Children[0];
				}

				*this = *iterator;
			}

			void Deincrement()
			{
				ContainerT *iterator = this;

				if (iterator->m_Children[0])
				{
					iterator = iterator->m_Children[0];
				}
				else if (iterator->m_Parent->m_Children[1])
				{
					_Key comparisonValue = iterator->m_Data;
					do
					{
						iterator = iterator->m_Parent;
					} while (iterator->m_Data < comparisonValue);
				}
				else
				{
					do
					{
						iterator = iterator->m_Parent;
					} while (!iterator->m_Children[0]);
				}

				while (iterator->m_Children[1])
				{
					iterator = iterator->m_Children[1];
				}

				*this = *iterator;
			}

		public:
			_Key m_Key;
			_Data m_Data;

		protected:
			ContainerT *m_Children[2];
			ContainerT *m_Parent;
			bool colour;
		};

	public:
		typedef ContainerT<_Key, _Data> container;

		inline Map() : m_root(0)
		{
		}

		inline ~Map()
		{
		}

		void Insert(_Key newKey, _Data newData)
		{
			container
				*__restrict newContainer = new container(),
				*__restrict iterator = m_root;

			newContainer->m_Data = newData;
			newContainer->m_Key = newKey;
			newContainer->colour = true;
			newContainer->m_Children[0] = 0;
			newContainer->m_Children[1] = 0;

			if (!iterator)
			{
				iterator = newContainer;
				iterator->m_Parent = 0;
			}
			else
			{
				while (iterator->m_Children[newContainer->m_Key > iterator->m_Key])
				{
					iterator = iterator->m_Children[newContainer->m_Key > iterator->m_Key];
				}

				iterator->m_Children[newContainer->m_Key > iterator->m_Key] = newContainer;
				iterator->m_Children[newContainer->m_Key > iterator->m_Key]->m_Parent = iterator;
			}

			InsertHelper(iterator);
		}

		void Erase(container *__restrict erasableNode)
		{
			// Are our pointers different?
			if (erasableNode->m_Children[0] != erasableNode->m_Children[1])
			{
				container *__restrict child = erasableNode->m_Children[!erasableNode->m_Children[0]];

				if (erasableNode->m_Children[0] && erasableNode->m_Children[1])
				{
					// Both pointers are valid
					while (child->m_Children[1])
					{
						child = child->m_Children[1];
					}

					erasableNode->m_Key = child->m_Key;
					erasableNode->m_Data = child->m_Data;
					erasableNode = child;
				}
				else
				{
					// Only one pointer is valid
					child->m_Parent = erasableNode->m_Parent;
					if (child->m_Parent)
					{
						child->m_Parent->m_Children[erasableNode->m_Parent->m_Children[1] == erasableNode] = child;
					}
					else
					{
						m_root = child;
					}

					if (erasableNode->colour == false)
					{
						child->colour ? child->colour = false : EraseHelper(child);
					}
				}
			}
			else
			{
				if (erasableNode->m_Parent)
				{
					erasableNode->m_Parent->m_Children[erasableNode->m_Parent->m_Children[1] == erasableNode] = 0;
				}
				else
				{
					m_root = 0;
				}
			}

			delete erasableNode;
		}

		container *Find(_Key request) const
		{
			container *__restrict iterator = m_root;
			while (request != iterator->m_Key)
			{
				iterator = iterator->m_Children[request > iterator->m_Key];
			}
			return iterator;
		}

		container *FindLower(_Key request) const
		{
			container *__restrict iterator = m_root;
			while (request != iterator->m_Key && iterator->m_Children[request > iterator->m_Key])
			{
				iterator = iterator->m_Children[request > iterator->m_Key];
			}
			if (iterator->m_Key > request)
			{
				--(*iterator);
			}
			return iterator;
		}

		container *FindHigher(_Key request) const
		{
			container *__restrict iterator = m_root;
			while (request != iterator->m_Key && iterator->m_Children[request > iterator->m_Key])
			{
				iterator = iterator->m_Children[request > iterator->m_Key];
			}
			if (iterator->m_Key < request)
			{
				--(*iterator);
			}
			return iterator;
		}

		container *First() const
		{
			container *__restrict iterator = m_root;
			while (iterator->m_Children[0])
			{
				iterator = iterator->m_Children[0];
			}
			return iterator;
		}

		container *Last() const
		{
			container *__restrict iterator = m_root;
			while (iterator->m_Children[1])
			{
				iterator = iterator->m_Children[1];
			}
			return iterator;
		}

		const bool IsEmpty() const
		{
			return !m_root;
		}

	private:
		inline void InsertHelper(container *__restrict target)
		{
			while (true)
			{
				if (!target->m_Parent)
				{
					target->colour = false;
					m_root = target;
				}
				else if (target->m_Parent->colour)
				{
					container
						*__restrict grandparent = target && target->m_Parent ? target->m_Parent->m_Parent : 0,
						*__restrict uncle = grandparent ? grandparent->m_Children[target->m_Parent == grandparent->m_Children[0]] : 0;

					if (uncle && uncle->colour)
					{
						target->m_Parent->colour = uncle->colour = false;
						grandparent->colour = true;
						target = grandparent;
						continue;
					}
					else
					{
						if (target == target->m_Parent->m_Children[1] && target->m_Parent == grandparent->m_Children[0])
						{
							RotateTree(target, false);
							target = target->m_Children[0];
						}
						else if (target == target->m_Parent->m_Children[0] && target->m_Parent == grandparent->m_Children[1])
						{
							RotateTree(target, true);
							target = target->m_Children[1];
						}

						target->m_Parent->colour = false;
						grandparent->colour = true;

						RotateTree(target->m_Parent, target == target->m_Parent->m_Children[0] && target->m_Parent == grandparent->m_Children[0]);

						while (m_root->m_Parent)
						{
							m_root = m_root->m_Parent;
						}
					}
				}
				break;
			}
		}

		inline void EraseHelper(container *__restrict target)
		{
			while (true)
			{
				if (target->m_Parent)
				{
					container *__restrict sibling = target->m_Parent->m_Children[target == target->m_Parent->m_Children[0]];

					if (sibling->colour == true)
					{
						target->m_Parent->colour = true;
						sibling->colour = false;
						rotateTree(target, target == target->m_Parent->m_Children[0]);
					}
					else if ((sibling->colour == false) && (sibling->m_Children[0]->colour == false) && (sibling->m_Children[1]->colour == false))
					{
						sibling->colour = true;
						if (target->m_Parent->colour)
						{
							target->m_Parent->colour = false;
						}
						else
						{
							target = target->m_Parent;
							continue;
						}
					}
					else
					{
						sibling->colour = target->m_Parent->colour;
						target->m_Parent->colour = false;

						sibling->m_Children[target == target->m_Parent->m_Children[0]]->colour = false;
						rotateTree(target, target == target->m_Parent->m_Children[0]);
					}

					while (m_root->m_Parent)
					{
						m_root = m_root->m_Parent;
					}
				}
				break;
			}
		}

		static inline void RotateTree(container *__restrict target, const bool direction)
		{
			container
				*__restrict m_Parent = target->m_Parent,
				*__restrict grandparent = target->m_Parent->m_Parent,
				*__restrict middleChild = target->m_Children[direction];

			m_Parent->m_Children[!direction] = middleChild;
			if (middleChild)
			{
				middleChild->m_Parent = m_Parent;
			}

			target->m_Parent = grandparent;
			if (grandparent)
			{
				grandparent->m_Children[grandparent->m_Children[1] == m_Parent] = target;
			}

			target->m_Children[direction] = m_Parent;
			m_Parent->m_Parent = target;
		}

		container *m_root;
	};
}

#endif //_MAP_HEADER_