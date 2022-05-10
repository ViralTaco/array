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

   template <class It> struct reverse_iterator_impl {
     using iterator = It;
     iterator pos;

     // NOLINTNEXTLINE(google-explicit-constructor)
     explicit(false) constexpr reverse_iterator_impl(iterator it) : pos(it) {}

     constexpr auto& operator  *() { return *(pos - 1); }
     constexpr auto& operator ++() { --pos; return *this; }
     constexpr auto& operator --() { ++pos; return *this; }
     constexpr auto  operator
     !=(reverse_iterator_impl const& o) { return pos != o.pos; }
   };

   using reverse_iterator       = reverse_iterator_impl<iterator>;
   using const_reverse_iterator = reverse_iterator_impl<const_iterator>;

   value_type self[N + 1];
   const_iterator end_ = self + N;

   constexpr pointer       data()       noexcept { return self; }
   constexpr const_pointer data() const noexcept { return self; }

   constexpr reference operator [](size_type i) noexcept { return self[i]; }
   constexpr const_reference operator [](size_type i) const noexcept {
     return self[i];
   }
   constexpr reference at(size_type i) {
     if (i >= N) throw std::out_of_range("vt::array::at(size_t)");
     return self[i];
   }
   constexpr const_reference at(size_type i) const {
     if (i >= N) throw std::out_of_range("vt::array::at(size_t) const");
     return self[i];
   }
   constexpr iterator                 begin() noexcept { return data(); }
   constexpr iterator                   end() noexcept { return data() + N; }
   constexpr reverse_iterator        rbegin() noexcept { return data() + N; }
   constexpr reverse_iterator          rend() noexcept { return data(); }
   constexpr const_iterator    cbegin() const noexcept { return data(); }
   constexpr const_iterator      cend() const noexcept { return data() + N; }
   constexpr const_reverse_iterator
   crbegin() const noexcept { return data() + N; }
   constexpr const_reverse_iterator   crend() const noexcept { return data(); }

   [[nodiscard]] constexpr size_type     size() const noexcept { return N; }
   [[nodiscard]] constexpr size_type max_size() const noexcept { return N; }
   [[nodiscard]] constexpr size_type capacity() const noexcept { return N; }
   [[nodiscard]] constexpr bool         empty() const noexcept { return !N; }

   constexpr vt::array<T, N>& fill(const_reference value) noexcept {
     for (reference x: *this)
       x = value;
     return *this;
   }

   constexpr void swap(vt::array<T, N>& other) noexcept {
     vt::swap_ranges(begin(), end(), other.begin());
   }

   friend std::ostream& operator <<(std::ostream& os,
                                    vt::array<T, N> const& a) {
     if constexpr (vt::is_same_v<T, char>) {
       return os.write(a.data(), a.size());
     }
     os << "[ ";
     for (const_iterator x = a.cbegin(); x != a.cend(); ++x)
       os << *x << ", ";
     return os.put(']');
   }

   friend std::istream& operator >>(std::istream& in, vt::array<T, N>& a) {
     for (reference x: a)
       if (not in >> x) break;
     return in;
   }
 };
} // namespace vt
