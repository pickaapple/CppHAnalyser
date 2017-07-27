//
//  Tree.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/19.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include "Tree.hpp"
namespace st{
   
	bool TreeToString(string& buff, Tree<char>& tree)
	{
		List<INode<char>*> nodeStack(tree.GetHeight());

		INode<char>* currentNode = &tree.GetRoot();
		nodeStack.AddAtLast(currentNode);
		while (!nodeStack.IsEmpty())
		{
			//if NODEA has children visit children first
			if (currentNode = currentNode->GetFloatChild(0))
			{
				nodeStack.AddAtLast(currentNode);
				continue;
			}
			
			currentNode = nodeStack.PopLast();
			buff.Append(currentNode->GetPayload());				//visit first child node

			//if first child node of NODEA has right brother visit right brother 
			if (currentNode = currentNode->GetRightBrother())
			{
				nodeStack.AddAtLast(currentNode);
				continue;
			}

			//if all children of NODEA have been visited
			currentNode = nodeStack.PopLast();
			buff.Append(currentNode->GetPayload());				//visit NODEA
			
			//if NODEA has right brother visit it
			while (!(currentNode = currentNode->GetRightBrother()))
			{
				currentNode = nodeStack.PopLast();
				buff.Append(currentNode->GetPayload());
				if (nodeStack.IsEmpty())
					return true;
			}
			nodeStack.AddAtLast(currentNode);
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	FlagNode::Flag::Flag()
		:_Type(0)
	{
	}

	FlagNode::Flag::~Flag()
	{
	}

	bool FlagNode::AddChild(INode<char>* node)
	{
		ASSERT(0);
		return false;
	}

	size_t FlagNode::GetChildCount() const
	{
		ASSERT(0);
		return 0;
	}

	INode<char>* FlagNode::GetFloatChild(size_t index) const
	{
		ASSERT(0);
		return nullptr;
	}

	INode<char>* FlagNode::GetRightBrother() const
	{
		ASSERT(0);
		return nullptr;
	}

	INode<char>* FlagNode::GetFirstChild() const
	{
		return nullptr;
	}

	bool FlagNode::IsFlagNode() const
	{
		return true;
	}

	FlagNode::FlagNode()
	{

	}

	FlagNode::FlagNode(const char& payload)
	{
		INode<char>::_Payload = payload;
	}

	FlagNode::~FlagNode()
	{

	}


}
