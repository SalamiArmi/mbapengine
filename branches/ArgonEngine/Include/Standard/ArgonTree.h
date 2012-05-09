#ifndef _ARGONTREE_HEADER_
#define _ARGONTREE_HEADER_

#include "ArgonBaseTree.h"

namespace Argon
{
	template <class Type> class Tree : public TreeBase
	{
	public:		
		~Tree() {}

		Type* Previous() const
		{
			return (static_cast<Type* >(static_cast<Tree<Type>* >(TreeBase::Previous())));
		}

		Type* Next() const
		{
			return (static_cast<Type* >(static_cast<Tree<Type>* >(TreeBase::Next())));
		}

		Type* GetSuperNode() const
		{
			return (static_cast<Type* >(static_cast<Tree<Type>* >(TreeBase::GetSuperNode())));
		}

		Type* GetFirstSubnode() const
		{
			return (static_cast<Type* >(static_cast<Tree<Type>* >(TreeBase::GetFirstSubnode())));
		}

		Type* GetLastSubnode() const
		{
			return (static_cast<Type* >(static_cast<Tree<Type>* >(TreeBase::GetLastSubnode())));
		}

		Type* GetRootNode()
		{
			return (static_cast<Type* >(static_cast<Tree<Type>* >(TreeBase::GetRootNode())));
		}

		const Type* GetRootNode() const
		{
			return (static_cast<const Type* >(static_cast<const Tree<Type>* >(TreeBase::GetRootNode())));
		}

		bool Descendant(const Tree<Type>* Node) const
		{
			return (TreeBase::Descendant(Node));
		}

		Type* GetLeftMostNode()
		{
			return (static_cast<Type* >(static_cast<Tree<Type>* >(TreeBase::GetLeftMostNode())));
		}

		const Type* GetLeftMostNode() const
		{
			return (static_cast<const Type* >(static_cast<const Tree<Type>* >(TreeBase::GetLeftMostNode())));
		}

		Type* GetRightMostNode()
		{
			return (static_cast<Type* >(static_cast<Tree<Type>* >(TreeBase::GetRightMostNode())));
		}

		const Type* GetRightmostNode() const
		{
			return (static_cast<const Type* >(static_cast<const Tree<Type>* >(TreeBase::GetRightMostNode())));
		}

		Type* GetNextNode(const Tree<Type>* Node) const
		{
			return (static_cast<Type* >(static_cast<Tree<Type>* >(TreeBase::GetNextNode(Node))));
		}

		Type* GetPreviousNode(const Tree<Type>* Node)
		{
			return (static_cast<Type* >(static_cast<Tree<Type>* >(TreeBase::GetPreviousNode(Node))));
		}

		const Type* GetPreviousNode(const Tree<Type>* Node) const
		{
			return (static_cast<const Type* >(static_cast<const Tree<Type>* >(TreeBase::GetPreviousNode(Node))));
		}

		Type* GetNextLevelNode(const Tree<Type>* Node) const
		{
			return (static_cast<Type* >(static_cast<Tree<Type>* >(TreeBase::GetNextLevelNode(Node))));
		}

		void MoveSubtree(Tree<Type>* Super)
		{
			TreeBase::MoveSubtree(Super);
		}

		virtual void AddSubnode(Tree<Type>* Node)
		{
			TreeBase::AddSubnode(Node);
		}

		virtual void AddFirstSubnode(Tree<Type>* Node)
		{
			TreeBase::AddFirstSubnode(Node);
		}

		virtual void AddSubnodeBefore(Tree<Type>* Node, Tree<Type>* Before)
		{
			TreeBase::AddSubnodeBefore(Node, Before);
		}

		virtual void AddSubnodeAfter(Tree<Type>* Node, Tree<Type>* After)
		{
			TreeBase::AddSubnodeAfter(Node, After);
		}

		virtual void RemoveSubnode(Tree<Type>* Node)
		{
			TreeBase::RemoveSubnode(Node);
		}

	}; //Class
} //Namespace

#endif //_ARGONTREE_HEADER_