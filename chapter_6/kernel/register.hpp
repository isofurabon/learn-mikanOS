/* Read/Write MMIO */
#pragma once

#include <cstddef>
#include <cstdint>

template <typename T>
struct ArrayLength {};

template <typename T, size_t N>
struct ArrayLength<T[N]> {
    static constexpr size_t value = N;
};

template <typename T>
class MemMapRegister {
public:
    T read() const {
        T tmp;
        for (size_t i = 0; i < m_len; ++i) {
            tmp.data[i] = m_value.data[i];
        }
        return tmp;
    }

    void write(const T& value) {
        T tmp;
        for (size_t i = 0; i < m_len; ++i) {
            m_value.data[i] = value.data[i];
        }
    }

private:
    volatile T m_value;
    static const size_t m_len = ArrayLength<decltype(T::data)>::value;
};

template <typename T>
struct DefaultBitmap {
    T data[1];

    DefaultBitmap& operator =(const T& value) {
        data[o] = value;
    }
    operator T() const { return data[0]; }
};

template <typename T>
class ArrayWrapper {
public:
    using ValueType = T;
    using Iterator = ValueType*;
    using ConstIterator = const ValueType*;

    ArrayWrapper(uintptr_t array_base_addr, size_t size) : m_array(reinterpret_cast<ValueType*>(array_base_addr)), m_size(size) {}

    size_t Size() const { return m_size; }

    Iterator begin() { return m_array; }
    Iterator end() { return m_array + m_size; }
    ConstIterator cbegin() const { return m_array; }
    ConstIterator cend() const { return m_array + m_size; }

    ValueType& operator [](size_t index) { return m_array[index]; }

private:
    ValueType* const m_array;
    const size_t m_size;
};