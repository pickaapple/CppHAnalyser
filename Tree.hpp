//
//  Tree.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/19.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef Tree_hpp
#define Tree_hpp

#include "Macro.h"
#include "Allocation.hpp"
#include "List.hpp"
#include "String.hpp"
namespace st
{
	//////////////////////////////////////////////////////////////////////////

	template<class P /*Payload type*/>
	class Tree;

	template<class NT /*Node Type*/,class P /*Payload type*/>
	NT* NewNode(const P& payload);

	template<class NT /*Node Type*/>
	NT* NewNode();

	template<class NT /*Node Type*/>
	void DeleteNode(NT* p);

	bool TreeToString(string& buff, Tree<char>& tree);

	//////////////////////////////////////////////////////////////////////////
	//Interface
	template<typename P /*Payload*/>
	class INode
	{
	public:
		typedef P payload_type;

		virtual INode<payload_type>* GetFirstChild() const = 0;

		virtual INode<payload_type>* GetRightBrother() const = 0;

		virtual INode<payload_type>* GetFloatChild(size_t index) const = 0;

		virtual size_t				 GetChildCount() const = 0;

		virtual bool AddChild(INode<payload_type>* node) = 0;

		virtual bool IsFlagNode() const = 0;

		INode();

		INode(const INode<P>& node);

		INode(const INode<P>* node);

		virtual ~INode();

		bool operator ==    (const payload_type& payload) const;

		bool operator >     (const payload_type& payload) const;

		bool operator <     (const payload_type& payload) const;
	protected:
		DECLARE_ATTRI_REF_QUICKLY(INode<payload_type>, payload_type, Payload)

		DECLARE_ATTRI_PTR(INode<payload_type>*, Parent)

		DECLARE_ATTRI(int, Index)
	};

	//
	//  Implement
	//

	template<class P /*Payload*/>
	bool INode<P>::operator < (const payload_type& payload) const
	{
		return _Payload < payload;
	}

	template<class P /*Payload*/>
	bool INode<P>::operator > (const payload_type& payload) const
	{
		return _Payload > payload;
	}

	template<class P /*Payload*/>
	bool INode<P>::operator == (const payload_type& payload) const
	{
		return _Payload == payload;
	}

	template<typename P /*Payload*/>
	INode<P>::INode()
		:_Index(0)
	{
	}

	template<typename P /*Payload*/>
	INode<P>::INode(const INode<P>& node)
		: _Payload(node._Payload)
		, _Parent(node._Parent)
		, _Index(node._Index)
	{
	}

	template<typename P /*Payload*/>
	st::INode<P>::INode(const INode<P>* node)
	{
		ASSERT(node);
		_Payload = node->_Payload;
		_Parent = node->_Parent;
		_Index = node->_Index
	}

	template<typename P /*Payload*/>
	INode<P>::~INode()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	class FlagNode
		:public INode<char>
	{
	public:
		struct Flag
		{
			char _Flag;
			int _Type;

			Flag();

			virtual ~Flag();
		};

		INode<char>* GetFirstChild() const override;

		INode<char>* GetRightBrother() const override;

		INode<char>* GetFloatChild(size_t index) const override;

		size_t				 GetChildCount() const override;

		bool AddChild(INode<char>* node) override;

		bool IsFlagNode() const override;

		FlagNode();

		FlagNode(const char& payload);

		virtual ~FlagNode();

	protected:
		DECLARE_ATTRI_REF(List<Flag>, Flags)
	};

	//////////////////////////////////////////////////////////////////////////

	template<class P /*Payload*/>
	class TreeNode
		:public INode<P>
	{
	public:
		typedef P payload_type;

		INode<payload_type>*	GetFirstChild()			const override;

		INode<payload_type>*	GetRightBrother()		const override;

		INode<payload_type>*	GetFloatChild(size_t index)	const override;

		size_t		GetChildCount()	const override;

		bool		AddChild(INode<payload_type>* node) override;

		bool IsFlagNode() const override;

		TreeNode();

		virtual ~TreeNode();

	protected:
		DECLARE_ATTRI(List<INode*>, Children)
	};


	//
	//  Implement
	//

	template<class P /*Payload*/>
	INode<P>* TreeNode<P>::GetFirstChild() const
	{
		if (_Children.IsEmpty())
			return nullptr;
		return _Children[0];
	}

	template<class P /*Payload*/>
	INode<P>* TreeNode<P>::GetRightBrother() const
	{
		if (!_Parent)
			return nullptr;
		return _Parent->GetFloatChild(_Index + 1);
	}

	template<class P /*Payload*/>
	INode<P>* st::TreeNode<P>::GetFloatChild(size_t index) const
	{
		if (index >= _Children.size())
			return nullptr;
		return _Children[index];
	}

	template<class P /*Payload*/>
	size_t st::TreeNode<P>::GetChildCount() const
	{
		return _Children.size();
	}

	template<class P /*Payload*/>
	bool TreeNode<P>::AddChild(INode<P> *node)
	{
		node->SetParent(this);
		node->SetIndex(_Children.size());
		_Children.AddAtLast(node);
		return true;
	}

	template<class P /*Payload*/>
	bool TreeNode<P>::IsFlagNode() const
	{
		return false;
	}

	template<class P /*Payload*/>
	st::TreeNode<P>::TreeNode()
		:INode<P>()
	{
	}

	template<class P /*Payload*/>
	st::TreeNode<P>::~TreeNode()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	template<class P /*Payload*/>
	class BinaryTreeNode
		:public INode<P>
	{
	public:
		typedef P payload_type;

		INode<payload_type>* GetFirstChild()		const override;

		INode<payload_type>* GetRightBrother()		const override;

		INode<payload_type>* GetFloatChild(size_t index) const override;

		size_t		GetChildCount()	const override;

		bool		AddChild(INode<payload_type>* node) override;

		bool IsFlagNode() const override;

		BinaryTreeNode();

		virtual ~BinaryTreeNode();

	public:
		DECLARE_ATTRI_PTR(INode<payload_type>*, Left)

		DECLARE_ATTRI_PTR(INode<payload_type>*, Right)

	};

	//
	//  Implement
	//

	template<class P /*Payload*/>
	INode<P>* BinaryTreeNode<P>::GetFirstChild() const
	{
		return _Left;
	}

	template<class P /*Payload*/>
	INode<P>* BinaryTreeNode<P>::GetRightBrother() const
	{
		ASSERT(_Parent);
		return _Parent->GetChild(_Index + 1);
	}

	template<class P /*Payload*/>
	INode<P>* st::BinaryTreeNode<P>::GetFloatChild(size_t index) const
	{
		switch (index)
		{
		case 0:
			if (!_Left)
				return _Right
				return _Left;
		case 1:
			return _Right;
		default:
			break;
		}
		return nullptr;
	}

	template<class P /*Payload*/>
	size_t st::BinaryTreeNode<P>::GetChildCount() const
	{
		size_t childCount = 0;
		if (_Left)
			++childCount;
		if (_Right)
			++childCount;
		return childCount;
	}

	template<class P /*Payload*/>
	bool BinaryTreeNode<P>::AddChild(INode<P> *node)
	{
		if (!_Left)
		{
			_Left = node;
			_Left->_Index = 0;
			node->SetParent(this);
			return true;
		}
		if (!_Right)
		{
			_Right = node;
			_Right->_Index = 1;
			node->SetParent(this);
			return true;
		}

		return false;
	}

	template<class P /*Payload*/>
	bool BinaryTreeNode<P>::IsFlagNode() const
	{
		return false;
	}

	template<class P /*Payload*/>
	st::BinaryTreeNode<P>::BinaryTreeNode()
		:INode<P>()
	{

	}

	template<class P /*Payload*/>
	st::BinaryTreeNode<P>::~BinaryTreeNode()
	{

	}

	//////////////////////////////////////////////////////////////////////////

	template<class P /*Payload*/>
	class Tree
	{
	public:
		typedef P	payload_type;

		/*

		example:
		if you inject the nodes that is a array of (node1,node2,node3,node4),
		the result will be like that node1->node2->node3->node4 when the tree is empty.

		*/

		INode<payload_type>* InjectTreeNodes(const payload_type* payload, size_t length)
		{
			if (length > _Height)
				_Height = length;

			INode<payload_type>* currentNodeParent = &_Root;
			INode<payload_type>* currentNode = nullptr;
			int i;
			foreachArray(i, length)
			{
				const payload_type& currentPayload = *(payload + i);
				currentNode = currentNodeParent->GetFirstChild();
				//if parent of the node do not have any node
				if (!currentNode)
				{
					currentNode = NewNode<TreeNode<payload_type>>(currentPayload);
					currentNodeParent->AddChild(currentNode);
				}
				else
				{
					//find the same node that add remaining node
					for (; currentNode; currentNode = currentNode->GetRightBrother())
					{
						if (*currentNode == currentPayload)
						{
							break;
						}
					}
					//if do not find the same one
					if (!currentNode)
					{
						currentNode = NewNode<TreeNode<payload_type>>(currentPayload);
						currentNodeParent->AddChild(currentNode);
					}
				}
				currentNodeParent = currentNode;
			}

			return currentNode;
		};

		Tree(const P& Payload)
			:_Height(0)
		{
			_Root.SetPayload(Payload);
		}

		virtual ~Tree() {};

	protected:
		DECLARE_ATTRI_REF(TreeNode<P>, Root)

		DECLARE_ATTRI(int, Height)
	};

	//////////////////////////////////////////////////////////////////////////

	template<class P /*Payload*/>
	FlagNode* FindFlagNodeUnderNode(const INode<P>* node)
	{
		INode<P>* currentNode = nullptr;
		const INode<P>* currentParent = node;
		int i = 0;
		while (currentNode = currentParent->GetFloatChild(i++))
		{
			if (currentNode->IsFlagNode())
				return dynamic_cast<FlagNode*>(currentNode);
		}
		return nullptr;
	};

	template<class P /*Payload*/>
	FlagNode* FindFlagNodeInTrie(const P* str, size_t length, const Tree<P>& tree)
	{
		const INode<P>* currentParentNode = &tree.GetRoot();
		const INode<P>* currentNode = nullptr;
		INode<P>* flagNode = nullptr;
		int i, j, k;
		//for each character
		foreachArray(i, length)
		{
			//for each child node
			j = 0;
			while (currentNode = currentParentNode->GetFloatChild(j++))
			{
				if (*currentNode == str[i])
				{
					currentParentNode = currentNode;
					break;
				}
			}
			//do not have match child node
			if (!currentNode)
			{
				return nullptr;
			}
		}
		//find flag node
		k = 0;
		while (flagNode = currentNode->GetFloatChild(k++))
		{
			if (flagNode->IsFlagNode())
				break;
		}
		return dynamic_cast<FlagNode*>(flagNode);
	}

	template<class NT /*Node Type*/, class P /*Payload type*/>
	NT* NewNode(const P& payload)
	{
		NT* node = new NT();
		node->SetPayload(payload);
		return node;
	};

	template<class NT /*Node Type*/>
	NT* NewNode()
	{
		return new NT();
	};

	template<class NT /*Node Type*/>
	void DeleteNode(NT* p)
	{
		delete p;
	};


}
#endif /* Tree_hpp */
