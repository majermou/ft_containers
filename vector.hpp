/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:16:22 by majermou          #+#    #+#             */
/*   Updated: 2021/10/06 19:53:03 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "iterators_traits.hpp"

template <typename _Iterator> class __normal_iterator;
template <typename _Iterator> class __reverse_iterator;

namespace ft {
template < class T, class Alloc = std::allocator<T> >
class vector {
public:
        typedef T                                                   value_type;
        typedef Alloc                                               allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef __normal_iterator<pointer>                          iterator;
        typedef __normal_iterator<const_pointer>                    const_iterator;
        typedef __reverse_iterator<pointer>                         reverse_iterator;
        typedef __reverse_iterator<const_pointer>                   const_reverse_iterator;
        typedef ptrdiff_t                                           difference_type;
        typedef size_t                                              size_type;
private:
        value_type          *buff;
        size_type           _capacity;
        size_type           _size;
        allocator_type      _allocator;

        void        reallocate(void)
        {
            size_type       newCapacity = (!_capacity) ? 1 : 2 * _capacity;
            value_type      *ptr = _allocator.allocate(newCapacity);

            for (size_type i = 0; i < _size; i++)
                ptr[i] = buff[i];
            _allocator.deallocate(buff, _capacity);
            buff = ptr;
            _capacity = newCapacity;
        }
public:
        explicit vector (): _capacity(0), _size(0) {}
        explicit vector (size_type n, const value_type& val): _capacity(n), _size(0) {
            buff = _allocator.allocate(_capacity);
            for (size_type i = 0; i < n; ++i)
                buff[_size++] = val;
        }
        template <class InputIterator>
        vector (InputIterator first, InputIterator last): _capacity(last - first), _size(0) {
            buff = _allocator.allocate(_capacity);
            while (first != last)
                buff[_size++] = *first++;
        }
        vector (const vector& x): _capacity(x.size()), _size(0) {
            buff = _allocator.allocate(_capacity);
            for (size_type i = 0; i < x.size(); ++i) {
                buff[_size] = x[_size];
                ++_size;
            }
        }
        ~vector () {
            _allocator.deallocate(buff, _capacity);
            // invalidate its/ref/ptrs.
        }
        vector& operator= (const vector& x) {
            _capacity = x.size();
            _size = 0;
            buff = _allocator.allocate(buff, _capacity);
            for (size_type i = 0; i < x.size(); ++i) {
                buff[_size] = x[_size];
                ++_size;
            }
        }

        iterator begin() { return iterator(buff); }
        const_iterator begin() const { return const_iterator(buff); }
        iterator end() { return iterator(buff + _size); }
        const_iterator end() const { return const_iterator(buff + _size); }
        reverse_iterator rbegin() { return reverse_iterator(buff + _size); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(buff + _size); }
        reverse_iterator rend() { return reverse_iterator(buff); }
        const_reverse_iterator rend() const { return const_reverse_iterator(buff); }

        //Capacity:
        size_type   size() const {return _size; }
        size_type   max_size() const { return _allocator.max_size(); }
        size_type   capacity() const { return _capacity; }
        bool        empty() const { return((!_size) ? true: false); }
        void        resize (size_type n) {
            if (n < _size)
                _size = n;
            else if (n > _size) {
                if (n > _capacity) {
                    _capacity = n;
                    value_type* ptr = _allocator.alloc(_capacity);
                    for (size_type i = 0; i < _size; i++)
                        ptr[i] = buff[i];
                    _allocator.deallocate(buff, _capacity);
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
                    value_type* ptr = _allocator.alloc(_capacity);
                    for (size_type i = 0; i < _size; i++)
                        ptr[i] = buff[i];
                    _allocator.deallocate(buff, _capacity);
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
                value_type      *ptr = _allocator.allocate(n);
                for (size_type i = 0; i < _size; i++)
                    ptr[i] = buff[i];
                _allocator.deallocate(buff, _capacity);
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
                _allocator.deallocate(buff, _capacity);
                buff = _allocator.allocate(_capacity);
            }
            for (_size = 0; _size < last - first; ++_size) {
                buff[_size] = *first++;
            }
        }
        void assign (size_type n, const value_type& val) {
            if (n > _capacity) {
                _capacity = n;
                _allocator.deallocate(buff, _capacity);
                buff = _allocator.allocate(_capacity);
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
            return _allocator;
        }

};  // vector class
}   // namespace ft

template <typename _Iterator>
class __normal_iterator
{
public:
        typedef _Iterator                                                       iterator_type;
        typedef typename __iterator_traits<iterator_type>::difference_type      difference_type;
        typedef typename __iterator_traits<iterator_type>::value_type           value_type;
        typedef typename __iterator_traits<iterator_type>::pointer              pointer;
        typedef typename __iterator_traits<iterator_type>::reference            reference;
        typedef typename __iterator_traits<iterator_type>::iterator_category    iterator_category;
private:
        iterator_type                                                           __current;
public:
        __normal_iterator(): __current() {}
        explicit __normal_iterator(iterator_type __x): __current(__x) {}
        __normal_iterator(const __normal_iterator& __x): __current(__x.__current) {}
        template <typename _Iter>
        __normal_iterator(const __normal_iterator<_Iter>& __i): __current(__i.base()) {}
        const iterator_type&    base() const { return __current; }

        reference   operator*() const { 
            return *__current;
        }
        pointer     operator->() const {
            return __current;
        }
        __normal_iterator&  operator++() {
            ++__current;
            return *this;
        }
        __normal_iterator    operator++(int) {
            return __normal_iterator(__current++);
        }
        __normal_iterator&  operator--() {
            --__current;
            return *this;
        }
        __normal_iterator   operator--(int) {
            return __normal_iterator(__current--);
        }
        reference    operator[] (difference_type __n) const {
            return __current[__n];
        }
        __normal_iterator&    operator+= (difference_type __n) {
            __current += __n;
            return *this;
        }
        __normal_iterator     operator+ (difference_type __n) {
            return __normal_iterator(__current + __n);
        }
        __normal_iterator&    operator-= (difference_type __n) {
            __current -= __n;
            return *this;
        }
        __normal_iterator&    operator- (difference_type __n) {
            return __normal_iterator(__current - __n);
        } 
};

template <typename _Iterator>
bool            operator==(const __normal_iterator<_Iterator>& x, const __normal_iterator<_Iterator>& y) { return x.base() == y.base(); }
template <typename _Iterator>
bool            operator!=(const __normal_iterator<_Iterator>& x, const __normal_iterator<_Iterator>& y) { return x.base() != y.base(); }
template <typename _Iterator>
bool            operator>(const __normal_iterator<_Iterator>& x, const __normal_iterator<_Iterator>& y) { return x.base() > y.base(); }
template <typename _Iterator>
bool            operator<(const __normal_iterator<_Iterator>& x, const __normal_iterator<_Iterator>& y) { return x.base() < y.base(); }
template <typename _Iterator>
bool            operator>=(const __normal_iterator<_Iterator>& x, const __normal_iterator<_Iterator>& y) { return x.base() >= y.base(); }
template <typename _Iterator>
bool            operator<=(const __normal_iterator<_Iterator>& x, const __normal_iterator<_Iterator>& y) { return x.base() <= y.base(); }
template <typename _Iterator>
typename __iterator_traits<_Iterator>::difference_type operator-(const __normal_iterator<_Iterator>& x, const __normal_iterator<_Iterator>& y) { return x.base() - y.base(); }

template <typename _Iterator>
class __reverse_iterator
{
public:
        typedef _Iterator                                                       iterator_type;
        typedef typename __iterator_traits<iterator_type>::difference_type      difference_type;
        typedef typename __iterator_traits<iterator_type>::value_type           value_type;
        typedef typename __iterator_traits<iterator_type>::pointer              pointer;
        typedef typename __iterator_traits<iterator_type>::reference            reference;
        typedef typename __iterator_traits<iterator_type>::iterator_category    iterator_category;
private:
        iterator_type                                                           __current;
public:
        __reverse_iterator(): __current() {}
        explicit __reverse_iterator(iterator_type __x): __current(__x) {}
        __reverse_iterator(const __reverse_iterator& __x): __current(__x.__current) { }
        template <typename _Iter>
        __reverse_iterator(const __reverse_iterator<_Iter>& __i): __current(__i.base()) {}
        const iterator_type& base() const { return __current; }

        reference   operator*() const {
            pointer tmp = __current;
            return *--tmp;
        }
        pointer     operator->() const {
            return &(operator*());
        }
        __reverse_iterator&  operator++() {
            --__current;
            return *this;
        }
        __reverse_iterator    operator++(int) {
            return __reverse_iterator(__current--);
        }
        __reverse_iterator&  operator--() {
            ++__current;
            return *this;
        }
        __reverse_iterator   operator--(int) {
            return __reverse_iterator(__current++);
        }
        __reverse_iterator     operator+(difference_type __n) {
            return __reverse_iterator(__current - __n);
        }
        __reverse_iterator&    operator+=(difference_type __n) {
            __current -= __n;
            return *this;
        }
        __reverse_iterator&    operator-=(difference_type __n) {
            __current += __n;
            return *this;
        }
        __reverse_iterator&    operator-(difference_type __n) {
            return __reverse_iterator(__current + __n);
        }
        reference    operator[](difference_type __n) const {
            return *(*this + __n);
        }
};

template <typename _Iterator>
bool operator==(const __reverse_iterator<_Iterator>& x, const __reverse_iterator<_Iterator>& y) { return x.base() == y.base(); }
template <typename _Iterator>
bool operator!=(const __reverse_iterator<_Iterator>& x, const __reverse_iterator<_Iterator>& y) { return x.base() != y.base(); }
template <typename _Iterator>
bool operator>(const __reverse_iterator<_Iterator>& x, const __reverse_iterator<_Iterator>& y) { return x.base() > y.base(); }
template <typename _Iterator>
bool operator<(const __reverse_iterator<_Iterator>& x, const __reverse_iterator<_Iterator>& y) { return x.base() < y.base(); }
template <typename _Iterator>
bool operator>=(const __reverse_iterator<_Iterator>& x, const __reverse_iterator<_Iterator>& y) { return x.base() >= y.base(); }
template <typename _Iterator>
bool operator<=(const __reverse_iterator<_Iterator>& x, const __reverse_iterator<_Iterator>& y) { return x.base() <= y.base(); }
template <typename _Iterator>
typename __iterator_traits<_Iterator>::difference_type operator-(const __reverse_iterator<_Iterator>& x, const __reverse_iterator<_Iterator>& y) { return x.base() - y.base(); }

#endif // VECTOR_HPP
