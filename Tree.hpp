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
        
		bool IsFlagNode() const;

        INode();
        
        virtual ~INode();
        
        bool operator ==    (const payload_type& payload) const;
        
        bool operator >     (const payload_type& payload) const;
        
        bool operator <     (const payload_type& payload) const;
    protected:
		DECLARE_ATTRI_REF_QUICKLY(INode<payload_type>, payload_type, Payload)

		DECLARE_ATTRI_PTR(INode<payload_type>*, Parent)

		DECLARE_ATTRI_PTR(INode<payload_type>*, Flag)

		DECLARE_ATTRI(int, Index)
    };

    //
    //  Implement
    //

	template<typename P /*Payload*/>
	bool st::INode<P>::IsFlagNode() const
	{
		return !!_Flag;
	}

	template<typename P /*Payload*/>
	st::INode<P>::INode()
		:_Index(0)
	{

	}

	template<typename P /*Payload*/>
	st::INode<P>::~INode()
	{

	}

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
        return _Parent -> GetChild(_Index + 1);
    }

	template<class P /*Payload*/>
	INode<P>* st::BinaryTreeNode<P>::GetFloatChild(size_t index) const
	{
		switch (index)
		{
		case 0:
			if(!_Left)
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
        if(!_Left)
        {
            _Left = node;
			_Left->_Index = 0;
			node->SetParent(this);
            return true;
        }
        if(!_Right)
        {
			_Right = node;
			_Right->_Index = 1;
			node->SetParent(this);
            return true;
        }
        
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

    template<class P /*Payload*/,class MA /*Memory Allocation*/= Mallocation>
    class Tree
	{
    public:
        typedef MA	mallocation_type;
		typedef P	payload_type;
        
		/*

		example:
		if you inject the nodes that is a array of (node1,node2,node3,node4), 
		the result will be like that node1->node2->node3->node4 when the tree is empty.

		*/
        void InjectNodes(const payload_type* payloads,size_t length);
        
        Tree(const P& rootPayload);
        
        virtual ~Tree();
        
    private:
        INode<payload_type>* NewData(const payload_type &payload);
        
        void DeleteData(INode<payload_type>* p);
        
	protected:
		DECLARE_ATTRI_REF(TreeNode<P>, Root)

		DECLARE_ATTRI(int, Height)
	};

	typedef Tree<char> BTreeOfChar;

    
    //
    //  Implement
    //
    
    
	template<class P /*Payload*/, class MA /*Memory Allocation*//*= Mallocation*/>
	void Tree<P, MA>::InjectNodes(const payload_type* payloads, size_t length)
	{
		if (length > _Height)
		{
			_Height = length;
		}
		INode<P>* currentNodeParent = &_Root;
		INode<P>* tempNode = nullptr;
		INode<P>* lastNode = nullptr;
		int i;
		foreachArray(i, length)
		{
			const payload_type& currentPayload = *(payloads + i);
			INode<P>* currentNode = currentNodeParent->GetFirstChild();
			if (!currentNode)
			{
				tempNode = NewData(currentPayload);
				currentNodeParent->AddChild(tempNode);

				//set last index node
				lastNode = NewData(currentPayload);
				lastNode->SetPayload(i);
				tempNode->SetFlag(lastNode);

				currentNodeParent = tempNode;
			}
			else
			{
				for (;currentNode; currentNode = currentNode->GetRightBrother())
				{
					if (*currentNode == currentPayload)
					{
						currentNodeParent = currentNode;
						break;
					}
				}
				if (!currentNode)//if do not find the same one
				{
					tempNode = NewData(currentPayload);
					currentNodeParent->AddChild(tempNode);

					//set last index node
					lastNode = NewData(currentPayload);
					lastNode->SetPayload(i);
					tempNode->SetFlag(lastNode);

					currentNodeParent = tempNode;
				}
			}
			
		}
	}
    
    template<class P /*Payload*/, class MA /*Memory Allocation*//*= Mallocation*/>
	Tree<P, MA>::Tree(const P& rootPayload)
		:_Height(0)
    {
		_Root.SetPayload(rootPayload);
    }
    
    template<class P /*Payload*/, class MA /*Memory Allocation*//*= Mallocation*/>
    Tree<P,MA>::~Tree()
    {
    }

	//private function

    template<class P /*Payload*/, class MA /*Memory Allocation*//*= Mallocation*/>
    INode<P>* Tree<P,MA>::NewData(const payload_type &payload)
    {
		TreeNode<P>* node = new TreeNode<P>();
		return node->SetPayload(payload);
        //return static_cast<INode<P>*>(mallocation_type::New(sizeof(TreeNode<P>)))->SetPayload(payload);
    }
    
    template<class P /*Payload*/, class MA /*Memory Allocation*//*= Mallocation*/>
    void Tree<P,MA>::DeleteData(INode<payload_type> *p)
    {
        p->~INode<payload_type>();
        mallocation_type::Delete((void*)p);
    }

	//////////////////////////////////////////////////////////////////////////

	bool TreeToString(string& buff, Tree<char>& tree);
	
	bool FindFlagNodeInTrie(const char* str,size_t length,const Tree<char>& tree, INode<char>& flagNode);
}
#endif /* Tree_hpp */
