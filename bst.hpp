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

#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include "make_pair.hpp"

template<typename T>
struct BstNode
{
    T           m_data;
    BstNode*    m_left;
    BstNode*    m_right;
    BstNode(T data) : m_data(data), m_left(NULL), m_right(NULL) {}
};

template  <
            typename Key,
            typename T,
            typename Compare = std::less<Key>,
            typename Alloc = std::allocator<pair<const Key,T> >
          >
class Bst
{

public:
    typedef Key                                         key_type;
    typedef T                                           mapped_type;
    typedef pair<const Key,T>                           value_type;
    typedef Compare                                     key_compare;
    typedef Alloc                                       allocator_type;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::const_reference    const_refernce;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;
    typedef typename allocator_type::difference_type    difference_type;
    typedef typename allocator_type::size_type          size_type;
    class value_compare : public std::binary_function<value_type, value_type, bool> {
        friend class map;
    protected:
        key_compare   comp;
        value_compare(key_compare c) : comp(c) {}
    public:
        bool operator()(const value_type& x, const value_type& y) const {
            return comp(x.first, y.first);
        }
    };


private:
    BstNode<value_compare>      *m_root;
    void    insert(BstNode* node, value_type data) {
        if (!root) {
            nodenew BstNode(data);
        }
        if (value_compare(data, node)) {
            node->left = insert(node->left, data);
        }
        else {
            node->right = insert(node->right, data);
        }
        return node;
    }
public:
    Bst() : m_root(NULL) {}
    ~Bst() {}
    
    void    insert(value_type data) {
        insert(m_root, data);
        
    }
    
};

#endif // BST_HPP