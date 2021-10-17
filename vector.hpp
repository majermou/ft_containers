/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:16:22 by majermou          #+#    #+#             */
/*   Updated: 2021/10/17 17:16:52 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "enable_if.hpp"
#include "is_integral.hpp"
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
        pointer             __buff;
        size_type           __capacity;
        size_type           __size;
        allocator_type      __allocator;

        void        reallocate(void)
        {
            size_type       newCapacity = (!__capacity) ? 1 : 2 * __capacity;
            value_type      *ptr = __allocator.allocate(newCapacity);

            for (size_type i = 0; i < __size; i++)
                ptr[i] = __buff[i];
            __allocator.deallocate(__buff, __capacity);
            __buff = ptr;
            __capacity = newCapacity;
        }
public:
        explicit vector (): __buff(NULL), __capacity(0), __size(0) {}
        explicit vector(size_type n): __capacity(n), __size(0) {
            __buff = __allocator.allocate(__capacity);
            for (size_type i = 0; i < n; ++i) {
                __buff[__size++] = value_type();
            }
        }
        explicit vector (size_type n, const value_type& val): __capacity(n), __size(0) {
            __buff = __allocator.allocate(__capacity);
            for (size_type i = 0; i < n; ++i) {
                __buff[__size++] = val;
            }
        }
        template <class InputIterator>
        vector (InputIterator first, InputIterator last,
                typename enable_if<!is_integral<InputIterator>::value, bool>::type = true): __capacity(last - first), __size(0) {
            __buff = __allocator.allocate(__capacity);
            while (first != last)
                __buff[__size++] = *first++;
        }
        vector (const vector& x): __capacity(x.size()), __size(0) {
            __buff = __allocator.allocate(__capacity);
            for (size_type i = 0; i < x.size(); ++i) {
                __buff[__size] = x[__size];
                ++__size;
            }
        }
        ~vector () {
            __allocator.destroy(__buff);
            __allocator.deallocate(__buff, __capacity);
            __size = 0;
        }
        vector& operator= (const vector& x) {
            __capacity = x.size();
            __size = 0;
            __buff = __allocator.allocate(__capacity);
            for (size_type i = 0; i < x.size(); ++i) {
                __buff[__size] = x[__size];
                ++__size;
            }
            return *this;
        }

        iterator begin() {
            return iterator(__buff);
        }
        const_iterator  begin() const {
            return const_iterator(__buff);
        }
        iterator end() {
            return iterator(__buff + __size);
        }
        const_iterator  end() const {
            return const_iterator(__buff + __size);
        }
        reverse_iterator rbegin() {
            return reverse_iterator(__buff + __size);
        }
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(__buff + __size);
        }
        reverse_iterator rend() {
            return reverse_iterator(__buff);
        }
        const_reverse_iterator rend() const {
            return const_reverse_iterator(__buff);
        }

        size_type   size() const {
            return __size;
        }
        size_type   max_size() const {
            return __allocator.max_size();
        }
        void        resize (size_type n) {
            if (n < __size)
                __size = n;
            else if (n > __size) {
                if (n > __capacity) {
                    __capacity = n;
                    value_type* ptr = __allocator.alloc(__capacity);
                    for (size_type i = 0; i < __size; i++)
                        ptr[i] = __buff[i];
                    __allocator.deallocate(__buff, __capacity);
                    __buff = ptr;
                }
                for (__size; __size < n; ++__size)
                    __buff[__size] = value_type(0);
            }
        }
        void resize (size_type n, value_type val = value_type()){
            if (n < __size)
                __size = n;
            else if (n > __size) {
                if (n > __capacity) {
                    __capacity = n;
                    value_type* ptr = __allocator.allocate(__capacity);
                    for (size_type i = 0; i < __size; i++)
                        ptr[i] = __buff[i];
                    __allocator.deallocate(__buff, __capacity);
                    __buff = ptr;
                }
                for (; __size < n; ++__size)
                    __buff[__size] = val;
            }
        }
        size_type   capacity() const {
            return __capacity;
        }
        bool        empty() const {
            return((!__size) ? true: false);
        }
        void reserve (size_type n)
        {
            if (n > __capacity)
            {
                value_type      *ptr = __allocator.allocate(n);
                for (size_type i = 0; i < __size; i++)
                    ptr[i] = __buff[i];
                __allocator.deallocate(__buff, __capacity);
                __buff = ptr;
                __capacity = n;
            }
        }

        value_type&     operator[](size_type n) {
            return __buff[n];
        }
        const value_type&   operator[](size_type n) const {
            return __buff[n];
        }
        value_type&     at(size_type n)
        {
            if (n >= __size)
                throw std::out_of_range("-");
            return __buff[n];
        }
        const value_type&    at (size_type n) const
        {
             if (n >= __size)
                throw std::out_of_range("-");
            return __buff[n];
        }
        value_type&     front() {
            return __buff[0];
        }
        const value_type&   front() const {
            return __buff[0];
        }
        value_type&          back() {
            return __buff[__size - 1];
        }
        const value_type&    back() const {
            return __buff[__size - 1];
        }

        template <class InputIterator>
        void assign (InputIterator first, InputIterator last,
                     typename enable_if<!is_integral<InputIterator>::value, bool>::type = true) {
            size_type rangeLength = static_cast<size_type>(last - first);
            __allocator.destroy(__buff);
            if (rangeLength > __capacity) {
                __capacity = rangeLength;
                __allocator.deallocate(__buff, __capacity);
                __buff = __allocator.allocate(__capacity);
            }
            for (__size = 0; __size < rangeLength; ++__size) { 
                __buff[__size] = *first++;
            }
        }
        void assign (size_type n, const value_type& val) {
            __allocator.destroy(__buff);
            if (n > __capacity) {
                __capacity = n;
                __allocator.deallocate(__buff, __capacity);
                __buff = __allocator.allocate(__capacity);
            }
            for (__size = 0; __size < n; ++__size) {
                __buff[__size] = val;
            }
        }
        void        push_back (const value_type& val)
        {
            if (__size + 1 >= __capacity)
                reallocate();
            __buff[__size++] = val;
        }
        void pop_back() {
            --__size;
        }
        iterator insert (iterator position, const value_type& val) {
            size_type dealloc = __capacity;
            if (__size + 1 > __capacity) {
                pointer tmp = __allocator.allocate(__size + 1);
                iterator it = begin();
                iterator ite = end();
                __size = 0;
                while (it < position)
                    tmp[__size++] = *it++;
                tmp[__size++] = val;
                while (it < ite) {
                    tmp[__size++] = *it++;
                }
                __allocator.deallocate(__buff, dealloc);
                __buff = tmp;
            } else {
                value_type prev_val = val, tmp;
                iterator it = position;
                iterator ite = end();
                while (it != ite) {
                    tmp = *it;
                    *it = prev_val;
                    prev_val = tmp;
                    it++;
                }
                __size += 1;
            }
            return begin();
        }
        void insert (iterator position, size_type n, const value_type& val) {
            size_type dealloc = __capacity;
            (__size + n > __capacity) ? __capacity = __size + n : __capacity;
            pointer tmp = __allocator.allocate(__capacity);
            iterator it = begin();
            iterator ite = end();
            __size = 0;
            while (it < position) {
                tmp[__size++] = *it++;
            }
            for (size_t i = 0; i < n; i++) {
                tmp[__size++] = val;
            }
            while (it < ite) {
                tmp[__size++] = *it++;
            }
            __allocator.deallocate(__buff, dealloc);
            __buff = tmp;
        }
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last,
                    typename enable_if<!is_integral<InputIterator>::value, bool>::type = true) {
            size_type dealloc = __capacity;
            (__size + static_cast<size_type>(last - first) > __capacity) ? __capacity = __size + static_cast<size_type>(last - first) : __capacity;
            pointer tmp = __allocator.allocate(__capacity);
            iterator it = begin();
            iterator ite = end();
            __size = 0;
            while (it < position) {
                tmp[__size++] = *it++;
            }
            while (first != last) {
                tmp[__size++] = *first++;
            }
            while (it < ite) {
                tmp[__size++] = *it++;
            }
            __allocator.deallocate(__buff, dealloc);
            __buff = tmp;
        }
        iterator erase (iterator position) {
            iterator it = position;
            iterator ite = end();
            while (it + 1 != ite) {
                *it = *(it + 1);
                it++;
            }
            __size -= 1;
            return position;
        }
        iterator erase (iterator first, iterator last) {
            iterator ite = end();
            __size -= static_cast<size_type>(last -first);
            iterator it = first;
            while (last != ite) {
                *it++ = *last++; 
            }
            return first;
        }
        void swap (vector& x) {
            value_type  tmp;
            if (x.size() > __capacity) {
                reserve(x.size());
            }
            if (__size > x.capacity()) {
                x.reserve(__size);
            }
            size_type sz = size();
            resize(x.size(), value_type());
            x.resize(sz, value_type());
            for (size_t i = 0; i < __size || i < x.size(); i++) {
                tmp = x[i];
                if (i < __size)
                    x[i] = __buff[i];
                if (i < x.size())
                    __buff[i] = tmp;
            }
        }
        void clear() {
            __allocator.destroy(__buff);
            __size = 0;
        }
        allocator_type get_allocator() const {
            return __allocator;
        }
};  // vector class

template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template<typename T, typename Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
    T           val;
    if (x.size() > y.capacity())
        y.reserve(x.size());
    if (y.size() > x.capacity())
        x.reserve(y.size());
    size_t      sz = y.size();
    y.resize(x.size(), T());
    x.resize(sz, T());
    for (size_t i = 0; i < y.size() || i < x.size(); i++)
    {
        val = x[i];
        if (i < x.size()) {
            x[i] = y[i];
        }
        if (i < y.size()) {
            y[i] = val;
        }
    }
}
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
        reference    operator[](difference_type __n) const {
            return __current[__n];
        }
        __normal_iterator&    operator+=(difference_type __n) {
            __current += __n;
            return *this;
        }
        __normal_iterator     operator+(difference_type __n) {
            return __normal_iterator(__current + __n);
        }
        __normal_iterator&    operator-=(difference_type __n) {
            __current -= __n;
            return *this;
        }
        __normal_iterator   operator-(difference_type __n) const {
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
typename iterators_traits<_Iterator>::difference_type operator-(const __normal_iterator<_Iterator>& x, const __normal_iterator<_Iterator>& y) { return x.base() - y.base(); }

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
