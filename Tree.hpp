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
namespace st
{
	//////////////////////////////////////////////////////////////////////////
	//Interface
    template<typename P /*Payload*/>
    class INode
    {
    public:
        typedef P payload_type;
        
        virtual INode<P>* GetFirstChild() const = 0;
        
        virtual INode<P>* GetRightBrother() const = 0;
        
        virtual bool AddChild(INode<payload_type>* node) = 0;
        
        INode();
        
        virtual ~INode();
        
        bool operator ==    (const payload_type& payload) const;
        
        bool operator >     (const payload_type& payload) const;
        
        bool operator <     (const payload_type& payload) const;
    protected:
		DECLARE_ATTRI_QUICKLY(INode<P>, payload_type, Payload);

		DECLARE_ATTRI_PTR(INode*, Parent);

		DECLARE_ATTRI(int, Index);
    };

    //
    //  Implement
    //

    template<class P /*Payload*/>
    bool INode<P>::operator < (const payload_type& payload) const
    {
        return _payload < payload;
    }
    
    template<class P /*Payload*/>
    bool INode<P>::operator > (const payload_type& payload) const
    {
        return _payload > payload;
    }
    
    template<class P /*Payload*/>
    bool INode<P>::operator == (const payload_type& payload) const
    {
        return _payload = payload;
    }
    
    //////////////////////////////////////////////////////////////////////////
    
    template<class P /*Payload*/>
    class TreeNode
        :INode<P>
    {
    public:
        typedef P payload_type;
        
        INode<payload_type>* GetFirstChild() const override;
        
        INode<payload_type>* GetRightBrother() const override;
        
        bool AddChild(INode<payload_type>* node) override;
        
        TreeNode();
        
        virtual ~TreeNode();
    
    protected:
        DECLARE_ATTRI(List<INode*>, Children);
    };
    
    //
    //  Implement
    //
    
    template<class P /*Payload*/>
    INode<P>* TreeNode<P>::GetFirstChild() const
    {
        return _Children.At(0);
    }
    
    template<class P /*Payload*/>
    INode<P>* TreeNode<P>::GetRightBrother() const
    {
        ASSERT(_Parent);
		TreeNode<P> *treeNode = dynamic_cast<TreeNode<P>*>(_Parent);
		if (treeNode)
			return treeNode->_Children[_Index + 1];
        return _Parent->GetRightBrother();
    }
    
    template<class P /*Payload*/>
    bool TreeNode<P>::AddChild(INode<P> *node)
    {
        _Children.AddAtLast(node)->SetIndex(_Index + 1);
        return true;
    }
    
    //////////////////////////////////////////////////////////////////////////
    
    template<class P /*Payload*/>
    class BinaryTreeNode
        :INode<P>
	{
	public:
        typedef P payload_type;

		INode<P>* GetFirstChild() const override;

		INode<P>* GetRightBrother() const override;

		bool AddChild(INode<P>* node) override;

		BinaryTreeNode();

		virtual ~BinaryTreeNode();
        
	public:
        DECLARE_ATTRI_PTR(INode<P>*, Left);
        
        DECLARE_ATTRI_PTR(INode<P>*, Right);
        
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
        return _Parent -> _Right;
    }
    
    template<class P /*Payload*/>
    bool BinaryTreeNode<P>::AddChild(INode<P> *node)
    {
        if(!_Left)
        {
            _Left = node;
			_Left->_Index = 0;
            return true;
        }
        if(!_Right)
        {
			_Right = node;
			_Right->_Index = 1;
            return true;
        }
        
        return false;
    }
    
	template<class P /*Payload*/>
	st::BinaryTreeNode<P>::BinaryTreeNode()
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
        
        void InjectNodes(const payload_type* payloads,size_t length);
        
        Tree();
        
        virtual ~Tree();
        
    private:
		void Initialize();

        INode<payload_type>* NewData(const payload_type &payload);
        
        void DeleteData(INode<payload_type>* p);
        
	protected:
		TreeNode<P> _root;
	};

	typedef Tree<char> BTreeOfChar;

    
    //
    //  Implement
    //
    
    
	template<class P /*Payload*/, class MA /*Memory Allocation*//*= Mallocation*/>
	void Tree<P, MA>::InjectNodes(const payload_type* payloads, size_t length)
	{
		int i;
		foreachArray(i, length)
		{
			const payload_type& currentPayload = *(payloads + i);
			INode<P>* currentNode = _root.GetFirstChild();
			do 
			{
				if (currentNode == currentPayload) 
				{
					if (!currentNode->GetFirstChild())
					{
						currentNode->AddChild(NewData()->SetPayload(currentPayload));
						break;
					}
                    currentNode = currentNode->GetFirstChild();
				}

				currentNode = currentNode->GetRightBrother();
				if (!currentNode) 
				{
					currentNode->GetParent()->AddChild(NewData()->SetPayload(currentPayload));
					break;
				}
			} while (1);
		}
	}
    
    template<class P /*Payload*/, class MA /*Memory Allocation*//*= Mallocation*/>
    Tree<P,MA>::Tree()
    {
		Initialize();
    }
    
    template<class P /*Payload*/, class MA /*Memory Allocation*//*= Mallocation*/>
    Tree<P,MA>::~Tree()
    {
    }

	//private function

	template<class P /*Payload*/, class MA /*Memory Allocation*//*= Mallocation*/>
	void st::Tree<P, MA>::Initialize()
	{
	}

    template<class P /*Payload*/, class MA /*Memory Allocation*//*= Mallocation*/>
    INode<P>* Tree<P,MA>::NewData(const payload_type &payload)
    {
        return static_cast<INode<P>*>(mallocation_type::New(sizeof(TreeNode<P>)))->SetPayload(payload);
    }
    
    template<class P /*Payload*/, class MA /*Memory Allocation*//*= Mallocation*/>
    void Tree<P,MA>::DeleteData(INode<payload_type> *p)
    {
        p->~INode<payload_type>();
        mallocation_type::Delete((void*)p);
    }
}
#endif /* Tree_hpp */
