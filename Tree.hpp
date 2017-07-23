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
        
        DECLARE_ATTRI_QUICKLY(INode<P>, payload_type, payload);
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
        DECLARE_ATTRI_PTR(INode<P>*, parent);
        
        DECLARE_ATTRI(List<INode<P>*>, children);
        
        DECLARE_ATTRI(int, index);
    };
    
    //
    //  Implement
    //
    
    template<class P /*Payload*/>
    INode<P>* TreeNode<P>::GetFirstChild() const
    {
        return _children.At(0);
    }
    
    template<class P /*Payload*/>
    INode<P>* TreeNode<P>::GetRightBrother() const
    {
        ASSERT(_parent);
        return _parent ->_children.At(_index+1);
    }
    
    template<class P /*Payload*/>
    bool TreeNode<P>::AddChild(INode<P> *node)
    {
        _children.AddAtLast(node)._index = _index + 1;
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
        DECLARE_ATTRI_PTR(INode<P>*, parent);
        
        DECLARE_ATTRI_PTR(INode<P>*, left);
        
        DECLARE_ATTRI_PTR(INode<P>*, right);
        
    };
    
    //
    //  Implement
    //
    
    template<class P /*Payload*/>
    INode<P>* BinaryTreeNode<P>::GetFirstChild() const
    {
        return _left;
    }
    
    template<class P /*Payload*/>
    INode<P>* BinaryTreeNode<P>::GetRightBrother() const
    {
        ASSERT(_parent);
        return _parent -> _right;
    }
    
    template<class P /*Payload*/>
    bool BinaryTreeNode<P>::AddChild(INode<P> *node)
    {
        if(!_left)
        {
            _left = node;
            return true;
        }
        if(!_right)
        {
            _right = node;
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
        
        void Initialize(INode<P>*);
        
        void InjectNodes(const payload_type* payloads,size_t length);
        
        Tree();
        
        virtual ~Tree();
        
    private:
        INode<payload_type>* NewData(const payload_type &payload);
        
        void DeleteData(INode<payload_type>* p);
        
	protected:
		INode<P>* _root;
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
			INode<P>* currentNode = _root->GetFirstChild();
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
					currentNode->_p.AddChild(NewData()->SetPayload(currentPayload));
					break;
				}
			} while (1);
		}
	}
    
    template<class P /*Payload*/, class MA /*Memory Allocation*//*= Mallocation*/>
    Tree<P,MA>::Tree()
    {
    }
    
    template<class P /*Payload*/, class MA /*Memory Allocation*//*= Mallocation*/>
    Tree<P,MA>::~Tree()
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
