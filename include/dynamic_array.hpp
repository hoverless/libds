#pragma once

#include <cstddef>
#include <iostream>
#include <limits>

namespace ds::impl::internal {
template<typename T>
void reallocate(T* data, std::size_t old_size, std::size_t new_size)
{
  // Allocate new block and transfer old data. Free old memory block.
  T* tmp = new T[new_size];
  for (auto i = 0u; i < old_size; ++i) {
    tmp[i] = data[i];
  }
  delete[] data;
  data = tmp;
}
} // namespace ds::impl::internal

namespace ds::impl {

template<typename T>
class dynamic_array {
private:
  // Data buffer
  T*          m_data;
  std::size_t m_size;
  std::size_t m_capacity;

public:
  // Construction and Destruction
  dynamic_array() noexcept;
  dynamic_array(std::size_t count);
  dynamic_array(const dynamic_array& other);
  dynamic_array(dynamic_array&& other);
  ~dynamic_array();

  // Operator overloads
  dynamic_array& operator=(const dynamic_array& other);
  dynamic_array& operator=(dynamic_array&& other);

  // Capacity
  std::size_t size() const noexcept;
  std::size_t capacity() const noexcept;
  std::size_t max_size() const noexcept;
  bool        empty() const noexcept;
  void        reserve(std::size_t new_cap);
  void        shrink_to_fit();

  // Access
  const T*    data() const noexcept;

};

// IMPLEMENTATION
template<typename T>
dynamic_array<T>::dynamic_array() noexcept {
  m_size      = 0;
  m_capacity  = 0;
  m_data      = nullptr;
}

template<typename T>
dynamic_array<T>::dynamic_array(std::size_t count) {
  m_size      = count;
  m_data      = new T[count];
  m_capacity  = count;

  // Default initialize all data in the buffer.
  for (auto i = 0u; i < m_size; ++i) {
    m_data[i] = T();
  }
}

template<typename T>
dynamic_array<T>::dynamic_array(const dynamic_array<T>& other) {
}

template<typename T>
dynamic_array<T>::dynamic_array(dynamic_array<T>&& other) {
}


template<typename T>
dynamic_array<T>::~dynamic_array() {
  delete[] m_data;
}

template<typename T>
dynamic_array<T>& 
dynamic_array<T>::operator=(const dynamic_array<T>& other){
}

template<typename T>
dynamic_array<T>& 
dynamic_array<T>::operator=(dynamic_array<T>&& other) {
}


template<typename T>
std::size_t
dynamic_array<T>::size() const noexcept {
  return m_size;
}

template<typename T>
std::size_t
dynamic_array<T>::capacity() const noexcept {
  return m_capacity;
}

template<typename T>
std::size_t
dynamic_array<T>::max_size() const noexcept {
  return std::numeric_limits<std::size_t>::max() / sizeof(T);
}

template<typename T>
bool
dynamic_array<T>::empty() const noexcept {
  return size() == 0;
}

template<typename T>
void
dynamic_array<T>::reserve(std::size_t new_cap) {
  if (new_cap > max_size()) {
    throw std::length_error("Requested memory greater than maximum");
  }
  if (new_cap <= m_capacity) {
    return;
  }

  // Allocate new block and transfer old data. Free old memory block.
  T* tmp = new T[new_cap];
  for (auto i = 0u; i < m_size; ++i) {
    tmp[i] = m_data[i];
  }
  delete[] m_data;
  m_data = tmp;
  m_capacity = new_cap;
}

template<typename T>
void
dynamic_array<T>::shrink_to_fit() {
  if (m_size == 0) {
      delete[] m_data;
      m_data = nullptr;
      m_capacity = 0;
  } else if (m_size == m_capacity) {
      // do nothing
  } else {
      internal::reallocate(m_data, m_size, m_size); // will shrink the buffer to m_size
      m_capacity = m_size;
  }
}

template<typename T>
const T*
dynamic_array<T>::data() const noexcept {
  return m_data;
}

} // namespace ds::impl
