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

	bool FindFlagNodeInTrie(const char* str, size_t length,const Tree<char>& tree, INode<char>& flagNode)
	{
		const INode<char>* currentNode = &tree.GetRoot();
		int i,j;
		foreachArray(i,length)
		{
			foreachArray(j, currentNode->GetChildCount())
			{
				if (*currentNode->GetFloatChild(j) == str[i])
				{
					currentNode = currentNode->GetFloatChild(j);
					break;
				}
			}
			if (j == currentNode->GetChildCount())
			{
				return false;
			}
		}
		if (!currentNode->IsFlagNode())
			return false;
		flagNode = *currentNode->GetFlag();
		return true;
	}

}
