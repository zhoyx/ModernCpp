#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <cstddef>
#include <utility>
#include <cstdio>

template<typename T> class Vector {
public:
    Vector() : m_size{ 0 }, m_ptr{ nullptr } {
        std::printf("Default constructor called, address: [%p]\n", m_ptr);
    };
    Vector(size_t size) : m_size{ 0 }, m_ptr{ new T[size] } {
        for (int i = 0; i < size; ++i) {
            m_ptr[i] = 0;
        }
        std::printf("Size constructor called, address: [%p]\n", m_ptr);
    }

    // Copy constructor to prevent double-frees
    Vector(const Vector& rhs) : m_size{ rhs.m_size }, m_ptr{ new T[rhs.m_size] } {
        std::copy(rhs.m_ptr, rhs.m_ptr + m_size, m_ptr);
        std::printf("Copy constructor called, new copy address: [%p], copied address: [%p]\n", m_ptr, rhs.m_ptr);
    }

    // Move constructor
    Vector(Vector&& rhs) noexcept {
        m_size = std::exchange(rhs.m_size, 0);
        m_ptr = std::exchange(rhs.m_ptr, nullptr);
        std::printf("Move constructor called, on address: [%p]\n", m_ptr);
    }

    // Assignment operator to free left-hand resource and transfer ownership to the right-hand one
    Vector& operator=(Vector copy) {
        copy.swap(*this);
        std::printf("Assignment operator called\n");
        return *this;
    }

    // Destructor
    ~Vector() {
        std::printf("Destructor Called, address: [%p]\n", m_ptr);
        delete[] m_ptr;
    }

    // Member swap
    void swap(Vector& rhs) noexcept {
        using std::swap;
        swap(m_size, rhs.m_size);
        swap(m_ptr, rhs.m_ptr);
    }

    // Two argument swap to make Vector efficiently "std::swappable"
    friend void swap(Vector& a, Vector& b) {
        a.swap(b);
    }


private:
    size_t m_size;
    T* m_ptr;
};


#endif
