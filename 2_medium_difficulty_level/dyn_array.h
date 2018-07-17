#pragma once

#include <algorithm>
#include <memory>
#include <type_traits>
#include <iterator>
#include <utility>
#include <cassert>

namespace detail {

  template<typename CurrentIt, typename RequiredIt>
  using RequireIterator = std::enable_if<std::is_base_of<RequiredIt, typename std::iterator_traits<CurrentIt>::iterator_category>::value>;

  template<typename CurrentIt, typename RequiredIt>
  using RequireIterator_t = typename RequireIterator<CurrentIt, RequiredIt>::type;

  template<typename InputIt>
  inline void placement_destruct(InputIt first, InputIt last)
  {
    using T = std::remove_reference_t<decltype(*first)>;
    std::for_each(first, last, [](auto& v){ v.~T(); });
  }

  template<typename InputIt, typename ConstructFunc>
  void placement_construct(InputIt first, InputIt last, ConstructFunc f)
  {
    for(auto it=first; it!=last; ++it) {
      try {
        // construct in place
        f(static_cast<void*>(std::addressof(*it)));
      }
      catch(...) {
        // destroy already created elements in reverse order
        placement_destruct(std::make_reverse_iterator(it), std::make_reverse_iterator(first));
        throw;
      }
    }
  }

}

template<typename T>
class dyn_array {
public:
  using value_type             = T;
  using size_type              = std::size_t;
  using reference              = value_type&;
  using const_reference        = const value_type&;
  using pointer                = value_type*;
  using const_pointer          = const value_type*;
  using iterator               = pointer;
  using const_iterator         = const_pointer;
  using reverse_iterator       = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  dyn_array() = default;

  dyn_array(const dyn_array& other):
    _size{ other._size }, _buffer((_size > 0) ? std::make_unique<char[]>(_size * sizeof(T)) : nullptr)
  {
    auto it = other.begin();
    detail::placement_construct(begin(), end(), [&](auto ptr) { new(ptr) T{*it++}; });
  }

  dyn_array(dyn_array&& other) noexcept:
    dyn_array()
  {
    swap(*this, other);
  }

  explicit dyn_array(size_type count):
    _size{ count }, _buffer((_size > 0) ? std::make_unique<char[]>(_size * sizeof(T)) : nullptr)
  {
    detail::placement_construct(begin(), end(), [](auto ptr) { new(ptr) T{}; });
  }

  dyn_array(size_type count, const T& value):
    _size{ count }, _buffer((_size > 0) ? std::make_unique<char[]>(_size * sizeof(T)) : nullptr)
  {
    detail::placement_construct(begin(), end(), [&](auto ptr) { new(ptr) T{value}; });
  }

  template<typename InputIt, typename = detail::RequireIterator_t<InputIt, std::input_iterator_tag>>
  dyn_array(InputIt first, InputIt last):
    _size{ static_cast<size_type>(std::distance(first, last)) }, _buffer((_size > 0) ? std::make_unique<char[]>(_size * sizeof(T)) : nullptr)
  {
    assert(first <= last);
    detail::placement_construct(begin(), end(), [&](auto ptr) { new(ptr) T{*first++}; });
  }

  dyn_array(std::initializer_list<T> init):
    dyn_array(init.begin(), init.end())
  {
  }

  ~dyn_array()
  {
    detail::placement_destruct(rbegin(), rend());
  }

  dyn_array& operator=(const dyn_array& other)
  {
    if(_size != other._size) {
      dyn_array temp(other);
      swap(*this, temp);
      return *this;
    }
    if(this != &other) {
      std::copy(other.begin(), other.end(), begin());
    }
    return *this;
  }

  dyn_array& operator=(dyn_array&& other) noexcept
  {
    dyn_array temp(std::move(other));
    swap(*this, temp);
    return *this;
  }

  // element access
  reference at(size_type pos)
  {
    if(pos < _size) {
      return (*this)[pos];
    }
    throw std::out_of_range("dyn_array: index out of range");
  }

  const_reference at(size_type pos) const
  {
    if(pos < _size) {
      return (*this)[pos];
    }
    throw std::out_of_range("dyn_array: index out of range");
  }

  reference operator[](size_type pos)              { return *(begin() + pos); }
  const_reference operator[](size_type pos) const  { return *(begin() + pos); }

  reference front()                                { return (*this)[0]; }
  const_reference front() const                    { return (*this)[0]; }
  reference back()                                 { return (*this)[_size - 1]; }
  const_reference back() const                     { return (*this)[_size - 1]; }

  pointer data()                                   { return begin(); }
  const_pointer data() const                       { return begin(); }

  // iterators
  iterator begin()                                 { return reinterpret_cast<pointer>(_buffer.get()); }
  const_iterator begin() const                     { return reinterpret_cast<pointer>(_buffer.get()); }
  const_iterator cbegin() const                    { return reinterpret_cast<pointer>(_buffer.get()); }
  iterator end()                                   { return begin() + _size; }
  const_iterator end() const                       { return begin() + _size; }
  const_iterator cend() const                      { return begin() + _size; }

  reverse_iterator rbegin()                        { return std::make_reverse_iterator(end()); }
  const_reverse_iterator rbegin() const            { return std::make_reverse_iterator(end()); }
  const_reverse_iterator crbegin() const           { return std::make_reverse_iterator(end()); }
  reverse_iterator rend()                          { return std::make_reverse_iterator(begin()); }
  const_reverse_iterator rend() const              { return std::make_reverse_iterator(begin()); }
  const_reverse_iterator crend() const             { return std::make_reverse_iterator(begin()); }

  // capacity
  bool empty() const                               { return size() == 0; }
  size_type size() const                           { return _size; }

  // operations
  friend void swap(dyn_array& lhs, dyn_array& rhs) noexcept
  {
    using std::swap;
    swap(lhs._size, rhs._size);
    swap(lhs._buffer, rhs._buffer);
  }

private:
  size_type _size = 0;
  std::unique_ptr<char[]> _buffer;
};


template<typename T>
inline bool operator==(const dyn_array<T>& lhs, const dyn_array<T>& rhs)
{
  const std::size_t lhs_size = lhs.size();
  if (lhs_size != rhs.size()) return false;
  for (std::size_t i{}; i < lhs_size; i++) {
    if (lhs[i] != rhs[i]) return false;
  }

  return true;  
}

template<typename T>
inline bool operator!=(const dyn_array<T>& lhs, const dyn_array<T>& rhs)
{
  return !(lhs == rhs);
}

template<typename T>
inline bool operator<(const dyn_array<T>& lhs, const dyn_array<T>& rhs)
{
  const std::size_t lhs_size = lhs.size();
  const std::size_t rhs_size = rhs.size();
  if (lhs_size < rhs_size) return true;
  if (lhs_size > rhs_size) return false;

  for (std::size_t i{}; i < lhs_size; i++) {
    if (lhs[i] < rhs[i]) return true;
  }

  return false;  
}

template<typename T>
inline bool operator>(dyn_array<T> lhs, dyn_array<T> rhs)
{
  const std::size_t lhs_size = lhs.size();
  const std::size_t rhs_size = rhs.size();
  if (lhs_size > rhs_size) return true;
  if (lhs_size < rhs_size) return false;

  for (std::size_t i{}; i < lhs_size; i++) {
    if (lhs[i] > rhs[i]) return true;
  }

  return false;
}

template<typename T>
inline bool operator<=(dyn_array<T> lhs, dyn_array<T> rhs)
{
  return !(lhs > rhs);
}

template<typename T>
inline bool operator>=(dyn_array<T> lhs, dyn_array<T> rhs)
{
  return !(lhs < rhs);
}
