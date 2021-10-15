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

#include "pair.hpp"
#include "make_pair.hpp"
#include <iostream>

template<typename T>
struct Node
{
    T           data;
    Node*       right;
    Node*       left;
    Node*       parent;
    size_t      height;
    Node(T _data, size_t _height):   data(_data),
                                                    right(NULL),
                                                    left(NULL),
                                                    height(_height) {
    }
    void    setParentNode(Node* _parent) {
        parent = _parent;
    }
};

template  < typename Key,
            typename T,
            typename Compare = std::less<Key>,
            typename Alloc = std::allocator<Node<pair<Key,T> > > >
class Avl {

public:
    typedef Key                                         key_type;
    typedef T                                           mapped_type;
    typedef pair<key_type,mapped_type>                  value_type;
    typedef Compare                                     key_compare;
    typedef Node<value_type>                            AvlNode;
    typedef Alloc                                       allocator_type;
    typedef typename allocator_type::size_type              size_type;

    class value_compare {
        key_compare   comp;
        value_compare(key_compare c) : comp(c) {}
    public:
        value_compare(): comp() {}
        bool operator()(const value_type& x, const value_type& y) const {
            return comp(x.first, y.first);
        }
    };

private:

    AvlNode*                m_root;
    size_t                  m_size;
    allocator_type          m_allocator;
    value_compare           m_comp;

    size_t max(size_t a, size_t b) {
        return (a > b) ? a : b;
    }

    size_t  heightOf(AvlNode *node) {
        if (!node)
            return 0;
        return node->height;
    }

    int     getBalanceFactor(AvlNode* node) {
        if (!node)
            return 0;
        return heightOf(node->left) - heightOf(node->right);
    }

    AvlNode*    rightRotate(AvlNode* y) {
        AvlNode     *x = y->left;
        AvlNode     *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->parent = x->parent;
        x->parent = y;
        y->height = max(heightOf(y->left), heightOf(y->right)) + 1;
        x->height = max(heightOf(x->left), heightOf(x->right)) + 1;
        return x;
    }

    AvlNode*    leftRotate(AvlNode* x) {
        AvlNode     *y = x->right;
        AvlNode     *T2 = y->left;
        y->left = x;
        x->right = T2;
        y->parent = x->parent;
        x->parent = y;
        x->height = max(heightOf(x->left), heightOf(x->right)) + 1;
        y->height = max(heightOf(y->left), heightOf(y->right)) + 1;
        return y;
    }

    AvlNode*    insertNode(AvlNode* node, const value_type data, AvlNode* parent = NULL) {
        if (!node) {
            node = m_allocator.allocate(sizeof(AvlNode));
            m_allocator.construct(node, data, 1);
            node->setParentNode(parent);
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

    AvlNode*    nodeWithMinVal(AvlNode* node) {
        AvlNode*    current = node;
        while (!current->left) {
            current = current->left;
        }
        return current;
    }

    AvlNode*    removeNode(AvlNode* node, value_type data) {
        if (!node) {
            return node;
        } else if (m_comp(data, node->data)) {
            node->left = removeNode(node->left, data);
        } else if (m_comp(node->data, data)) {
            node->right = (node->right, data);
        } else {
            if (!node->left || !node->right) {
                AvlNode*    tmp = node->left ? node->left : node->right;
                if (!tmp) {
                    tmp = node;
                    node = NULL;
                } else {
                    *node = *tmp;
                    m_allocator.deallocate(tmp, sizeof(AvlNode));
                    m_size -= 1;
                }
            } else {
                AvlNode *tmp = nodeWithMinVal(node->right);
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

    AvlNode*    clearAvlTree(AvlNode* node) {
        if (!node) {
            return NULL;
        }
        clearAvlTree(node->left);
        clearAvlTree(node->right);
        m_allocator.deallocate(node, sizeof(AvlNode));
        return NULL;
    }

    AvlNode*    searchAvlTree(AvlNode* root, const value_type val) {
        AvlNode*    current = root;
        while (current) {
            if (!m_comp(val, current->data) && !m_comp(current->data, val)) {
                return current;
            } else if (m_comp(val, root->data)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return NULL;
    }

    void    printAvlTree(AvlNode* node, std::string indent, bool last) {
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
    Avl(): m_root(NULL), m_size(0) {}
    ~Avl() {
        clearAvlTree(m_root);
    }

    bool    isEmpty() const {
        return ((!m_root) ? true : false);
    }
    void    insert(value_type data) {
        m_root = insertNode(m_root, data);
    }
    void    remove(value_type val) {
        m_root = removeNode(m_root, val);
    }
    mapped_type&    search(const key_type& key) {
        AvlNode*    node = searchAvlTree(m_root, make_pair(key, mapped_type(0)));
        if (node) {
            return node->data.second;
        } 
        return mapped_type(0);
    }
    void    clear() {
        m_root = clearAvlTree(m_root);
    }
    void    print() {
        printAvlTree(m_root,"",true);
    }

    size_type   getSize() const {
        return m_size;
    }

    size_type   getMaxSize() const {
        return m_allocator.max_size();
    }
};

#endif // AVL_HPP
