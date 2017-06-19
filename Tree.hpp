//
//  Tree.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/19.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef Tree_hpp
#define Tree_hpp
namespace st{
    template<class P>
    class BinaryTreeNode{
        typedef P payload_type;
        BinaryTreeNode* _parent;
        BinaryTreeNode* _left;
        BinaryTreeNode* _right;
        payload_type p;
        /**
         Next empty node of this node

         @return 
            next custom node's address, but null when this node has full children.
         */
        BinaryTreeNode* NextEmpty();
        bool operator ==    (const BinaryTreeNode& node) const;
        bool operator >     (const BinaryTreeNode& node) const;
        bool operator <     (const BinaryTreeNode& node) const;
    };
    template<class N>
    class Tree{
    public:
        typedef N node_type;
        
        void InjectNodes(const node_type* nodes,const node_type& endOfNode);
        node_type root;
    };
    
    typedef Tree<BinaryTreeNode<char>> BTreeOfChar;
}
#endif /* Tree_hpp */
