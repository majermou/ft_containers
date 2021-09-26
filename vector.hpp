/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 09:38:05 by majermou          #+#    #+#             */
/*   Updated: 2021/09/17 09:38:50 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <iterator>

namespace ft {

template < class T, class Alloc = std::allocator<T> >
class vector
{
    public:

        typedef T                                                   value_type;
        typedef Alloc                                               allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef pointer                                             iterator;
        typedef const_pointer                                       const_iterator;
        typedef std::reverse_iterator<iterator>                     reverse_iterator;
        typedef std::reverse_iterator<const_iterator>               const_reverse_iterator;
        typedef ptrdiff_t                                           difference_type;
        typedef size_t                                              size_type;

    private:

        value_type          *buff;
        size_type           _capacity;
        size_type           _size;

        void        reallocate(void)
        {
            size_type       newCapacity = (!_capacity) ? 1 : 2 * _capacity;
            value_type      *ptr = allocator_type().allocate(newCapacity);

            for (size_type i = 0; i < _size; i++)
                ptr[i] = buff[i];
            allocator_type().deallocate(buff, _capacity);
            buff = ptr;
            _capacity = newCapacity;
        }

    public:

        explicit vector (): _capacity(0), _size(0) {}
        explicit vector (size_type n, const value_type& val): _capacity(n), _size(0) {
            buff = allocator_type().allocate(_capacity);
            for (size_type i = 0; i < n; ++i)
                buff[_size++] = val;
        }
        template <class InputIterator>
        vector (InputIterator first, InputIterator last): _capacity(last - first), _size(0) {
            buff = allocator_type().allocate(_capacity);
            while (first != last)
                buff[_size++] = *first++;
        }
        vector (const vector& x): _capacity(x.size()), _size(0) {
            buff = allocator_type().allocate(_capacity);
            for (size_type i = 0; i < x.size(); ++i) {
                buff[_size] = x[_size];
                ++_size;
            }
        }
        ~vector () {
            allocator_type().deallocate(buff, _capacity);
            // invalidate its/ref/ptrs.
        }
        vector& operator= (const vector& x) {
            _capacity = x.size();
            _size = 0;
            buff = allocator_type().allocate(buff, _capacity);
            for (size_type i = 0; i < x.size(); ++i) {
                buff[_size] = x[_size];
                ++_size;
            }
        }

        // Iterators:
        iterator begin() { return buff; }
        const_iterator begin() const { return buff; }
        iterator end(){ return buff + _size; };
        const_iterator end() const { return buff + _size; }
        reverse_iterator rbegin() { return buff + _size; }
        const_reverse_iterator rbegin() const { return buff + _size; }
        reverse_iterator rend() { return buff; }
        const_reverse_iterator rend() const { return buff; }

        //Capacity:
        size_type   size() const {return _size; }
        size_type   max_size() const { return allocator_type().max_size(); }
        size_type   capacity() const { return _capacity; }
        bool        empty() const { return((!_size) ? true: false); }
        void        resize (size_type n) {
            if (n < _size)
                _size = n;
            else if (n > _size) {
                if (n > _capacity) {
                    _capacity = n;
                    value_type* ptr = allocator_type().alloc(_capacity);
                    for (size_type i = 0; i < _size; i++)
                        ptr[i] = buff[i];
                    allocator_type().deallocate(buff, _capacity);
                    buff = ptr;
                }
                for (_size; _size < n; ++_size)
                    buff[_size] = value_type(0);
            }
        }
        void resize (size_type n, value_type val = value_type()){
            if (n < _size)
                _size = n;
            else if (n > _size) {
                if (n > _capacity) {
                    _capacity = n;
                    value_type* ptr = allocator_type().alloc(_capacity);
                    for (size_type i = 0; i < _size; i++)
                        ptr[i] = buff[i];
                    allocator_type().deallocate(buff, _capacity);
                    buff = ptr;
                }
                for (_size; _size < n; ++_size)
                    buff[_size] = val;
            }
        }
        void reserve (size_type n)
        {
            if (n > _capacity)
            {
                value_type      *ptr = allocator_type().allocate(n);
                for (size_type i = 0; i < _size; i++)
                    ptr[i] = buff[i];
                allocator_type().deallocate(buff, _capacity);
                buff = ptr;
                _capacity = n;
            }
        }

        // Element access:
        value_type&          operator[](size_type n) { return buff[n]; }
        const value_type&    operator[] (size_type n) const { return buff[n]; }

        value_type&          at (size_type n)
        {
            if (n >= _size)
                throw std::out_of_range("-");
            return buff[n];
        }
        const value_type&    at (size_type n) const
        {
             if (n >= _size)
                throw std::out_of_range("-");
            return buff[n];
        }

        value_type&          front() { return buff[0]; }
        const value_type&    front() const { return buff[0]; }

        value_type&          back() { return buff[_size - 1]; }
        const value_type&    back() const { return buff[_size - 1]; }

        // Modifiers:
        void        push_back (const value_type& val)
        {
            if (_size + 1 >= _capacity)
                reallocate();
            buff[_size++] = val;
        }
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last) {
            if (last - first > _capacity) {
                _capacity = last - first;
                allocator_type().deallocate(buff, _capacity);
                buff = allocator_type().allocate(_capacity);
            }
            for (_size = 0; _size < last - first; ++_size) {
                buff[_size] = *first++;
            }
        }
        void assign (size_type n, const value_type& val) {
            if (n > _capacity) {
                _capacity = n;
                allocator_type().deallocate(buff, _capacity);
                buff = allocator_type().allocate(_capacity);
            }
            for (_size = 0; _size < n; ++_size) {
                buff[_size] = val;
            }
        }
        void pop_back() {
            --_size;
        }

        // insert
        // erase
        // swap

        void clear() { _size = 0; }
        allocator_type get_allocator() const {
            return allocator_type();
        }

};

}

#endif