#ifndef VECTORCPP
#define VECTORCPP
#include "Vector.hpp" 
#include <stdexcept>

template <typename T>
Vector<T>::Vector() : data_{nullptr}, capacity_{0}, size_{0}{}

template <typename T>
Vector<T>::Vector(size_t size) : data_{nullptr}, capacity_{size}, size_{size} {}

template <typename T>
Vector<T>::Vector(size_t size, const T& value) : capacity_{size}, size_{size} {
    data_ = new T[capacity_];
    for(int i = 0; i < size_; ++i) {
        data_[i] = value;
    }
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other) : capacity_{other.capacity_}, size_{other.size_} {
    data_ = new T[capacity_];
    for(int i = 0; i < capacity_; ++i) {
        data_[i] = other.data_[i];
    } 
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept : capacity_{other.capacity_}, size_{other.size_} {
    data_ = other.data_;
    other.data_ = nullptr;
}

template <typename T>
Vector<T>::~Vector() {
    capacity_ = 0;
    size_ = 0;
    delete[] data_;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init) {
    capacity_ = init.size();
    size_ = init.size();
    data_ = new T[capacity_];
    int i = 0;
    for(const T& it : init) {
        data_[i++] = it;
    }
}

template <typename T> 
Vector<T>& Vector<T>::operator= (Vector&& other) noexcept {
    if(this == &other) {
        return *this;
    }
    capacity_ = other.capacity_;
    size_ = other.size_;
    delete[] data_;
    data_ = other.data_;
    other.data_ = nullptr;
    return *this;
}

template <typename T> 
Vector<T>& Vector<T>::operator= (std::initializer_list<T> init) {
    capacity_ = init.size();
    size_ = init.size();
    delete[] data_;
    data_ = new T[capacity_];
    int i = 0;
    for(const T& it : init) {
        data_[i++] = it;
    }
    return *this;
}

template <typename T> 
Vector<T>& Vector<T>::operator= (const Vector& other) {
    if(this == &other) {
        return *this;
    }
    capacity_ = other.capacity_;
    size_ = other.size_;
    delete[] data_;
    data_ = new T[capacity_];
    for(int i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
    return *this;
}

template <typename T>
void Vector<T>::assign(size_t count, const T& val) {
    *this = Vector<T>(count, val);
}

template <typename T>
void Vector<T>::assign(std::initializer_list<T> init) {
    *this = Vector<T>(init);
}

template <typename T>
const T& Vector<T>::at(size_t pos) const {
    if(pos >= size_) {
        throw std::out_of_range();
    }
    return data_[pos];
}

template <typename T>
T& Vector<T>::at(size_t pos) {
    if(pos >= size_) {
        throw std::out_of_range();
    }
    return data_[pos];
}

template <typename T>
const T& Vector<T>::operator[] (size_t pos) const {
    return data_[pos];
}

template <typename T>
T& Vector<T>::operator[] (size_t pos) {
    return data_[pos];
}

template <typename T>
const T& Vector<T>::front() const {
    return data_[0];
}

template <typename T>
T& Vector<T>::front() {
    return data_[0];
}

template <typename T>
const T& Vector<T>::back() const {
    return data_[size_ - 1];
}

template <typename T>
T& Vector<T>::back() {
    return data_[size_ - 1];
}

template <typename T> 
T* Vector<T>::data() {
    return data_;
}

template <typename T> 
const T* Vector<T>::data() const {
    return data_;
}

#endif