//
//  Tree.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/19.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef Tree_hpp
#define Tree_hpp
#include "Allocation.hpp"
namespace st
{
    template<class P /*Payload*/>
    class BinaryTreeNode
	{
	public:
        typedef P payload_type;

		BinaryTreeNode<P>* GetFirstChild();

		BinaryTreeNode<P>* GetRightBrother();

		bool AddChild(BinaryTreeNode<P>* node);

		BinaryTreeNode();

		virtual ~BinaryTreeNode();

		bool operator ==    (const BinaryTreeNode& node) const;

		bool operator ==    (const payload_type& payload) const;

		bool operator >     (const BinaryTreeNode& node) const;

		bool operator >     (const payload_type& payload) const;

		bool operator <     (const BinaryTreeNode& node) const;

		bool operator <     (const payload_type& payload) const;

	public:
		BinaryTreeNode* _parent;
		BinaryTreeNode* _left;
		BinaryTreeNode* _right;
		payload_type _p;
    };


	template<class P /*Payload*/>
	st::BinaryTreeNode<P>::BinaryTreeNode()
	{

	}

	template<class P /*Payload*/>
	st::BinaryTreeNode<P>::~BinaryTreeNode()
	{

	}

	template<class P /*Payload*/>
	bool BinaryTreeNode<P>::operator < (const BinaryTreeNode<P> &node) const 
	{
		return _p < node._p;
	}

	template<class P /*Payload*/>
	bool BinaryTreeNode<P>::operator < (const payload_type& payload) const
	{
		return _p < payload;
	}

	template<class P /*Payload*/>
	bool BinaryTreeNode<P>::operator > (const BinaryTreeNode<P> &node) const 
	{
		return _p > node._p;
	}

	template<class P /*Payload*/>
	bool BinaryTreeNode<P>::operator > (const payload_type& payload) const
	{
		return _p > payload;
	}

	template<class P /*Payload*/>
	bool BinaryTreeNode<P>::operator == (const BinaryTreeNode<P> &node) const 
	{
		return _p == node._p;
	}

	template<class P /*Payload*/>
	bool BinaryTreeNode<P>::operator==(const payload_type& payload) const
	{
		return _p = payload;
	}


	//////////////////////////////////////////////////////////////////////////

    template<class P /*Payload*/, class N /*Node*/ = BinaryTreeNode<P>,class MA /*Memory Allocation*/= Mallocation>
    class Tree
	{
    public:
        typedef N	node_type;
        typedef MA	mallocation_type;
		typedef P	payload_type;

        void InjectNodes(const payload_type* nodes,size_t length);

	protected:
		node_type _root;
	};

	typedef Tree<char> BTreeOfChar;

	template<class P /*Payload*/, class N /*Node*/ /*= BinaryTreeNode<P>*/, class MA /*Memory Allocation*//*= Mallocation*/>
	void Tree<P, N, MA>::InjectNodes(const payload_type* nodes, size_t length)
	{
		int i;
		foreachArray(i, length)
		{
			const payload_type& currentPayload = *(nodes + i);
			node_type* currentNode = _root->GetFirstChild();
			do 
			{
				if (currentNode == currentPayload) 
				{
					currentNode = currentNode->GetFirstChild();
					if (!currentNode) 
					{
						currentNode->AddChild(currentPayload);
						break;
					}
				}

				currentNode = currentNode->GetRightBrother();
				if (!currentNode) 
				{
					currentNode->_p.AddChild(currentPayload);
					break;
				}
			} while (1);
		}
	}
}
#endif /* Tree_hpp */
