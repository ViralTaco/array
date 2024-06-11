#pragma once /// Copyright viraltaco_ <https://opensource.org/licenses/MIT>
#ifndef viraltaco_array_array_hxx_included
#define viraltaco_array_array_hxx_included

#include "internal/size_t.hxx"
#include "internal/type_traits.hxx"
#include "internal/utility.hxx"
#include "internal/numeric.hxx"

namespace vt::inline detail {
  template <class It> class reverse_iterator {
    It pos;
  public:
    [[nodiscard]] explicit constexpr reverse_iterator(It it) : pos(it) {}
    
    constexpr auto& operator   *() const noexcept { return *(pos - 1); }
    constexpr auto& operator  ++()       noexcept { --pos; return *this; }
    constexpr auto& operator  --()       noexcept { ++pos; return *this; }
    constexpr auto  operator <=>(reverse_iterator const&) const = default;
  };
} // namespace vt::inline detail

namespace vt {
template <class T, const size_t N> struct array {
  using size_type                        = decltype (N);
  using value_type                       = vt::remove_cvref_t<T>;
  using type            [[maybe_unused]] = array;
  using array_type      [[maybe_unused]] = type;
  using reference       [[maybe_unused]] = value_type&;
  using const_reference [[maybe_unused]] = value_type const&;
  using pointer                          = value_type*;
  using iterator                         = pointer;
  using const_pointer                    = value_type const*;
  using const_iterator                   = const_pointer;
  using reverse_iterator                 = vt::reverse_iterator<iterator>;
  using const_reverse_iterator           = vt::reverse_iterator<const_iterator>;

/// members:
  value_type self[N];
  
/// data access:
  constexpr auto&        data()                  noexcept { return self; }
  constexpr auto&        data()            const noexcept { return self; }
  constexpr auto& operator [](size_type i)       noexcept { return data()[i]; }
  constexpr auto& operator [](size_type i) const noexcept { return data()[i]; }

#define VT_MAKE_ITERATOR_BOILERPLATE_(NAME, RET, TYPE)                         \
  constexpr auto NAME() noexcept -> TYPE { return RET; }                       \
  constexpr auto NAME() const noexcept -> const_##TYPE { return RET; }         \
  constexpr auto c##NAME() const noexcept -> const_##TYPE { return RET; }      \
  static_assert (!"Missing `;` on line" + __LINE__, #NAME "() def.")

  VT_MAKE_ITERATOR_BOILERPLATE_( begin, data()    , iterator);
  VT_MAKE_ITERATOR_BOILERPLATE_(   end, data() + N, iterator);
  VT_MAKE_ITERATOR_BOILERPLATE_(rbegin, data() + N, reverse_iterator);
  VT_MAKE_ITERATOR_BOILERPLATE_(  rend, data()    , reverse_iterator);
#undef VT_MAKE_ITERATOR_BOILERPLATE_

  constexpr auto& at(size_type i) noexcept {
    return (i < N) ? this[i] : end();
  }
  constexpr auto& at(size_type i) const noexcept { return at(i); }
  [[nodiscard]] constexpr auto     size() const noexcept { return N; }
  [[nodiscard]] constexpr auto max_size() const noexcept { return N; }
  [[nodiscard]] constexpr auto capacity() const noexcept { return N; }
  [[nodiscard]] constexpr auto    empty() const noexcept { return N == 0U; }

  constexpr auto& front()       noexcept { return this[0]; }
  constexpr auto& front() const noexcept { return this[0]; }
  constexpr auto&  back()       noexcept { return this[N - 1U]; }
  constexpr auto&  back() const noexcept { return this[N - 1U]; }

/// data mutation:
  constexpr void swap(array& other) noexcept {
    vt::swap_ranges(begin(), end(), other.begin());
  }
  
  template <class F>
  constexpr auto apply(F&& op) noexcept -> array {
    for (auto& e: *this) {
      if constexpr (vt::is_same_v<value_type, F>) {
        e = op;
      } else {
        e = static_cast<value_type> (op(e));
      }
    }
    return *this;
  }

  constexpr auto fill(value_type val) noexcept -> array {
    return apply(vt::move(val));
  }

/// const operators:
#define VECTOR_SCALAR_OP_DEF(OP)                                               \
  constexpr auto operator OP##=(const auto v) noexcept -> array {              \
    return apply([v] (auto& x) { return x OP v; });                            \
  }                                                                            \
                                                                               \
  template <class V>                                                           \
  constexpr auto operator OP(const V v) const noexcept -> array {              \
    auto a = *this;                                                            \
    return a.apply([v] (auto& x) { return x OP v; });                          \
  }                                                                            \
  static_assert(!"Missing `;` on line" + __LINE__, "vector-scalar" #OP)

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
#define VECTOR_VECTOR_OP_DEF(OP)                                               \
  constexpr auto operator OP##=(array o) -> array { return o OP *this; }       \
  constexpr auto operator OP(array const& other) const -> array {              \
    return vt::fold(*this, other, array{}, [] (T a, T b) { return a OP b; });  \
  }                                                                            \
  static_assert(!"Missing `;` on line" + __LINE__, "vector-vector" #OP)

  VECTOR_VECTOR_OP_DEF(+);
  VECTOR_VECTOR_OP_DEF(-);
  VECTOR_VECTOR_OP_DEF(<<);
  VECTOR_VECTOR_OP_DEF(>>);
  VECTOR_VECTOR_OP_DEF(^);
  VECTOR_VECTOR_OP_DEF(|);
  VECTOR_VECTOR_OP_DEF(&);
#undef VECTOR_VECTOR_OP_DEF

  auto operator  *(array const&) = delete; // issue #4
  auto operator *=(array const&) = delete;

  template <class Array>
  constexpr auto operator ==(Array const& o) const noexcept -> bool {
    if constexpr (not vt::is_same_v<value_type, typename Array::value_type>) {
      return false;
    } else if (vt::pointer_equal(this, &o)) {
      return true;
    } else {
      return N == o.size() and [k = *this ^ o] {
        return not vt::sum(k.cbegin(), k.cend(), T{});
      }();
    }
  }
  constexpr auto operator <=>(array const&) const = default;
  /// friends:
  template <class Ostream>
  friend Ostream& operator <<(Ostream& os, array const& a) {
    if constexpr (vt::is_same_v<value_type, char>) {
      return os.write(a.data(), a.size());
    }

    os << "[ ";
    for (const value_type x: a)
      os << x << ", ";
    return os << "]";
  }

  template <class Istream>
  friend Istream& operator >>(Istream& in, array& a) {
    for (auto it = a.begin(); it != a.end(); ++it)
      if (not (in >> *it)) break;
    return in;
  }
};
/// @brief Deduce the type and size of the array from the elements.
/// If T and U have different types, the behavior is undefined.
template <class T, class... U>
array(T, U...) -> array<T, 1 + sizeof...(U)>;

/// @brief Deduce the type and size of the array from a string literal.
template <class CharT = char, size_t kLen>
array(CharT const(&)[kLen]) -> array<CharT, kLen>;
}  // namespace vt

#endif // #ifndef viraltaco_array_array_hxx_included
