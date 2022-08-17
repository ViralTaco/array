#pragma once /// copyright 2022 viraltaco_ <https://opensource.org/licenses/MIT>
#ifndef viraltaco_array_internals_size_t_hxx_included
#define viraltaco_array_internals_size_t_hxx_included

namespace vt::inline detail::inline types {
 using ssize_t =   signed long long;
 using size_t  = unsigned long long;

 namespace literals {
  consteval auto operator ""_z(unsigned long long x) noexcept
  -> size_t { return x; }

  /**
   * @brief auto operator ""_sz(x) -> ssize_t
   * @param x unsigned long long
   * @returns <code>static_cast<ssize_t> (x)</code>
   * @throws noexcept
   * @warning <code>if x > std::numeric_limits&lt;long long&gt;::max()</code>
   * the behavior is undefined.
   */
  consteval auto operator ""_sz(unsigned long long x) noexcept
  -> ssize_t { return static_cast<ssize_t> (x); }
 } // namespace vt::inline detail::::inline types::literals
} // namespace vt::inline detail::inline types

#endif  // viraltaco_array_internals_size_t_hxx_included
