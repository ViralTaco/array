#pragma once /// Copyright 2022 viraltaco_ <https://opensource.org/licenses/MIT>

#include "internal/type_traits.hxx"

namespace vt {
 inline namespace detail {
  using size_t = decltype (sizeof 0);
 }

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
     iterator pos_;

     constexpr reverse_iterator(iterator _it) : pos_{ _it } {}
     constexpr auto& operator  *() { return *(pos_ - 1u);  }
     constexpr auto& operator ++() { --pos_; return *this; }
     constexpr auto& operator --() { ++pos_; return *this; }
     constexpr auto friend
     operator !=(reverse_iterator const& a, reverse_iterator const& b) {
       return a.pos_ != b.pos_;
     }
   };

   static constexpr size_t size = N;
   value_type data[N + 1]; // +1 for sentinel

   constexpr reference       operator [](size_t i)       { return data[i]; }
   constexpr const_reference operator [](size_t i) const { return data[i]; }
   constexpr const_iterator       cbegin()         const { return data;     }
   constexpr const_iterator         cend()         const { return data + N; }
   constexpr iterator              begin()               { return data;     }
   constexpr iterator                end()               { return data + N; }
   constexpr reverse_iterator     rbegin()               { return data + N; }
   constexpr reverse_iterator       rend()               { return data;     }
 };
} // namespace vt
