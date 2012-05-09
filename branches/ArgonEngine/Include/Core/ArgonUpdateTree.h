#ifndef _ARGONUPDATETREE_HEADER_
#define _ARGONUPDATETREE_HEADER_

#include <Standard/ArgonTree.h>

namespace Argon
{
	template <class NodeType> class UpdatableTree : public Tree<NodeType>
	{	
	public:
		~UpdatableTree()
		{
			//unsigned long Flags = m_ActiveUpdateFlags & NodeType::kPropagatedUpdateFlags;
			//if (Flags != 0)
			//{
			//	UpdatableTree *super = Tree<NodeType>::GetSuperNode();
			//	if (super) super->PropagateUpdateFlags(Flags);
			//}
		}

		unsigned long GetActiveUpdateFlags() const
		{
			return (m_ActiveUpdateFlags);
		}

		unsigned long GetCurrentUpdateFlags() const
		{
			return (m_CurrentUpdateFlags);
		}

		unsigned long GetSubtreeUpdateFlags() const
		{
			return (m_SubtreeUpdateFlags);
		}

		void Detach()
		{
			UpdatableTree* Super = Tree<NodeType>::GetSuperNode();
			if (Super)
			{
				/*unsigned long Flags = m_ActiveUpdateFlags & NodeType::kPropagatedUpdateFlags;
				if (Flags != 0) super->PropagateUpdateFlags(Flags);*/

				Tree<NodeType>::Detach();
			}
		}

		void AddSubnode(NodeType* Node)
		{
			Node->UpdatableTree<NodeType>::Detach();
			Tree<NodeType>::AddSubnode(Node);
			Node->Invalidate();
		}

		void AddFirstSubnode(NodeType* Node)
		{
			Node->UpdatableTree<NodeType>::Detach();
			Tree<NodeType>::AddFirstSubnode(Node);
			Node->Invalidate();
		}

		void AddSubnodeBefore(NodeType *Node, NodeType* Before)
		{
			Node->UpdatableTree<NodeType>::Detach();
			Tree<NodeType>::AddSubnodeBefore(Node, Before);
			Node->Invalidate();
		}

		void AddSubnodeAfter(NodeType *Node, NodeType* After)
		{
			Node->UpdatableTree<NodeType>::Detach();
			Tree<NodeType>::AddSubnodeAfter(Node, After);
			Node->Invalidate();
		}

		void RemoveSubnode(NodeType *Node)
		{
			//unsigned long Flags = Node->GetActiveUpdateFlags() & NodeType::kPropagatedUpdateFlags;
			//if (Flags != 0) PropagateUpdateFlags(NodeType::kPropagatedUpdateFlags);

			Tree<NodeType>::RemoveSubnode(Node);
		}

		void SetActiveUpdateFlags(unsigned long Flags)
		{
			m_ActiveUpdateFlags = Flags;
			m_CurrentUpdateFlags = Flags;

			UpdatableTree *super = Tree<NodeType>::GetSuperNode();
			if (super) super->PropagateUpdateFlags(Flags);
		}

		virtual void Invalidate()
		{
			unsigned long Flags = m_CurrentUpdateFlags | m_ActiveUpdateFlags;
			m_CurrentUpdateFlags = Flags;

			UpdatableTree *super = Tree<NodeType>::GetSuperNode();
			if (super) super->PropagateUpdateFlags(Flags | m_SubtreeUpdateFlags);

			UpdatableTree *Node = Tree<NodeType>::GetFirstSubnode();
			while (Node)
			{
				Node->Invalidate();
				Node = Node->Next();
			}
		}

		virtual void Update(float DeltaT)
		{
			m_CurrentUpdateFlags = 0;

			if (m_SubtreeUpdateFlags != 0)
			{
				m_SubtreeUpdateFlags = 0;

				UpdatableTree *Node = Tree<NodeType>::GetFirstSubnode();
				while (Node)
				{
					Node->Update(DeltaT);
					Node = Node->Next();
				}
			}
		}

	private:

		unsigned long	m_ActiveUpdateFlags;
		unsigned long	m_CurrentUpdateFlags;
		unsigned long	m_SubtreeUpdateFlags;

		void PropagateUpdateFlags(unsigned long Flags)
		{
			UpdatableTree *Node = this;
			do
			{
				if ((Node->m_SubtreeUpdateFlags & Flags) == Flags) break;

				/*Node->m_CurrentUpdateFlags |= Flags & NodeType::kPropagatedUpdateFlags;
				Node->m_SubtreeUpdateFlags |= Flags;*/

				Node = Node->GetSuperNode();
			} while (Node);
		}

	protected:

		UpdatableTree()
		{
			m_ActiveUpdateFlags = NodeType::InitialUpdateFlags;
			m_CurrentUpdateFlags = NodeType::InitialUpdateFlags;
			m_SubtreeUpdateFlags = 0;
		}

		void SetCurrentUpdateFlags(unsigned long Flags)
		{
			m_CurrentUpdateFlags = Flags;
		}

		void SetSubtreeUpdateFlags(unsigned long Flags)
		{
			m_SubtreeUpdateFlags = Flags;
		}
	};	
	
}//Namespace

#endif //_ARGONUPDATETREE_HEADER_