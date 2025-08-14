#ifndef VECTORHPP
#define VECTORHPP
#include <cstddef>
#include <initializer_list>

template <typename T>
class Vector {
public:
    using value_type = T;
    using ponter = T*;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;
    explicit Vector();
    Vector(size_t size);
    Vector(size_t size, const_reference value);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector(std::initializer_list<T>);
    ~Vector();
    Vector& operator= (Vector&& other) noexcept; 
    Vector& operator= (std::initializer_list<T> init);
    Vector& operator= (const Vector& other); 
    void assign(size_t count, const_reference val);
    void assign(std::initializer_list<T> init);
    const_reference at(size_t pos) const;
    T& at(size_t pos);
    const_reference operator[] (size_t pos) const;
    T& operator[] (size_t pos);
    const_reference front() const;
    T& front();
    const_reference back() const;
    T& back();
    T* data();
    const T* data() const;
    bool empty() const;
    size_t size() const;
    void reserve(size_t cap);
    size_t capacity() const;
    void shrink_to_fit();
    void swap(Vector<T>& other) noexcept;
    void clear();
    void insert(size_t pos, const_reference val);
    void insert(size_t pos, T&& val);
    void insert(size_t pos, size_t count, const_reference val);
    template <typename... Args>
    void emplace(size_t pos, Args&&... args);
    void erase(size_t pos);
    void erase(size_t pos1, size_t pos2);
    void push_back(const_reference val);
    void pop_back(const_reference val);
    void resize(size_t size);
    void resize(size_t size, const_reference);
    template <typename...Args>
    void emplace_back(Args&&...);
};

#include "Vector.cpp" 
#endif