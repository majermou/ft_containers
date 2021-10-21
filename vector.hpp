/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majermou <majermou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:16:22 by majermou          #+#    #+#             */
/*   Updated: 2021/10/21 14:00:13 by majermou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "equal.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "reverse_iterator.hpp"
#include "lexicographical_compare.hpp"

template <typename iterator> class normal_iterator;

namespace ft {

template < typename T, typename Alloc = std::allocator<T> >
class vector {

public:

        typedef T                                                   value_type;
        typedef Alloc                                               allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef normal_iterator<pointer>                            iterator;
        typedef normal_iterator<const_pointer>                      const_iterator;
        typedef ReverseIterator<iterator>                           reverse_iterator;
        typedef ReverseIterator<const_iterator>                     const_reverse_iterator;
        typedef ptrdiff_t                                           difference_type;
        typedef size_t                                              size_type;

private:

        typedef ft::vector<value_type>      Self;

        pointer             m_buff;
        size_type           m_capacity;
        size_type           m_size;
        allocator_type      m_allocator;

        void    reallocate(void)
        {
            size_type       newCapacity = (!m_capacity) ? 1 : 2 * m_capacity;
            value_type      *ptr = m_allocator.allocate(newCapacity);

            for (size_type i = 0; i < m_size; i++)
                ptr[i] = m_buff[i];
            m_allocator.deallocate(m_buff, m_capacity);
            m_buff = ptr;
            m_capacity = newCapacity;
        }

public:

    explicit vector(const allocator_type& alloc = allocator_type())
                    : m_buff(NULL), m_capacity(0), m_size(0), m_allocator(alloc) {
    }
    explicit vector(size_type n, const value_type& val,
                    const allocator_type& alloc = allocator_type())
                    : m_capacity(n), m_size(0), m_allocator(alloc) {
        m_buff = m_allocator.allocate(m_capacity);
        while (m_size < m_capacity) {
            m_buff[m_size++] = val;
        }
    }
    template <class InputIterator>
    vector(InputIterator first, InputIterator last,
            typename enable_if<!is_integral<InputIterator>::value, bool>::type = true,
            const allocator_type& alloc = allocator_type())
            : m_capacity(last - first), m_size(0), m_allocator(alloc) {
        m_buff = m_allocator.allocate(m_capacity);
        while (first != last)
            m_buff[m_size++] = *first++;
    }
    vector(const vector& x): m_capacity(x.size()), m_size(0), m_allocator(x.m_allocator) {
        m_buff = m_allocator.allocate(m_capacity);
        while (m_size < m_capacity) {
            m_buff[m_size] = x[m_size];
            ++m_size;
        }
    }
    ~vector () {
        m_allocator.deallocate(m_buff, m_capacity);
    }
    vector& operator= (const vector& x) {
        if (m_capacity < x.size()) {
            m_allocator.deallocate(m_buff, m_capacity);
            m_capacity = x.size();
            m_buff = m_allocator.allocate(m_capacity);
        }
        m_size = 0;
        while (m_size < x.size()) {
            m_buff[m_size] = x[m_size];
            ++m_size;
        }
        return *this;
    }

    iterator begin() {
        return iterator(m_buff);
    }
    const_iterator  begin() const {
        return const_iterator(m_buff);
    }
    iterator end() {
        return iterator(m_buff + m_size);
    }
    const_iterator  end() const {
        return const_iterator(m_buff + m_size);
    }
    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }
    reverse_iterator rend() {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    size_type   size() const {
        return m_size;
    }
    size_type   max_size() const {
        return m_allocator.max_size();
    }
    void resize(size_type n, value_type val = value_type()) {
        if (n < m_size)
            m_size = n;
        else if (n > m_size) {
            if (n > m_capacity) {
                value_type* ptr = m_allocator.allocate(n);
                for (size_type i = 0; i < m_size; i++)
                    ptr[i] = m_buff[i];
                m_allocator.deallocate(m_buff, m_capacity);
                m_capacity = n;
                m_buff = ptr;
            }
            for (; m_size < n; ++m_size)
                m_buff[m_size] = val;
        }
    }
    size_type   capacity() const {
        return m_capacity;
    }
    bool        empty() const {
        return (m_size == 0);
    }
    void reserve(size_type n) {
        if (n > m_capacity)
        {
            value_type      *ptr = m_allocator.allocate(n);
            for (size_type i = 0; i < m_size; i++)
                ptr[i] = m_buff[i];
            m_allocator.deallocate(m_buff, m_capacity);
            m_capacity = n;
            m_buff = ptr;
        }
    }

    value_type&     operator[](size_type n) {
        return m_buff[n];
    }
    const value_type&   operator[](size_type n) const {
        return m_buff[n];
    }
    value_type& at(size_type n) {
        if (n >= m_size)
            throw std::out_of_range("vector");
        return m_buff[n];
    }
    const value_type&   at(size_type n) const {
        if (n >= m_size)
            throw std::out_of_range("vector");
        return m_buff[n];
    }
    value_type& front() {
        return m_buff[0];
    }
    const value_type&   front() const {
        return m_buff[0];
    }
    value_type& back() {
        return m_buff[m_size - 1];
    }
    const value_type&   back() const {
        return m_buff[m_size - 1];
    }

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last,
                typename enable_if<!is_integral<InputIterator>::value, bool>::type = true) {
        size_type rangeLength = static_cast<size_type>(last - first);
        m_allocator.destroy(m_buff);
        if (rangeLength > m_capacity) {
            m_allocator.deallocate(m_buff, m_capacity);
            m_buff = m_allocator.allocate(rangeLength);
            m_capacity = rangeLength;
        }
        for (m_size = 0; m_size < rangeLength; ++m_size) { 
            m_buff[m_size] = *first++;
        }
    }
    void assign(size_type n, const value_type& val) {
        m_allocator.destroy(m_buff);
        if (n > m_capacity) {
            m_allocator.deallocate(m_buff, m_capacity);
            m_buff = m_allocator.allocate(n);
            m_capacity = n;
        }
        for (m_size = 0; m_size < n; ++m_size) {
            m_buff[m_size] = val;
        }
    }
    void    push_back(const value_type& val)
    {
        if (m_size + 1 > m_capacity)
            reallocate();
        m_buff[m_size++] = val;
    }
    void pop_back() {
        --m_size;
    }
    iterator    insert(iterator position, const value_type& val) {
        size_type capacityTodealloc = m_capacity;
        m_capacity = (m_size + 1 > m_capacity) ? m_size + 1 : m_capacity;
        pointer tmp = m_allocator.allocate(m_capacity);
        iterator it = begin();
        iterator ite = end();
        m_size = 0;
        while (it < position)
            tmp[m_size++] = *it++;
        tmp[m_size++] = val;
        while (it < ite) {
            tmp[m_size++] = *it++;
        }
        m_allocator.deallocate(m_buff, capacityTodealloc);
        m_buff = tmp;
        return begin();
    }
    void insert(iterator position, size_type n, const value_type& val) {
        size_type capacityTodealloc = m_capacity;
        m_capacity = (m_size + n > m_capacity) ? m_size + n : m_capacity;
        pointer tmp = m_allocator.allocate(m_capacity);
        iterator it = begin();
        iterator ite = end();
        m_size = 0;
        while (it < position) {
            tmp[m_size++] = *it++;
        }
        for (size_t i = 0; i < n; i++) {
            tmp[m_size++] = val;
        }
        while (it < ite) {
            tmp[m_size++] = *it++;
        }
        m_allocator.deallocate(m_buff, capacityTodealloc);
        m_buff = tmp;
    }
    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last,
                typename enable_if<!is_integral<InputIterator>::value, bool>::type = true) {
        size_type capacityTodealloc = m_capacity;
        m_capacity = (m_size + (last - first) > m_capacity) ? m_size + (last - first)  : m_capacity;
        pointer tmp = m_allocator.allocate(m_capacity);
        iterator it = begin();
        iterator ite = end();
        m_size = 0;
        while (it < position) {
            tmp[m_size++] = *it++;
        }
        while (first != last) {
            tmp[m_size++] = *first++;
        }
        while (it < ite) {
            tmp[m_size++] = *it++;
        }
        m_allocator.deallocate(m_buff, capacityTodealloc);
        m_buff = tmp;
    }
    iterator erase (iterator position) {
        iterator it = position;
        iterator ite = end();
        while (it + 1 != ite) {
            *it = *(it + 1);
            it++;
        }
        m_size -= 1;
        return position;
    }
    iterator erase (iterator first, iterator last) {
        iterator ite = end();
        m_size -= (last -first);
        iterator it = first;
        while (last != ite) {
            *it++ = *last++; 
        }
        return first;
    }
    void swap (vector& x) {
        pointer tmp = x.m_buff;
        size_type sz = x.m_size;
        size_type capacity = x.m_capacity;

        x.m_capacity = m_capacity;
        m_capacity = capacity;
        x.m_size = m_size;
        m_size = sz;
        x.m_buff = m_buff;
        m_buff = tmp;
    }
    void clear() {
        m_allocator.destroy(m_buff);
        m_size = 0;
    }
    allocator_type get_allocator() const {
        return allocator_type();
    }

};  // vector class

template <class T, class Alloc>
bool    operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return (lhs.size() != rhs.size()) ? false : equal(lhs.begin(), lhs.end(), rhs.begin());
}
template <class T, class Alloc>
bool    operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs == rhs);
}
template <class T, class Alloc>
bool    operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template <class T, class Alloc>
bool    operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs > rhs);
}
template <class T, class Alloc>
bool    operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return lexicographical_compare(rhs.begin(), rhs.end(),lhs.begin(), lhs.end());
}
template <class T, class Alloc>
bool    operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
    return !(lhs < rhs);
}
template<typename T, typename Alloc>
void    swap(vector<T,Alloc>& x, vector<T,Alloc>& y) {
    x.swap(y);
}

}   // namespace ft

template <typename iterator>
class normal_iterator {

public:

        typedef iterator                                                        iterator_type;
        typedef typename iterators_traits<iterator_type>::difference_type       difference_type;
        typedef typename iterators_traits<iterator_type>::value_type            value_type;
        typedef typename iterators_traits<iterator_type>::pointer               pointer;
        typedef typename iterators_traits<iterator_type>::reference             reference;
        typedef typename iterators_traits<iterator_type>::iterator_category     iterator_category;

private:

        iterator_type                                                           m_current;

public:

        normal_iterator(): m_current() {}
        explicit normal_iterator(iterator_type x): m_current(x) {}
        normal_iterator(const normal_iterator& x): m_current(x.m_current) {}
        template <typename iter>
        normal_iterator(const normal_iterator<iter>& i): m_current(i.base()) {}
        const iterator_type&    base() const {
            return m_current;
        }

        reference   operator*() const { 
            return *m_current;
        }
        pointer     operator->() const {
            return m_current;
        }
        normal_iterator&  operator++() {
            ++m_current;
            return *this;
        }
        normal_iterator    operator++(int) {
            return normal_iterator(m_current++);
        }
        normal_iterator&  operator--() {
            --m_current;
            return *this;
        }
        normal_iterator   operator--(int) {
            return normal_iterator(m_current--);
        }
        reference    operator[](difference_type n) const {
            return m_current[n];
        }
        normal_iterator&    operator+=(difference_type n) {
            m_current += n;
            return *this;
        }
        normal_iterator     operator+(difference_type n) {
            return normal_iterator(m_current + n);
        }
        normal_iterator&    operator-=(difference_type n) {
            m_current -= n;
            return *this;
        }
        normal_iterator   operator-(difference_type n) const {
            return normal_iterator(m_current - n);
        } 
};

template <typename iterator1, typename iterator2>
bool operator==(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return (x.base() == y.base());
}
template <typename iterator1, typename iterator2>
bool operator>(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return x.base() > y.base();
}
template <typename iterator1, typename iterator2>
bool operator<(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return x.base() < y.base();
}
template <typename iterator1, typename iterator2>
bool operator!=(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return !(x == y);
}
template <typename iterator1, typename iterator2>
bool operator>=(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return !(x < y);
}
template <typename iterator1, typename iterator2>
bool operator<=(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return !(x > y);
}
template <typename iterator1, typename iterator2>
typename normal_iterator<iterator1>::difference_type operator-(const normal_iterator<iterator1>& x, const normal_iterator<iterator2>& y) {
    return x.base() - y.base();
}
template<typename iterator>
normal_iterator<iterator>   operator+(typename normal_iterator<iterator>::difference_type n, const normal_iterator<iterator>& x) {
    return normal_iterator<iterator>(x.base() + n);
}

#endif // VECTOR_HPP
