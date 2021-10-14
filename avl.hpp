/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:03:51 by majermou          #+#    #+#             */
/*   Updated: 2021/10/11 20:02:09 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <queue>
#include "make_pair.hpp"

template<typename T>
struct Node
{
    T               data;
    Node*           right;
    Node*           left;
    size_t          height;
    Node(T _data, size_t _height): data(_data), right(NULL), left(NULL), height(_height) {}
};

template  <
            typename Key,
            typename T,
            typename Compare = std::less<Key>,
            typename Alloc = std::allocator<Node<pair<const Key,T> > >
          >
class Avl {

public:
    typedef Key                                         key_type;
    typedef T                                           mapped_type;
    typedef pair<const key_type,mapped_type>            value_type;
    typedef Compare                                     key_compare;
    typedef Node<value_type>                            AvlNode;
    typedef Alloc                                       allocator_type;

    class value_compare {
        key_compare   comp;
    public:
        value_compare(): comp() {}
        value_compare(key_compare c) : comp(c) {}
        bool operator()(const value_type& x, const value_type& y) const {
            return comp(x.first, y.first);
        }
    };

private:

    AvlNode*                m_root;
    allocator_type          m_allocator;
    value_compare           m_comp;

    int  calHeight(AvlNode *node) {
        if (node->left && node->right) {
            if (node->left->height < node->right->height) {
                return node->right->height + 1;
            }
            else {
                return node->left->height + 1;
            }
        } else if (node->left && node->right == NULL) {
            return node->left->height + 1;
        } else if (node->right && node->left == NULL) {
            return node->right->height + 1;
        }
        return 0;
    }

    int  bf(AvlNode *node) {
        if (node->left && node->right) {
            return node->left->height - node->right->height;
        } else if (node->left && node->right == NULL) {
            return node->left->height;
        } else if (node->left == NULL && node->right) {
            return node->right->height;
        }
        return 0;
    }

    AvlNode*    llrotation(AvlNode* node){
        AvlNode *p;
        AvlNode *tp;
        p = node;
        tp = p->left;

        p->left = tp->right;
        tp->right = p;

        return tp; 
    }

    AvlNode*    rrrotation(AvlNode* node){
        AvlNode *p;
        AvlNode *tp;
        p = node;
        tp = p->right;

        p->right = tp->left;
        tp->left = p;

        return tp; 
    }

    AvlNode*    rlrotation(AvlNode* node){
        AvlNode *p;
        AvlNode *tp;
        AvlNode *tp2;
        p = node;
        tp = p->right;
        tp2 =p->right->left;

        p -> right = tp2->left;
        tp ->left = tp2->right;
        tp2 ->left = p;
        tp2->right = tp; 

        return tp2; 
    }

    AvlNode* lrrotation(AvlNode* node){
        AvlNode *p;
        AvlNode *tp;
        AvlNode *tp2;
        p = node;
        tp = p->left;
        tp2 =p->left->right;

        p -> left = tp2->right;
        tp ->right = tp2->left;
        tp2 ->right = p;
        tp2->left = tp; 

        return tp2; 
    }

    AvlNode*   Insert(AvlNode* node, const value_type data) {
        if (!node) {
            node = m_allocator.allocate(sizeof(AvlNode));
            m_allocator.construct(node, data, 1);
        } else if (m_comp(data, node->data)) {
            node->left = Insert(node->left, data);
        }
        else if (!m_comp(data, node->data) && m_comp(node->data, data)) {
            node->right = Insert(node->right, data);
        }
        node->height = calHeight(node);
        if(bf(node) == 2 && bf(node->left) == 1){
            node = llrotation(node);
        }
        else if(bf(node) == -2 && bf(node->right) == -1){
            node = rrrotation(node);
        }
        else if(bf(node) == -2 && bf(node->right) == 1){
            node = rlrotation(node);
        }
        else if(bf(node) == 2 && bf(node->left) == -1){
            node = lrrotation(node);
        }  
        return node;
    }

    AvlNode*    Remove(AvlNode* p,int data) {
        if(p->left == NULL && p->right == NULL){
            if(p == m_root)
                m_root = NULL;
            m_allocator.deallocate(p, sizeof(AvlNode));
            return NULL;
        }

        AvlNode *t;
        AvlNode *q;
        if(m_comp(p->data, data)){
            p->right = Remove(p->right,data);
        }
        else if(m_comp(data, p->data)){
            p->left = Remove(p->left,data);
        }
        else{
            if(p->left != NULL){
                q = Inpre(p->left);
                p->data = q->data;
                p->left=Remove(p->left,q->data);
            }
            else{
                q = Insuc(p->right);
                p->data = q->data;
                p->right = Remove(p->right,q->data);
            }
        }

        if(bf(p)==2 && bf(p->left)==1){ p = llrotation(p); }                  
        else if(bf(p)==2 && bf(p->left)==-1){ p = lrrotation(p); }
        else if(bf(p)==2 && bf(p->left)==0){ p = llrotation(p); }
        else if(bf(p)==-2 && bf(p->right)==-1){ p = rrrotation(p); }
        else if(bf(p)==-2 && bf(p->right)==1){ p = rlrotation(p); }
        else if(bf(p)==-2 && bf(p->right)==0){ p = llrotation(p); }

        return p;
    }

    AvlNode* inpre(AvlNode* p) {
        while(p->right != NULL) {
            p = p->right;
        }
        return p;
    }

    AvlNode* insuc(AvlNode* p) {
        while(p->left != NULL) {
            p = p->left;
        }
        return p;
    }

    AvlNode*    Clear(AvlNode* node) {
        if (!node) {
            return NULL;
        }
        Clear(node->left);
        Clear(node->right);
        m_allocator.deallocate(node, sizeof(AvlNode));
        return NULL;
    }

    // void    printInorder(AvlNode* node) {
    //     if (!node)
    //         return;
    //     printInorder(node->left);
    //     std::cout << node->data.first << "=>" << node->data.second << std::endl;
    //     printInorder(node->right);
    // }

    void printPostorder(AvlNode* node)
    {
        if (node == NULL)
            return;
        // first recur on left subtree
        printPostorder(node->left);
    
        // then recur on right subtree
        printPostorder(node->right);
    
        // now deal with the node
        std::cout << node->data.first << " ";
    }




public:
    Avl(): m_root(NULL) {}
    ~Avl() {
        Clear(m_root);
    }

    void    insert(value_type data) {
        m_root = Insert(m_root, data);
    }
    void    remove(value_type val) {
        m_root = Remove(m_root, val);
    }
    void    clear() {
        m_root = Clear(m_root);
    }
    void    print() {
        printPostorder(m_root);
    }

};

#endif // AVL_HPP
