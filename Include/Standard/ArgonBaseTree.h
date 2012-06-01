#ifndef _ARGONBASETREE_HEADER_
#define _ARGONBASETREE_HEADER_

#include "ArgonStandard.h"

namespace Argon
{
	class TreeBase
	{
	public:

		///GETSUBNDECOUNT(LONG)
		///
		/// The $GetSubnodeCount$ function returns the number of the immediate subnodes of an object.
		///
		/// No Param
		long GetSubnodeCount() const
		{
			long Count = 0;
			const TreeBase* SubNode = m_FirstSubnode;
			while(SubNode)
			{
				Count++;
				SubNode = SubNode->m_NextNode;
			}

			return (Count);
		}

		///GETNODEINDEX(LONG)
		///
		/// Get the NodeIndex if this Node
		///
		/// No Param
		long GetNodeIndex() const
		{
			long Index = 0;

			const TreeBase* Element = this;
			for (;;)
			{
				Element = Element->Previous();
				if (!Element) break;
				Index++;
			}

			return (Index);
		}

		///REMOVESUBTREE(VOID)
		///
		/// The $RemoveSubtree$ function removes all of the immediate subnodes of an object.
		///
		/// No Param	
		void RemoveSubtree()
		{
			TreeBase* Subnode = m_FirstSubnode;
			while (Subnode)
			{
				TreeBase* Next = Subnode->m_NextNode;
				Subnode->m_PrevNode = NULL;
				Subnode->m_NextNode = NULL;
				Subnode->m_SuperNode = NULL;
				Subnode = Next;
			}

			m_FirstSubnode = NULL;
			m_LastSubnode = NULL;
		}

		///DETACH(VOID)
		///
		/// The $Detach$ function removes this subnode from the supernode
		///
		/// No Param
		virtual void Detach()
		{
			if (m_SuperNode) m_SuperNode->RemoveSubnode(this);
		}

	protected:

		///TREEBASE(CTOR)
		///
		///When a $Tree$ object is initially created, its super node is $NULL$ and it has no subnodes. An object having no super node 
		///is the root of a tree. (A newly created $Tree$ object can be thought of as the root of a tree containing a single object.)
		///In a normal tree structure, one object is created to serve as the root node. Objects are added to the tree by calling the
		///$@Tree::AddSubnode@$ function to designate them as subnodes of other objects in the tree.
		///
		/// No Param
		TreeBase()
		{
			m_PrevNode = NULL;
			m_NextNode = NULL;
			m_SuperNode = NULL;
			m_FirstSubnode = NULL;
			m_LastSubnode = NULL;
		}

		virtual ~TreeBase()
		{
			PurgeSubtree();
			if (m_SuperNode) m_SuperNode->RemoveSubnode(this);
		}

		TreeBase *Previous() const
		{
			return (m_PrevNode);
		}

		TreeBase *Next() const
		{
			return (m_NextNode);
		}

		///GETSUPERNODE(TREEBASE)
		///
		/// The $GetSuperNode$ function returns the direct super node above an object in a tree. If the object is the root of a
		/// tree, then the return value is $NULL$
		///
		/// No Param
		TreeBase *GetSuperNode() const
		{
			return (m_SuperNode);
		}

		///GETFIRSTSUBNODE(TREEBASE)
		///
		/// The $GetFirstSubnode$ function returns the first direct subnode of an object is a tree. If the object has no subnodes,
		/// then the return value is $NULL$.
		///
		/// No Param
		TreeBase *GetFirstSubnode() const
		{
			return (m_FirstSubnode);
		}

		///GETLASESUBNODE(TREEBASE)
		///
		/// The $GetLastSubnode$ function returns the last direct subnode of an object is a tree. If the object has no subnodes,
		/// then the return value is $NULL$.
		/// 
		/// All of the direct subnodes of an object are stored in a single linked list. To go from one subnode to the next,
		/// starting with the last, the $@ListElement::Previous@$ function should be called.
		///
		/// No Param
		TreeBase *GetLastSubnode() const
		{
			return (m_LastSubnode);
		}

		TreeBase *GetRootNode()
		{
			TreeBase *root = this;
			for (;;)
			{
				TreeBase* Node = root->m_SuperNode;
				if (!Node) break;
				root = Node;
			}

			return (root);
		}



		///GETROOTNODE(TREEBASE)
		///
		/// The $GetRootNode$ function returns the root node of the tree containing an object. If the object is the root node
		/// of a tree, then the return value is a pointer to itself.
		///
		/// No Param
		const TreeBase *GetRootNode() const
		{
			const TreeBase *root = this;
			for (;;)
			{
				const TreeBase* Node = root->m_SuperNode;
				if (!Node) break;
				root = Node;
			}

			return (root);
		}

		///DESCENDANT(BOOL)
		///
		/// The $Descendant$ function returns $true$ if the node specified by the $node$ parameter is a descendant
		/// of the node for which the function is called. If the node is not an descendant, this function returns $false$.
		///
		///Param Node: Test if Node is an descendant of another.
		bool Descendant(const TreeBase* Node) const
		{
			TreeBase* Super = Node->m_SuperNode;
			while (Super)
			{
				if (Super == this) return (true);
				Super = Super->m_SuperNode;
			}

			return (false);
		}

		TreeBase *GetLeftMostNode()
		{
			TreeBase* Node = this;
			for (;;)
			{
				TreeBase* Subnode = Node->m_FirstSubnode;
				if (!Subnode) break;
				Node = Subnode;
			}

			return (Node);
		}

		const TreeBase *GetLeftMostNode() const
		{
			const TreeBase* Node = this;
			for (;;)
			{
				const TreeBase* Subnode = Node->m_FirstSubnode;
				if (!Subnode) break;
				Node = Subnode;
			}

			return (Node);
		} 

		TreeBase *GetRightMostNode() 
		{ 
			TreeBase* Node = this; 
			for (;;)
			{ 
				TreeBase* Subnode = Node->m_LastSubnode; 
				if (!Subnode) break;
				Node = Subnode; 
			} 

			return (Node); 
		}

		const TreeBase *GetRightMostNode() const
		{
			const TreeBase* Node = this;
			for (;;)
			{
				const TreeBase* Subnode = Node->m_LastSubnode;
				if (!Subnode) break;
				Node = Subnode;
			}

			return (Node);
		}



		///GETNEXTNODE(TREEBASE)
		///
		/// To iterate through the subnode hierarchy of a tree, the $GetNextNode$ function should be repeatedly called for the root
		/// node of the tree until it returns $NULL$. The root node is considered the first node visited in the tree. The second
		/// node is obtained by calling $GetNextNode$ with the $node$ parameter set to a pointer to the root node. The traversal
		/// occurs in depth-first order, meaning that a particular node's entire subtree is visited before the next node at the
		/// same level in the tree. The traversal is also a pre-order traversal, meaning that a particular node is visited
		/// before any of its subnodes are visited.
		///
		/// Param Node: 
		TreeBase *GetNextNode(const TreeBase* Node) const
		{
			TreeBase *N = Node->GetFirstSubnode();
			if (!N)
			{
				for (;;)
				{
					if (Node == this) break;

					N = Node->m_NextNode;
					if (N) break;

					Node = Node->m_SuperNode;
				}
			}

			return (N);
		}

		TreeBase *GetPreviousNode(const TreeBase* Node)
		{
			if (Node == this) return (NULL);

			TreeBase *N = Node->m_PrevNode;
			if (!N) return (Node->m_SuperNode);
			return (N->GetRightMostNode());
		}

		const TreeBase *GetPreviousNode(const TreeBase* Node) const
		{
			if (Node == this) return (NULL);

			const TreeBase *N = Node->m_PrevNode;
			if (!N) return (Node->m_SuperNode);
			return (N->GetRightMostNode());
		}

		///GETNEXTLEVELNODE(TREEBASE)
		///
		/// During iteration of the nodes in a tree, the $GetNextLevelNode$ function can be used to jump to the next subnode on the
		/// same level as the $node$ parameter, skipping its entire subtree. Node selection after skipping the subtree behaves
		/// exactly like that used by the $@Tree::GetNextNode@$ function.
		///
		///Param Node:
		TreeBase *GetNextLevelNode(const TreeBase* Node) const
		{
			TreeBase *N = NULL;
			for (;;)
			{
				if (Node == this) break;

				N = Node->Next();
				if (N) break;

				Node = Node->m_SuperNode;
			}

			return (N);
		}

		///MOVESUBTREE(TREEBASE)
		///
		/// The $MoveSubtree$ function removes all of the subnodes of an object and then transfers all of them as
		/// subnodes of the object specified by the $super$ parameter.]
		///
		///Param Super:
		void MoveSubtree(TreeBase* Super)
		{
			for (;;)
			{
				TreeBase* Node = GetFirstSubnode();
				if (!Node) break;
				Super->AddSubnode(Node);
			}
		}
		
		///PURGESUBTREE(VOID)
		///
		/// The $PurgeSubtree$ function recursively deletes all of the subnodes of an object.
		///
		///No Param:
		void PurgeSubtree()
		{
			while (m_FirstSubnode) delete m_FirstSubnode;
		}

		///ADDSUBNODE(VOID)
		///
		/// The $AddSubnode$ function adds the node pointed to by the $node$ parameter to an object. If the node is already a
		/// member of a tree, then it is first removed from that tree. If the node being added as a subnode has subnodes itself,
		/// then those subnodes are carried with the node into the new tree.
		///
		///Param Node:
		void AddSubnode(TreeBase* Node)
		{
			TreeBase* Tree = Node->m_SuperNode;
			if (Tree)
			{
				TreeBase* Prev = Node->m_PrevNode;
				TreeBase* Next = Node->m_NextNode;

				if (Prev)
				{
					Prev->m_NextNode = Next;
					Node->m_PrevNode = NULL;
				}

				if (Next)
				{
					Next->m_PrevNode = Prev;
					Node->m_NextNode = NULL;
				}

				if (Tree->m_FirstSubnode == Node) Tree->m_FirstSubnode = Next;
				if (Tree->m_LastSubnode == Node) Tree->m_LastSubnode = Prev;
			}

			if (m_LastSubnode)
			{
				m_LastSubnode->m_NextNode = Node;
				Node->m_PrevNode = m_LastSubnode;
				m_LastSubnode = Node;
			}
			else
			{
				m_FirstSubnode = m_LastSubnode = Node;
			}

			Node->m_SuperNode = this;
		}

		void AddFirstSubnode(TreeBase* Node)
		{
			TreeBase* Tree = Node->m_SuperNode;
			if (Tree)
			{
				TreeBase* Prev = Node->m_PrevNode;
				TreeBase* Next = Node->m_NextNode;

				if (Prev)
				{
					Prev->m_NextNode = Next;
					Node->m_PrevNode = NULL;
				}

				if (Next)
				{
					Next->m_PrevNode = Prev;
					Node->m_NextNode = NULL;
				}

				if (Tree->m_FirstSubnode == Node) Tree->m_FirstSubnode = Next;
				if (Tree->m_LastSubnode == Node) Tree->m_LastSubnode = Prev;
			}

			if (m_FirstSubnode)
			{
				m_FirstSubnode->m_PrevNode = Node;
				Node->m_NextNode = m_FirstSubnode;
				m_FirstSubnode = Node;
			}
			else
			{
				m_FirstSubnode = m_LastSubnode = Node;
			}

			Node->m_SuperNode = this;
		}

		void AddSubnodeBefore(TreeBase* Node, TreeBase* Before)
		{
			TreeBase* Tree = Node->m_SuperNode;
			if (Tree)
			{
				TreeBase* Prev = Node->m_PrevNode;
				TreeBase* Next = Node->m_NextNode;
				if (Prev) Prev->m_NextNode = Next;
				if (Next) Next->m_PrevNode = Prev;
				if (Tree->m_FirstSubnode == Node) Tree->m_FirstSubnode = Next;
				if (Tree->m_LastSubnode == Node) Tree->m_LastSubnode = Prev;
			}

			Node->m_NextNode = Before;
			TreeBase* After = Before->m_PrevNode;
			Node->m_PrevNode = After;

			if (After) After->m_NextNode = Node;
			else m_FirstSubnode = Node;

			Before->m_PrevNode = Node;
			Node->m_SuperNode = this;
		}

		void AddSubnodeAfter(TreeBase* Node, TreeBase* After)
		{
			TreeBase* Tree = Node->m_SuperNode;
			if (Tree)
			{
				TreeBase* Prev = Node->m_PrevNode;
				TreeBase* Next = Node->m_NextNode;
				if (Prev) Prev->m_NextNode = Next;
				if (Next) Next->m_PrevNode = Prev;
				if (Tree->m_FirstSubnode == Node) Tree->m_FirstSubnode = Next;
				if (Tree->m_LastSubnode == Node) Tree->m_LastSubnode = Prev;
			}

			Node->m_PrevNode = After;
			TreeBase* Before = After->m_NextNode;
			Node->m_NextNode = Before;

			if (Before) Before->m_PrevNode = Node;
			else m_LastSubnode = Node;

			After->m_NextNode = Node;
			Node->m_SuperNode = this;
		}

		

		///REMOVESUBNODE(VOID)
		///
		/// The $RemoveSubnode$ function removes the node pointed to by the $node$ parameter from an object. The node must be
		/// an existing subnode of the object for which $RemoveSubnode$ is called. If the node has any subnodes, then those
		/// subnodes remain subnodes of the removed node.
		///
		///Param Subnode:
		void RemoveSubnode(TreeBase* Subnode)
		{
			TreeBase* Prev = Subnode->m_PrevNode;
			TreeBase* Next = Subnode->m_NextNode;
			if (Prev) Prev->m_NextNode = Next;
			if (Next) Next->m_PrevNode = Prev;

			if (m_FirstSubnode == Subnode) m_FirstSubnode = Next;
			if (m_LastSubnode == Subnode) m_LastSubnode = Prev;

			Subnode->m_PrevNode = NULL;
			Subnode->m_NextNode = NULL;
			Subnode->m_SuperNode = NULL;
		}
	private:
		TreeBase*		m_PrevNode;
		TreeBase*		m_NextNode;
		TreeBase*		m_SuperNode;
		TreeBase*		m_FirstSubnode;
		TreeBase*		m_LastSubnode;
	}; //Class
} //Namespace

#endif //_ARGONBASETREE_HEADER_