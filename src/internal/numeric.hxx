#pragma once /// copyright 2022 viraltaco_ <https://opensource.org/licenses/MIT>
#ifndef viraltaco_array_internals_numeric_hxx_included
#define viraltaco_array_internals_numeric_hxx_included

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
 noexcept -> T;

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
 constexpr auto sum(InputIt begin, InputIt end, T init) noexcept -> T;
} // namespace vt::inline detail

#endif // viraltaco_array_internals_numeric_hxx_included
