#pragma once /// copyright 2022 viraltaco_ <https://opensource.org/licenses/MIT>
#ifndef viraltaco_array_internals_numeric_hxx_included
#define viraltaco_array_internals_numeric_hxx_included
#include "size_t.hxx"  // vt::ssize_t
#include "utility.hxx" // vt::move

namespace vt::inline detail {
 /**
  * @brief Computes the inner product of two ranges.
  *
  * @param lhs  The beginning of the first range.
  * @param end  The end of the first range.
  * @param rhs  The beginning of the second range.
  * @param init The initial value to which the inner product is added.
  *
  * @return The inner product of the two ranges.
  *
  * @warning If size(range_of_rhs) < distance(lhs, end)
  *          then the behavior is UNDEFINED.
  *
  * @throws noexcept
  */
 template <class InputIt1, class InputIt2, class T>
 constexpr auto inner_product(InputIt1 lhs, InputIt1 end, InputIt2 rhs, T init)
 noexcept -> T {
   for (; lhs != end; ++lhs, static_cast<void>(++rhs))
     init = vt::move(init) + ((*lhs) * (*rhs));
   return init;
 }

 /**
  * @brief Computes the sum of every element of a range.
  *
  * @param begin The beginning of the range.
  * @param end   The end of the range.
  * @param init  The initial value to which the sum is added.
  * @return The sum of every element of the range.
  *
  * @throws noexcept
  */
 template <class InputIt, class T>
 constexpr auto sum(InputIt begin, InputIt end, T init) noexcept -> T {
   for (init = *begin++; begin != end; ++begin)
     init = vt::move(init) + *begin;
   return init;
 }

 /**
  * @brief Applies <code>init[i] = op(a[i], b[i])</code>
  *        for <code>i</code> in <code>[0, a.size())</code>
  *
  * @param a     Container for the first range.
  * @param b     Container for the second range.
  * @param init  A container to store the results.
  * @param op    The function applied over the ranges.
  * @return      init
  *
  * @warning If the range pointed to by `b` has a size lower than that of `a`
  *          the behavior is undefined.
  *
  * @throws noexcept<code> (op)</code>
  */
 template <class T, class F>
 constexpr auto fold(auto const& a, auto const& b, T init, F&& op) -> T {
   const auto kLen = static_cast<ssize_t> (a.size());
   for (auto i = 0LL; i != kLen; ++i)
     init[i] = static_cast<typename T::value_type> (op(a[i], b[i]));
   return init;
 }
} // namespace vt::inline detail

#endif // viraltaco_array_internals_numeric_hxx_included
