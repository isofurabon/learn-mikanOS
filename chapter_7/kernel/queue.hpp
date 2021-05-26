#pragma once

#include <cstddef>
#include <array>

#include "error.hpp"

template <typename T>
class ArrayQueue {
public:
    template <size_t N>
    ArrayQueue(std::array<T, N>& buf);
    ArrayQueue(T* buf, size_t size);
    Error Push(const T& value);
    Error Pop();
    size_t Count() const;
    size_t Capacity() const;
    const T& Front() const;

private:
    T* m_data;
    size_t m_read_pos, m_write_pos, m_count;
    const size_t m_capacity;
};

// Constructors
template<typename T>
template<size_t N>
ArrayQueue<T>::ArrayQueue(std::array<T, N>& buf)
    : ArrayQueue(buf.data(), N) {}

template<typename T> 
ArrayQueue<T>::ArrayQueue(T* buf, size_t size)
    : m_data{buf}, m_read_pos{0}, m_write_pos{0}, m_count{0}, m_capacity{size}{}

// Methods
template<typename T> 
Error ArrayQueue<T>::Push(const T& value) {
    if (m_count == m_capacity){
        return MAKE_ERROR(Error::kFull);
    }

    m_data[m_write_pos] = value;
    m_write_pos++;
    m_count++;
    if (m_write_pos == m_capacity){
        m_write_pos = 0;
    }

    return MAKE_ERROR(Error::kSuccess);
}

template<typename T> 
Error ArrayQueue<T>::Pop() {
    if (m_count == 0){
        return MAKE_ERROR(Error::kEmpty);
    }

    m_read_pos++;
    m_count--;
    if (m_read_pos == m_capacity){
        m_read_pos = 0;
    }

    return MAKE_ERROR(Error::kSuccess);
}

template<typename T> 
size_t ArrayQueue<T>::Count() const {
    return m_count;
}

template<typename T> 
size_t ArrayQueue<T>::Capacity() const {
    return m_capacity;
}

template<typename T> 
const T& ArrayQueue<T>::Front() const {
    return m_data[m_read_pos];
}