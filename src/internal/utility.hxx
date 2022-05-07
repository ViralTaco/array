#pragma once /// copyright 2022 viraltaco_ <https://opensource.org/licenses/MIT>
#include "type_traits.hxx"

namespace vt::inline detail {
 template <auto... Is> struct integer_sequence {
   static constexpr auto size() noexcept { return sizeof... (Is); }
 };

 template <class T, class U = vt::remove_ref_t<T>> [[nodiscard]]
 constexpr U&& move(T&& o) noexcept { return static_cast<U&&> (o); }

 template <class T>
 constexpr void swap(T& a, T& b) noexcept {
   T _a = vt::move(a);
   a = vt::move(b);
   b = vt::move(_a);
 }
} // namespace vt::inline::detail
