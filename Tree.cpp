//
//  Tree.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/19.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include "Tree.hpp"
namespace st{
    template<class P>
    bool BinaryTreeNode<P>::operator < (const BinaryTreeNode<P> &node) const {
        return _p < node._p;
    }
    template<class P>
    bool BinaryTreeNode<P>::operator > (const BinaryTreeNode<P> &node) const {
        return _p > node._p;
    }
    template<class P>
    bool BinaryTreeNode<P>::operator == (const BinaryTreeNode<P> &node) const {
        return _p == node._p;
    }
    template<class P>
    BinaryTreeNode<P>* BinaryTreeNode<P>::NextEmpty(){
        if(!_left){
            return _left;
        }
        if(!_right){
            return _right;
        }
        return nullptr;
    }
    template<class N,class P>
    void Tree<N,P>::InjectNodes(const payload_type* nodes,const payload_type& endOfNode){
        
    }
}
