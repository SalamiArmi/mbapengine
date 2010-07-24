#ifndef _MAP_HEADER_
#define _MAP_HEADER_

//#include "stdafx.h"

namespace Argon
{
	template < typename _Key, typename _Data >
	class Map
	{
		template < typename _Key, typename _Data >
		class ContainerT
		{
			friend Map <_Key, _Data>;
		public:
			inline const bool isValid() const
			{
				return !(!parent && colour);
			}

			void operator = (const ContainerT &copy)
			{
				key = copy.key;
				children[0] = copy.children[0];
				children[1] = copy.children[1];
				data = copy.data;
				parent = copy.parent;
				colour = copy.colour;
			}

			inline const bool operator == (const ContainerT &copy) const
			{
				return key == copy.key;
			}

			inline const bool operator != (const ContainerT &copy) const
			{
				return key != copy.key;
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

			void increment()
			{
				ContainerT *iterator = this;

				if (iterator->children[1])
				{
					iterator = iterator->children[1];
				}
				else if (iterator->parent->children[0])
				{
					_Key comparisonValue = iterator->data;
					do
					{
						iterator = iterator->parent;
					} while (iterator->data < comparisonValue);
				}
				else
				{
					do
					{
						iterator = iterator->parent;
					} while (!iterator->children[1]);
				}

				while (iterator->children[0])
				{
					iterator = iterator->children[0];
				}

				*this = *iterator;
			}

			void deincrement()
			{
				ContainerT *iterator = this;

				if (iterator->children[0])
				{
					iterator = iterator->children[0];
				}
				else if (iterator->parent->children[1])
				{
					_Key comparisonValue = iterator->data;
					do
					{
						iterator = iterator->parent;
					} while (iterator->data < comparisonValue);
				}
				else
				{
					do
					{
						iterator = iterator->parent;
					} while (!iterator->children[0]);
				}

				while (iterator->children[1])
				{
					iterator = iterator->children[1];
				}

				*this = *iterator;
			}

		public:
			_Key key;
			_Data data;

		protected:
			ContainerT *children[2];
			ContainerT *parent;
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

		void insert(_Key newKey, _Data newData)
		{
			container
				*__restrict newContainer = new container(),
				*__restrict iterator = m_root;

			newContainer->data = newData;
			newContainer->key = newKey;
			newContainer->colour = true;
			newContainer->children[0] = 0;
			newContainer->children[1] = 0;

			if (!iterator)
			{
				iterator = newContainer;
				iterator->parent = 0;
			}
			else
			{
				while (iterator->children[newContainer->key > iterator->key])
				{
					iterator = iterator->children[newContainer->key > iterator->key];
				}

				iterator->children[newContainer->key > iterator->key] = newContainer;
				iterator->children[newContainer->key > iterator->key]->parent = iterator;
			}

			insertHelper(iterator);
		}

		void erase(container *__restrict erasableNode)
		{
			// Are our pointers different?
			if (erasableNode->children[0] != erasableNode->children[1])
			{
				container *__restrict child = erasableNode->children[!erasableNode->children[0]];

				if (erasableNode->children[0] && erasableNode->children[1])
				{
					// Both pointers are valid
					while (child->children[1])
					{
						child = child->children[1];
					}

					erasableNode->key = child->key;
					erasableNode->data = child->data;
					erasableNode = child;
				}
				else
				{
					// Only one pointer is valid
					child->parent = erasableNode->parent;
					if (child->parent)
					{
						child->parent->children[erasableNode->parent->children[1] == erasableNode] = child;
					}
					else
					{
						m_root = child;
					}

					if (erasableNode->colour == false)
					{
						child->colour ? child->colour = false : eraseHelper(child);
					}
				}
			}
			else
			{
				if (erasableNode->parent)
				{
					erasableNode->parent->children[erasableNode->parent->children[1] == erasableNode] = 0;
				}
				else
				{
					m_root = 0;
				}
			}

			delete erasableNode;
		}

		container *find(_Key request) const
		{
			container *__restrict iterator = m_root;
			while (request != iterator->key)
			{
				iterator = iterator->children[request > iterator->key];
			}
			return iterator;
		}

		container *findLower(_Key request) const
		{
			container *__restrict iterator = m_root;
			while (request != iterator->key && iterator->children[request > iterator->key])
			{
				iterator = iterator->children[request > iterator->key];
			}
			if (iterator->key > request)
			{
				--(*ret);
			}
			return ret;
		}

		container *findHigher(_Key request) const
		{
			container *__restrict iterator = m_root;
			while (request != iterator->key && iterator->children[request > iterator->key])
			{
				iterator = iterator->children[request > iterator->key];
			}
			if (iterator->key < request)
			{
				--(*ret);
			}
			return ret;
		}

		container *first() const
		{
			container *__restrict iterator = m_root;
			while (iterator->children[0])
			{
				iterator = iterator->children[0];
			}
			return iterator;
		}

		container *last() const
		{
			container *__restrict iterator = m_root;
			while (iterator->children[1])
			{
				iterator = iterator->children[1];
			}
			return iterator;
		}

		const bool empty() const
		{
			return !m_root;
		}

	private:
		inline void insertHelper(container *__restrict target)
		{
			while (true)
			{
				if (!target->parent)
				{
					target->colour = false;
					m_root = target;
				}
				else if (target->parent->colour)
				{
					container
						*__restrict grandparent = target && target->parent ? target->parent->parent : 0,
						*__restrict uncle = grandparent ? grandparent->children[target->parent == grandparent->children[0]] : 0;

					if (uncle && uncle->colour)
					{
						target->parent->colour = uncle->colour = false;
						grandparent->colour = true;
						target = grandparent;
						continue;
					}
					else
					{
						if (target == target->parent->children[1] && target->parent == grandparent->children[0])
						{
							rotateTree(target, false);
							target = target->children[0];
						}
						else if (target == target->parent->children[0] && target->parent == grandparent->children[1])
						{
							rotateTree(target, true);
							target = target->children[1];
						}

						target->parent->colour = false;
						grandparent->colour = true;

						rotateTree(target->parent, target == target->parent->children[0] && target->parent == grandparent->children[0]);

						while (m_root->parent)
						{
							m_root = m_root->parent;
						}
					}
				}
				break;
			}
		}

		inline void eraseHelper(container *__restrict target)
		{
			while (true)
			{
				if (target->parent)
				{
					container *__restrict sibling = target->parent->children[target == target->parent->children[0]];

					if (sibling->colour == true)
					{
						target->parent->colour = true;
						sibling->colour = false;
						rotateTree(target, target == target->parent->children[0]);
					}
					else if ((sibling->colour == false) && (sibling->children[0]->colour == false) && (sibling->children[1]->colour == false))
					{
						sibling->colour = true;
						if (target->parent->colour)
						{
							target->parent->colour = false;
						}
						else
						{
							target = target->parent;
							continue;
						}
					}
					else
					{
						sibling->colour = target->parent->colour;
						target->parent->colour = false;

						sibling->children[target == target->parent->children[0]]->colour = false;
						rotateTree(target, target == target->parent->children[0]);
					}

					while (m_root->parent)
					{
						m_root = m_root->parent;
					}
				}
				break;
			}
		}

		static inline void rotateTree(container *__restrict target, const bool direction)
		{
			container
				*__restrict parent = target->parent,
				*__restrict grandparent = target->parent->parent,
				*__restrict middleChild = target->children[direction];

			parent->children[!direction] = middleChild;
			if (middleChild)
			{
				middleChild->parent = parent;
			}

			target->parent = grandparent;
			if (grandparent)
			{
				grandparent->children[grandparent->children[1] == parent] = target;
			}

			target->children[direction] = parent;
			parent->parent = target;
		}

		container *m_root;
	};
}

#endif //_MAP_HEADER_