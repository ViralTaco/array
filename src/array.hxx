#pragma once /// Copyright 2022 viraltaco_ <https://opensource.org/licenses/MIT>

#include <iosfwd>     // std::{ istream, ostream }
#include <stdexcept>  // std::{ out_of_range, invalid_argument }

#include "internal/size_t.hxx"
#include "internal/type_traits.hxx"
#include "internal/utility.hxx"
#include "internal/numeric.hxx"

namespace vt {
template <class T, const size_t N>
struct array {
  /// typedefs:
  using size_type = vt::size_t;
  using value_type = vt::remove_cvref_t<T>;
  using array_type = typename vt::array<value_type, N>;
  using reference = value_type&;
  using const_reference = value_type const&;
  using pointer = value_type*;
  using iterator = pointer;
  using const_pointer = value_type const*;
  using const_iterator = const_pointer;

  template <class It>
  struct reverse_iterator_impl {
    using iterator = It;
    iterator pos;

    // NOLINTNEXTLINE(google-explicit-constructor)
    explicit(false) constexpr reverse_iterator_impl(iterator it) : pos(it) {}

    constexpr auto& operator  *() { return *(pos - 1); }
    constexpr auto& operator ++() { --pos; return *this; }
    constexpr auto& operator --() { ++pos; return *this; }

    constexpr auto operator !=(reverse_iterator_impl const& o) {
      return pos != o.pos;
    }
  };

  using reverse_iterator = reverse_iterator_impl<iterator>;
  using const_reverse_iterator = reverse_iterator_impl<const_iterator>;


private:
  using criter = const_reverse_iterator;
public:

  /// members:
  value_type self[N];
  const_iterator end_ = self + N;

  /// data access:
  constexpr auto data()       noexcept { return self; }
  constexpr auto data() const noexcept { return self; }
  constexpr auto& operator [](size_type i)       noexcept { return self[i]; }
  constexpr auto& operator [](size_type i) const noexcept { return self[i]; }

  constexpr auto& at(size_type i) {
    if (i >= N) throw std::out_of_range(__func__);
    else        return self[i];
  }

  constexpr auto& at(size_type i) const { return this->at(i); }

  constexpr auto   begin() noexcept { return iterator{ data() }; }
  constexpr auto     end() noexcept { return iterator{  data() + N }; }
  constexpr auto  rbegin() noexcept { return reverse_iterator{ data() + N }; }
  constexpr auto    rend() noexcept { return reverse_iterator{ data() }; }
  constexpr auto  cbegin() const noexcept { return data(); }
  constexpr auto    cend() const noexcept { return data() + N; }
  constexpr auto   crend() const noexcept { return criter{ data() }; }
  constexpr auto crbegin() const noexcept { return criter{ data() + N }; }

  [[nodiscard]] constexpr auto     size() const noexcept { return N; }
  [[nodiscard]] constexpr auto max_size() const noexcept { return N; }
  [[nodiscard]] constexpr auto capacity() const noexcept { return N; }
  [[nodiscard]] constexpr auto    empty() const noexcept { return N == 0U; }

  constexpr auto& front()       noexcept { return this[0]; }
  constexpr auto& front() const noexcept { return this[0]; }
  constexpr auto&  back()       noexcept { return this[N - 1U]; }
  constexpr auto&  back() const noexcept { return this[N - 1U]; }
  /// data mutation:

  constexpr void swap(array_type& other) noexcept {
    vt::swap_ranges(begin(), end(), other.begin());
  }

  constexpr auto fill(const_reference value) noexcept -> array_type {
    for (auto it = begin(); it != end_; ++it) { *it = value; }
    return *this;
  }

  template <class F>
  constexpr auto apply(F&& op) noexcept -> array_type {
    for (auto i = 0u; i != N; ++i) { self[i] = op(self[i]); }
    return *this;
  }

  /// const operators:
  template <class Array>
  constexpr bool operator ==(Array const& other) const noexcept {
    if constexpr (not vt::is_same_v<T, typename Array::value_type>)
      return false;
    if (static_cast<void const*> (this) == static_cast<void const*> (&other))
      return true;
    if (N != other.size())
      return false;

    for (auto i = 0; i != N; ++i)
      if (self[i] != other[i]) return false;

    return true;
  }

  constexpr auto operator <=>(array_type const&) const = default;

#define VECTOR_SCALAR_OP_DEF(OP)                                               \
  constexpr auto operator OP##=(const auto v) noexcept -> array_type {         \
    return apply([v] (auto& x) { return x OP v; });                            \
  }                                                                            \
                                                                               \
  template <class V>                                                           \
  constexpr auto operator OP(const V v) const noexcept -> array_type {         \
    auto a = *this;                                                            \
    return a.apply([v] (auto& x) { return x OP v; });                          \
  }                                                                            \
  static_assert(__LINE__, "Require semicolon. Binary operator.")

  VECTOR_SCALAR_OP_DEF(+);
  VECTOR_SCALAR_OP_DEF(-);
  VECTOR_SCALAR_OP_DEF(*);
  VECTOR_SCALAR_OP_DEF(/);
  VECTOR_SCALAR_OP_DEF(%);
  VECTOR_SCALAR_OP_DEF(<<);
  VECTOR_SCALAR_OP_DEF(>>);
  VECTOR_SCALAR_OP_DEF(^);
  VECTOR_SCALAR_OP_DEF(|);
  VECTOR_SCALAR_OP_DEF(&);
#undef VECTOR_SCALAR_OP_DEF
// vector-vector operators:
#define VECTOR_VECTOR_OP_DEF(OP)                                               \
  constexpr auto operator OP##=(array_type other) -> array_type {              \
    return other OP *this;                                                     \
  }                                                                            \
                                                                               \
  constexpr auto operator OP (array_type const& other) const -> array_type {   \
    constexpr auto handle = [] (auto a, auto b) { return a OP b; };            \
    return fold(*this, other, array_type{}, handle);                           \
  }                                                                            \
  static_assert(__LINE__, "Require semicolon. Binary (vec-vec) operator.")

  VECTOR_VECTOR_OP_DEF(+);
  VECTOR_VECTOR_OP_DEF(-);
  VECTOR_VECTOR_OP_DEF(<<);
  VECTOR_VECTOR_OP_DEF(>>);
  VECTOR_VECTOR_OP_DEF(^);
  VECTOR_VECTOR_OP_DEF(|);
  VECTOR_VECTOR_OP_DEF(&);
#undef VECTOR_VECTOR_OP_DEF

  template <class Array>
  constexpr auto operator *(Array const& o) const {
    if (size() != o.size()) {
      throw std::invalid_argument("vt::array<>::operator *(ArrayTemplate):"
                                  " array size mismatch.");
    }
    return vt::inner_product(begin(), end(), o.begin(),
                             value_type() * Array::value_type());
  }

  /// friends:
  friend std::ostream& operator <<(std::ostream& os, vt::array<T, N> const& a) {
    if constexpr (vt::is_same_v<T, char>) {
      return os.write(a.data(), a.size());
    }

    os << "[ ";
    for (auto x = a.cbegin(); x != a.cend(); ++x) {
      os << *x << ", ";
    }
    return os.put(']');
  }

  friend std::istream& operator >>(std::istream& in, vt::array<T, N>& a) {
    for (auto it = a.begin(); it != a.end(); ++it)
      if (not (in >> *it)) break;
    return in;
  }
};
// template deduction guide:
/// @brief Deduce the type and size of the array from the elements.
/// If T and U have different types, the behavior is undefined.
template <class T, class... U>
array(T, U...) -> array<T, 1 + sizeof...(U)>;

/// @brief Deduce the type and size of the array from a string literal.
template <class CharT = char, size_t kLen>
array(CharT const(&)[kLen]) -> array<CharT, kLen>;
}  // namespace vt
