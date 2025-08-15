#ifndef VECTORCPP
#define VECTORCPP
#include "Vector.hpp" 
#include <stdexcept>
#include <utility>

template <typename T>
Vector<T>::Vector() : data_{nullptr}, capacity_{0}, size_{0}{}

template <typename T>
Vector<T>::Vector(size_type size) : data_{nullptr}, capacity_{size}, size_{size} {
    data_ = new value_type[capacity_];
}

template <typename T>
Vector<T>::Vector(size_t size, const_reference value) : capacity_{size}, size_{size} {
    data_ = new value_type[capacity_];
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
    data_ = nullptr;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init) {
    capacity_ = init.size();
    size_ = init.size();
    data_ = new value_type[capacity_];
    int i = 0;
    for(const_reference it : init) {
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
    data_ = new value_type[capacity_];
    int i = 0;
    for(const_reference it : init) {
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
    data_ = new value_type[capacity_];
    for(int i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
    return *this;
}

template <typename T>
void Vector<T>::assign(size_t count, const_reference val) {
    *this = Vector<T>(count, val);
}

template <typename T>
void Vector<T>::assign(std::initializer_list<T> init) {
    *this = Vector<T>(init);
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type pos) const {
    if(pos >= size_) {
        throw std::out_of_range();
    }
    return data_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
    if(pos >= size_) {
        throw std::out_of_range();
    }
    return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::operator[] (size_type pos) const {
    return data_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[] (size_type pos) {
    return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
    return data_[0];
}

template <typename T>
typename Vector<T>::reference Vector<T>::front() {
    return data_[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
    return data_[size_ - 1];
}

template <typename T>
typename Vector<T>::reference Vector<T>::back() {
    return data_[size_ - 1];
}

template <typename T> 
typename Vector<T>::pointer Vector<T>::data() {
    return data_;
}

template <typename T> 
const typename Vector<T>::pointer Vector<T>::data() const {
    return data_;
}

template <typename T>
bool Vector<T>::empty() const {
    return  size_ == 0;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const {
    return size_;
}

template <typename T>
void Vector<T>::reserve(size_type cap) {
    if(cap <= capacity_) {
        return;
    }
    Vector<T> tmp(cap);
    for(int i = 0; i < size_; ++i) {
        tmp.data_[i] = data_[i];
    }
    tmp.size_ = size_;
    this->swap(tmp);
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const {
    return capacity_;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if(capacity_ == size_) {
        return;
    }
    Vector<T> tmp(size_);
    for(int i = 0; i < size_; ++i) {
        tmp[i] = data_[i];
    }
    tmp.size_ == size_;
    swap(tmp, *this);
}

template <typename T>
void Vector<T>::swap(Vector<T>& other) noexcept {
    size_type tmp = capacity_;
    capacity_ = other.capacity_;
    other.capacity_ = tmp;
    tmp = size_;
    size_ = other.size_;
    other.size_ = tmp;
    Vector<T>::pointer t = data_;
    data_ = other.data_;
    other.data_ = t;
    t = nullptr;
}

template <typename T>
void Vector<T>::clear() {
    size_ = 0;
}

template <typename T>
void Vector<T>::insert(size_type pos, const_reference val) {
    if(pos > size_) {
        throw std::out_of_range();
    }
    if(capacity_ == 0) {
        data_ = new T[1];
        data_[0] = val;
        capacity_ = 1;
        size_ = 1;
        return;
    }
    if(capacity_ == size_) { 
        reserve(capacity_ * 2); 
    } 
    for(int i = size_; i > pos; --i) {
        data_[i] = data_[i - 1]; 
    } 
    ++size_;
    data_[pos] = val;
}

template <typename T>
void Vector<T>::insert(size_type pos, reference& val) {
    if(pos > size_) {
        throw std::out_of_range();
    }
    if(capacity_ == 0) {
        data_ = new T[1];
        data_[0] = val;
        capacity_ = 1;
        size_ = 1;
        return;
    }
    if(capacity_ == size_) { 
        reserve(capacity_ * 2); 
    } 
    for(int i = size_; i > pos; --i) {
        data_[i] = data_[i - 1]; 
    } 
    ++size_;
    data_[pos] = std::move(val);
}

template <typename T>
void Vector<T>::insert(size_type pos, size_type count, const_reference val) {
    if(pos > size_) {
        throw std::out_of_range();
    }
    if(capacity_ == 0) {
        *this = Vector<int>(count, val);
        return;
    }
    if(capacity_ <= size_ + count) { 
        reserve(capacity_ * 2 + count); 
    } 
    for(int i = size_ + count - 1; i > pos; --i) {
        data_[i] = data_[i - 1]; 
    } 
    size_ += count;
    for(int i = pos; i < pos + count; ++i) {
        data_[i] = val; 
    }
}

template <typename T>
template <typename... Args>
void Vector<T>::emplace(size_type pos, Args&&... args) {
    insert(pos, T(std::forward<Args>(args)...));
}

template <typename T>
void Vector<T>::erase(size_type pos) {
    if(pos >= size_) {
        throw std::out_of_range();
    }
    for(int i = pos; i < size_ - 1; ++i) {
        data_[i] = data_[i + 1];
    }
    size_--;
}

template <typename T>
void Vector<T>::erase(size_type pos1, size_type pos2) {
    for(int i = pos1; i < size_; ++i) {
        erase(i);
    }
}

template <typename T>
void Vector<T>::push_back(const_reference val) {
    insert(size_, val);
}

template <typename T>
void Vector<T>::pop_back(const_reference val) {
    erase(size_ - 1);
}

template <typename T>
void Vector<T>::resize(size_type size) {
    if(size == size_) {
        return;
    }
    else if(size < size_) {
        erase(size, size_);
    }
    else {
        reserve(size);
        size_ = capacity_;
    }
}

template <typename T>
void Vector<T>::resize(size_type size, const_reference val) {
    if(size == size_) {
        return;
    }
    else if(size < size_) {
        erase(size, size_);
    }
    else {
        reserve(size);
        size_ = capacity_;
        for(int i = 0; i < size_; ++i) {
            data_[i] = val;
        }
    }
}

template <typename T>
template <typename...Args>
void Vector<T>::emplace_back(Args&&... args) {
    insert(size_ - 1, value_type(std::forward<Args>(args)...));
}

#endif