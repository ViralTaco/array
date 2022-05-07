#pragma once /// Copyright 2022 viraltaco_ <https://opensource.org/licenses/MIT>
#include "internal/type_traits.hxx"
#include "internal/utility.hxx"

namespace vt {
 inline namespace detail { using size_t = decltype (sizeof 0); }

 template <class T, const size_t N> struct array {
   using size_type        = vt::size_t;
   using value_type       = vt::remove_cvref_t<T>;
   using reference        = value_type&;
   using const_reference  = value_type const&;
   using pointer          = value_type*;
   using iterator         = pointer;
   using const_pointer    = value_type const*;
   using const_iterator   = const_pointer;

   struct reverse_iterator {
     iterator pos;

     // NOLINTNEXTLINE(google-explicit-constructor)
     explicit(false) constexpr reverse_iterator(iterator it) : pos(it) {}

     constexpr auto& operator  *() { return *(pos - 1); }
     constexpr auto& operator ++() { --pos; return *this; }
     constexpr auto& operator --() { ++pos; return *this; }
     constexpr auto  operator
     !=(reverse_iterator const& o) { return pos != o.pos; }
   };
   value_type data[N + 1];
   const iterator end_ = data + N;

   constexpr reference       operator [](size_t i)       { return data[i]; }
   constexpr const_reference operator [](size_t i) const { return data[i]; }
   constexpr const_iterator       cbegin()         const { return data; }
   constexpr const_iterator         cend()         const { return end_; }
   constexpr iterator              begin()               { return data; }
   constexpr iterator                end()               { return end_; }
   constexpr reverse_iterator     rbegin()               { return end_; }
   constexpr reverse_iterator       rend()               { return data; }

   [[nodiscard]] constexpr size_type     size() const { return N; }
   [[nodiscard]] constexpr size_type max_size() const { return N; }
   [[nodiscard]] constexpr size_type capacity() const { return N; }
   [[nodiscard]] constexpr bool         empty() const { return false; }

   constexpr vt::array<T, N>& fill(const_reference value) noexcept {
     for (auto& x: *this) x = value;
     return *this;
   }

   constexpr void swap(vt::array<T, N>& other) noexcept {
     for (auto i = 0; i != N; ++i) vt::swap(this[i], other[i]);
   }

  friend std::ostream& operator <<(std::ostream& os, vt::array<T, N> const& a) {
     return os << a.data;
   }

   friend std::istream& operator >>(std::istream& in, vt::array<T, N>& a) {
     for (auto& x: a) if (not in >> x) break;
     return in;
   }
 };
} // namespace vt
