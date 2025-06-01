#pragma once
#include <stdexcept>
#include <algorithm>

template <typename T>
class DynamicArray {
private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;

    void reallocate(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < m_size; ++i) {
            newData[i] = std::move(m_data[i]);
        }
        delete[] m_data;
        m_data = newData;
        m_capacity = newCapacity;
    }

public:
    DynamicArray() : m_data(new T[10]), m_size(0), m_capacity(10) {}
    DynamicArray(size_t initialCapacity) : m_data(new T[initialCapacity]), m_size(0), m_capacity(initialCapacity) {}
    DynamicArray(size_t count, const T& value) : m_data(new T[count]), m_size(count), m_capacity(count) {
        std::fill(m_data, m_data + count, value);
    }
    DynamicArray(const DynamicArray& other) : m_data(new T[other.m_capacity]), m_size(other.m_size), m_capacity(other.m_capacity) {
        std::copy(other.m_data, other.m_data + other.m_size, m_data);
    }
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] m_data;
            m_data = new T[other.m_capacity];
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            std::copy(other.m_data, other.m_data + other.m_size, m_data);
        }
        return *this;
    }
    ~DynamicArray() {
        delete[] m_data;
    }

    T& at(size_t index) {
        if (index >= m_size) throw std::out_of_range("Index out of range");
        return m_data[index];
    }
    const T& at(size_t index) const {
        if (index >= m_size) throw std::out_of_range("Index out of range");
        return m_data[index];
    }

    T& operator[](size_t index) { return m_data[index]; }
    const T& operator[](size_t index) const { return m_data[index]; }

    T& front() {
        if (empty()) throw std::underflow_error("Array is empty");
        return m_data[0];
    }
    const T& front() const {
        if (empty()) throw std::underflow_error("Array is empty");
        return m_data[0];
    }

    T& back() {
        if (empty()) throw std::underflow_error("Array is empty");
        return m_data[m_size - 1];
    }
    const T& back() const {
        if (empty()) throw std::underflow_error("Array is empty");
        return m_data[m_size - 1];
    }

    T* data_ptr() { return m_data; }
    const T* data_ptr() const { return m_data; }

    void push_back(const T& value) {
        if (m_size >= m_capacity) reallocate(static_cast<size_t>(m_capacity * 1.5) + 1);
        m_data[m_size++] = value;
    }
    void push_back(T&& value) {
        if (m_size >= m_capacity) reallocate(static_cast<size_t>(m_capacity * 1.5) + 1);
        m_data[m_size++] = std::move(value);
    }
    void pop_back() {
        if (empty()) throw std::underflow_error("Array is empty");
        --m_size;
    }
    void clear() { m_size = 0; }
    void resize(size_t newSize) {
        if (newSize > m_capacity) reserve(newSize);
        m_size = newSize;
    }
    void resize(size_t newSize, const T& value) {
        if (newSize > m_capacity) reserve(newSize);
        if (newSize > m_size) std::fill(m_data + m_size, m_data + newSize, value);
        m_size = newSize;
    }
    void reserve(size_t newCapacity) {
        if (newCapacity > m_capacity) reallocate(newCapacity);
    }
    void shrink_to_fit() {
        if (m_capacity > m_size) reallocate(m_size);
    }

    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }
    bool empty() const { return m_size == 0; }
    size_t max_size() const { return static_cast<size_t>(-1) / sizeof(T); }
    size_t memory_usage() const { return m_capacity * sizeof(T); }
};
