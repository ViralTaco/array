#pragma once /// copyright 2022 viraltaco_ <https://opensource.org/licenses/MIT>
#ifndef viraltaco_array_internals_utility_hxx_included
#define viraltaco_array_internals_utility_hxx_included
#include "type_traits.hxx"

namespace vt::inline detail {
template <auto... Is> struct integer_sequence {
  static constexpr auto size() noexcept { return sizeof... (Is); }
};

template <class T, class U = vt::remove_ref_t<T>>
[[nodiscard("Discarding moved value. THIS IS PROBABLY AN ERROR.")]]
constexpr auto move(T&& o) noexcept -> U&& { return static_cast<U &&> (o); }

template <class T>
constexpr void swap(T &a, T &b) noexcept {
  T _a = vt::move(a);
  a = vt::move(b);
  b = vt::move(_a);
}

template <class FwL, class FwR>
constexpr FwR swap_ranges(FwL l, FwL last, FwR r) noexcept {
  for (; l != last; ++l, static_cast<void> (++r))
    vt::swap(*l, *r);
  return r;
}

template <class T> constexpr T min(T a, T b) noexcept { return a < b ? a : b; }
template <class T> constexpr T max(T a, T b) noexcept { return a < b ? b : a; }

constexpr auto pointer_equal(auto const* a, auto const* b) noexcept {
  return static_cast<void const*>(a)
      == static_cast<void const*>(b);
}
} // namespace vt::inline::detail

#endif // viraltaco_array_internals_utility_hxx_included
