#ifndef VECTORHPP
#define VECTORHPP
#include <cstddef>
#include <initializer_list>

template <typename T>
class Vector {
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;
    using const_pointer = const T*;

    Vector() noexcept;
    explicit Vector(size_type size, const_reference value = T());
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector(std::initializer_list<T>);
    ~Vector();

    Vector& operator= (Vector&& other) noexcept; 
    Vector& operator= (std::initializer_list<T> &init);
    Vector& operator= (const Vector& other); 

    void assign(size_type count, const_reference val);
    void assign(std::initializer_list<T> init);

    const_reference at(size_type pos) const;
    reference at(size_type pos);
    const_reference operator[] (size_type pos) const;
    reference operator[] (size_type pos);

    const_reference front() const;
    reference front();
    const_reference back() const;
    reference back();
    pointer data();
    const_pointer data() const;

    bool empty() const noexcept;
    size_type size() const noexcept;
    void reserve(size_type cap);
    size_type capacity() const noexcept;
    void shrink_to_fit();
    
    void swap(Vector<T>& other) noexcept;
    void clear();
    void insert(size_type pos, const_reference val);
    void insert(size_type pos, T&& val);
    void insert(size_type pos, size_type count, const_reference val);
    template <typename... Args>
    void emplace(size_type pos, Args&&... args);
    void erase(size_type pos);
    void erase(size_type pos1, size_type pos2);
    void push_back(const_reference val);
    void push_back(T&& val);
    void pop_back(const_reference val);
    void resize(size_type size, const_reference val= T());
    template <typename...Args>
    void emplace_back(Args&&...);

private:
    pointer data_;
    size_type size_;
    size_type capacity_;
};

    template <typename U>
    bool operator== (const Vector<U>& lhs, const Vector<U>& rhs);
    template <typename U>
    bool operator!= (const Vector<U>& lhs, const Vector<U>& rhs);
    template <typename U>
    bool operator<= (const Vector<U>& lhs, const Vector<U>& rhs);
    template <typename U>
    bool operator>= (const Vector<U>& lhs, const Vector<U>& rhs);
    template <typename U>
    bool operator< (const Vector<U>& lhs, const Vector<U>& rhs);
    template <typename U>
    bool operator> (const Vector<U>& lhs, const Vector<U>& rhs);
    template <typename U>
    void swap (Vector<U>& lhs, Vector<U>& rhs) noexcept;
    template <typename U>
    size_t erase(const Vector<U>& lhs, const U&) noexcept;

#include "../source/Vector.cpp" 
#endif