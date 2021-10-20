/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:03:51 by majermou          #+#    #+#             */
/*   Updated: 2021/10/20 12:39:50 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_HPP
#define AVL_HPP

#include "make_pair.hpp"
#include <iostream>
#include "map.hpp"

template<typename T>
struct Node {
    typedef Node*           NodePtr;
    typedef const Node*     Const_NodePtr;

    T                   data;
    NodePtr             right;
    NodePtr             left;
    NodePtr             parent;
    size_t              height;
    Node(T _data):data(_data),right(NULL),left(NULL),parent(NULL),height(1) {
    }
};

template <  typename T,
            typename Comp,
            typename Alloc = std::allocator< T >
         > class Avl_tree {

friend class map;
public:

    typedef T                                       value_type;
    typedef typename Node<value_type>::NodePtr      AvlNode;
    typedef size_t                                  size_type;
    typedef Comp                                    value_compare;
    typedef typename Alloc::template rebind< Node<T> >::other allocator_type;
    

private:

    AvlNode                 m_root;
    AvlNode                 m_end;
    size_type               m_size;
    allocator_type          m_allocator;
    Comp                    m_comp;

    size_type max(size_type a, size_type b) {
        return (a > b) ? a : b;
    }

    size_type  heightOf(AvlNode node) {
        return (node == NULL) ? 0 : node->height;
    }

    int     getBalanceFactor(AvlNode node) {
        return (node == NULL) ? 0 : heightOf(node->left) - heightOf(node->right);
    }

    AvlNode findMin(AvlNode node) const {
        AvlNode current = node;

        if (current != NULL) {
            while (current->left) {
                current = current->left;
            }
        }
        return current;
    }

    AvlNode findMax(AvlNode node) const {
        AvlNode current = node;
        
        if (current != NULL) {
            while (current->right) {
                current = current->right;
            }
        }
        return current;
    }
    
    AvlNode    rightRotate(AvlNode y) {
        AvlNode     x = y->left;
        AvlNode     T2 = x->right;

        if(x->right != NULL)
            x->right->parent = y;
        x->right = y;
        y->left = T2;
        x->parent = y->parent;
        y->parent = x;
        y->height = max(heightOf(y->left), heightOf(y->right)) + 1;
        x->height = max(heightOf(x->left), heightOf(x->right)) + 1;
        return x;
    }

    AvlNode    leftRotate(AvlNode x) {
        AvlNode     y = x->right;
        AvlNode     T2 = y->left;

        if(y->left != NULL)
            y->left->parent = x;
        y->left = x;
        x->right = T2;
        y->parent = x->parent;
        x->parent = y;
        x->height = max(heightOf(x->left), heightOf(x->right)) + 1;
        y->height = max(heightOf(y->left), heightOf(y->right)) + 1;
        return y;
    }

    AvlNode    insertNode(AvlNode node, const value_type data, AvlNode parent = NULL) {
        if (!node) {
            node = m_allocator.allocate(1);
            m_allocator.construct(node, data);
            node->parent = parent;
            m_size += 1;
            return node;
        } else if (m_comp(data, node->data)) {
            node->left = insertNode(node->left, data, node);
        }
        else if (m_comp(node->data, data)) {
            node->right = insertNode(node->right, data, node);
        }

        // Update the balance factor of each node and
        // balance the tree
        node->height = max(heightOf(node->left), heightOf(node->right)) + 1;
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (m_comp(data, node->left->data)) {
                return rightRotate(node);
            } else if (m_comp(node->left->data, data)) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        } else if (balanceFactor < -1) {
            if (m_comp(node->right->data, data)) {
                return leftRotate(node);
            } else if (m_comp(data, node->right->data)) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }

    AvlNode    removeNode(AvlNode node, value_type data) {
        if (!node) {
            return node;
        } else if (m_comp(data, node->data)) {
            node->left = removeNode(node->left, data);
        } else if (m_comp(node->data, data)) {
            node->right = removeNode(node->right, data);
        } else {
            if (!node->left || !node->right) {
                AvlNode    tmp = node->left ? node->left : node->right;
                if (!tmp) {
                    tmp = node;
                    node = NULL;
                } else {
                    *node = *tmp;
                    m_allocator.deallocate(tmp, 1);
                    m_size -= 1;
                }
            } else {
                AvlNode tmp = findMin(node->right);
                node->data = tmp->data;
                node->right = removeNode(node->right, tmp->data);
            }
        }
        if (!node) return node;

        // Update the balance factor of each node and
        // balance the tree
        node->height = max(heightOf(node->left), heightOf(node->right));
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (getBalanceFactor(node->left) >= 0) {
                return rightRotate(node);
            } else {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        } else if (balanceFactor < -1) {
            if (getBalanceFactor(node->right) <= 0) {
                return leftRotate(node);
            } else {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }

    // Empty the tree
    AvlNode makeEmpty(AvlNode node) {
        if (node != NULL) {
            makeEmpty(node->left);
            makeEmpty(node->right);
            m_allocator.deallocate(node, 1);
        }
        return NULL;
    }

    // Search for a value in the tree
    AvlNode searchAvlTree(AvlNode node, const value_type val) const
    {
        if (node == NULL || (!m_comp(val, node->data) && !m_comp(node->data, val))) {
            return node;
        }
        if (m_comp(node->data, val)) {
            return searchAvlTree(node->right, val);
        }
        return searchAvlTree(node->left, val);
    }   

    // print the tree in a nice way //
    void    printAvlTree(AvlNode node, std::string indent, bool last) {
        if (node) {
            std::cout << indent;
            if (last) {
                std::cout << "R----";
                indent += "   ";
            } else {
                std::cout << "L----";
                indent += "|  ";
            }
            std::cout << node->data.first << std::endl;
            printAvlTree(node->left, indent, false);
            printAvlTree(node->right, indent, true);
        }
    }

public:

    Avl_tree(value_compare c): m_comp(c){
        m_root = NULL;
        m_size = 0;
        m_end = m_allocator.allocate(1);
        m_allocator.construct(m_end, value_type());
        m_end->parent = NULL;
    }
    ~Avl_tree() {
        m_root = makeEmpty(m_root);
    }

    bool    isEmpty() const {
        return (m_size == 0);
    }
    void    insert(value_type data) {
        AvlNode endNode;
        
        if ((endNode = findMax(m_root))) {
            endNode->parent->right = NULL;
        }
        m_root = insertNode(m_root, data);
        if ((endNode = findMax(m_root))) {
            endNode->right = m_end;
            m_end->parent = endNode;
        }
    }
    void    remove(value_type val) {
        AvlNode endNode;
        
        if ((endNode = findMax(m_root))) {
            endNode->parent->right = NULL;
        }
        m_root = removeNode(m_root, val);
        if ((endNode = findMax(m_root))) {
            endNode->right = m_end;
            m_end->parent = endNode;
        }
    }
    void    clear() {
        AvlNode endNode;
        
        if ((endNode = findMax(m_root))) {
            endNode->parent->right = NULL;
        }
        m_root = makeEmpty(m_root);
        m_size = 0;
    }
    size_type   getSize() const {
        return m_size;
    }
    size_type   getMaxSize() const {
        return m_allocator.max_size();
    }
    AvlNode getEndNode() const {
        return (m_size == 0) ? NULL : m_end;
    }
    AvlNode    getMinValNode() const {
        return  findMin(m_root);
    }
    AvlNode    getMaxValNode() const {
        return  findMax(m_root);
    }
    void    print() {
        printAvlTree(m_root,"",true);
    }
    AvlNode search(value_type val) const {
        return searchAvlTree(m_root, val);
    }

    void    swap(Avl_tree& x) {
        AvlNode     x_begin = x.m_root;
        AvlNode     x_end = x.m_end;
        size_type   x_size = x.m_size;

        x.m_size = m_size;
        m_size = x_size;
        x.m_root = m_root;
        x.m_end = m_end;
        m_root = x_begin;
        m_end = x_end;
    }

};

#endif // AVL_HPP
