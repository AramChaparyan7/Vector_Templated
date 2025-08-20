#ifndef VECTORCPP
#define VECTORCPP
#include "../includes/Vector.hpp" 
#include <stdexcept>
#include <utility>
#include <memory>

template <typename T>
Vector<T>::Vector() noexcept : data_{nullptr}, capacity_{0}, size_{0} {}

template <typename T>
Vector<T>::Vector(size_type size, const_reference value) : Vector{} {
    data_ = static_cast<T*>(operator new(sizeof(T) * size_));
    size_type i = 0;
    try {
        for(; i < size; ++i) {
            new (&data_[i]) T(value);
        }
        size_ = capacity_ = size;
    }
    catch (...) {
        for(size_type j = 0; j < i; ++j) {
            data_[j].~T();
        }
        operator delete(data_);
        throw;
    }
}


template <typename T>
Vector<T>::Vector(const Vector<T>& other) : Vector{} {
    data_ = static_cast<T*>(operator new(sizeof(T) * other.capacity_));
    size_type i = 0;
    try {
        std::uninitialized_copy_n(other.data_, other.size_, data_);
        capacity_ = other.capacity_;
        size_ = other.size_;
    }
    catch (...) {
        operator delete(data_);
        throw;
    }
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) noexcept : capacity_{other.capacity_}, size_{other.size_} {
    data_ = other.data_;
    other.data_ = nullptr;
}

template <typename T>
Vector<T>::~Vector() {
    clear();
    operator delete(data_);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init) {
    data_ = static_cast<T*>(operator new(sizeof(T) * init.size()));
    try {
        std::uninitialized_copy(init.begin(), init.end(), data_);
        capacity_ = size_ = init.size();
    }
    catch (...) {
        operator delete(data_);
        throw;
    }
}

template <typename T> 
Vector<T>& Vector<T>::operator= (Vector&& other) noexcept {
    if(this == &other) {
        return *this;
    }
    Vector<T> tmp(std::move(other));
    swap(tmp);
    return *this;
}

template <typename T> 
Vector<T>& Vector<T>::operator= (std::initializer_list<T>& init) {
    Vector<T> tmp(init);
    swap(tmp);
    return *this;
}

template <typename T> 
Vector<T>& Vector<T>::operator= (const Vector& other) {
    if(this == &other) {
        return *this;
    }
    Vector<T> tmp(other);
    swap(tmp);
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
        throw std::out_of_range("Wrong argument");
    }
    return data_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
    if(pos >= size_) {
        throw std::out_of_range("Wrong argument");
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
typename Vector<T>::const_pointer Vector<T>::data() const {
    return data_;
}

template <typename T>
bool Vector<T>::empty() const noexcept {
    return  size_ == 0;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const noexcept {
    return size_;
}

template <typename T>
void Vector<T>::reserve(size_type cap) {
    if(cap <= capacity_) {
        return;
    }
    T *new_data = static_cast<T*>(operator new(sizeof(T) * cap));
    size_type i = 0;
    try {
        for(; i < size_; ++i) {
            new (&new_data[i]) T(data_[i]);
        }
    }
    catch (...) {
        for(size_type j = 0; j < i; ++j) {
            new_data[j].~T();
        }
        operator delete(new_data);
        throw;
    }
    size_type tmp = size_;
    clear();
    operator delete(data_);
    data_ = new_data;
    capacity_ = cap;
    size_ = tmp;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept {
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
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(data_, other.data_);
}

template <typename T>
void Vector<T>::clear() {
    for(int i = 0; i < size_; ++i) {
        data_[i].~T();
    }
    size_ = 0;
}

template <typename T>
void Vector<T>::insert(size_type pos, const_reference val) {
    if(pos == size_) {
        push_back(val);
        return;
    }
    if(capacity_ == size_) { 
        reserve(capacity_ * 2); 
    } 
    size_type i = size_;
    for(; i > pos; --i) {
        new (&data_[i]) T(std::move(data_[i - 1])); 
    } 
    new (&data_[pos]) T(val);
    ++size_;
}

template <typename T>
void Vector<T>::insert(size_type pos, T&& val) {
    if(pos == size_) {
        push_back(val);
        return;
    }
    if(capacity_ == size_) { 
        reserve(capacity_ * 2); 
    } 
    size_type i = size_;
    for(; i > pos; --i) {
        new (&data_[i]) T(std::move(data_[i - 1])); 
    } 
    new (&data_[pos]) T(std::move(val));
    ++size_;
}

template <typename T>
void Vector<T>::insert(size_type pos, size_type count, const_reference val) {
    if(capacity_ < size_ + count) { 
        reserve(2 * (count + size_)); 
    } 
    for(size_type i = size_ + count; i >= pos + count; --i) {
        new (&data_[i]) T(std::move(data_[i - count]));
    } 
    size_type tmp = pos;
    while(count--) {
        new (&data_[pos++]) T(val);
    }
}

template <typename T>
template <typename... Args>
void Vector<T>::emplace(size_type pos, Args&&... args) {
    insert(pos, T(std::forward<Args>(args)...));
}

template <typename T>
void Vector<T>::erase(size_type pos) {
    data_[pos].~T();
    for(int i = pos; i < size_ - 1; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }
    --size_;
}

template <typename T>
void Vector<T>::erase(size_type pos1, size_type pos2) {
    for(size_type i = pos1; i < pos2; ++i) {
        data_[i].~T();
    }
    for(size_type i = pos1; i < size_ - pos2 + pos1; ++i) {
        new (&data_[i]) T(std::move(data_[i + pos1 - pos2]));
    }
    size_ -= pos2 - pos1;
}

template <typename T>
void Vector<T>::push_back(const_reference val) {
    if(capacity_ == size_) { 
        reserve(capacity_ == 0 ? 1 : capacity_ * 2); 
    } 
    ++size_;
    data_[size_ - 1] = val;
}

template <typename T>
void Vector<T>::push_back(T&& val) {
    if(capacity_ == size_) { 
        reserve(capacity_ == 0 ? 1 : capacity_ * 2); 
    } 
    ++size_;
    data_[size_ - 1] = std::move(val);
}

template <typename T>
void Vector<T>::pop_back(const_reference val) {
    erase(size_ - 1);
}


template <typename T>
void Vector<T>::resize(size_type size, const_reference val) {
    if(size == size_) {
        return;
    }
    if(size < size_) {
        for(size_type i = size; i < size_; ++i) {
            data_[i].~T();
        }
    }
    else {
        if(size > capacity_) {
            reserve(capacity_ * 2);
        }
        std::uninitialized_fill_n(data_ + size_, size - size_, val);
    }
    size_ = size;
}

template <typename T>
template <typename...Args>
void Vector<T>::emplace_back(Args&&... args) {
    if(capacity_ == size_) { 
        reserve(capacity_ * 2); 
    } 
    ++size_;
    new (&data_[size_]) T(std::forward<Args>(args)...);
}

template <typename T>
bool operator== (const Vector<T>& lhs, const Vector<T>& rhs) {
    if(lhs.size() != rhs.size()) {
        return false;
    }
    for(int i = 0; i < lhs.size(); ++i) {
        if(lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator!= (const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs==rhs);
}

template <typename T>
bool operator< (const Vector<T>& lhs, const Vector<T>& rhs){
    int size = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
    for(int i = 0; i < size; ++i) {
        if(lhs[i] > rhs[i]) {
            return false;
        }else if(lhs[i] < rhs[i]) {
            return true;
        }
    }
    return lhs.size() < rhs.size();
}

template <typename T>
bool operator> (const Vector<T>& lhs, const Vector<T>& rhs){
    return !(lhs <= rhs);
}

template <typename T>
bool operator<= (const Vector<T>& lhs, const Vector<T>& rhs){
    return lhs < rhs || lhs == rhs;
}

template <typename T>
bool operator>= (const Vector<T>& lhs, const Vector<T>& rhs){
    return !(lhs < rhs);
}

template <typename T>
void swap (Vector<T>& lhs, Vector<T>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename T>
typename Vector<T>::size_type erase(const Vector<T>& vec, typename Vector<T>::const_reference value) {
    for(int i = 0; i < vec.size(); ++i) {
        if(vec[i] == value) {
            vec.erase(vec[i]);
        }
    }
}

#endif