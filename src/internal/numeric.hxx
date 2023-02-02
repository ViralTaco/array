#pragma once /// copyright 2022 viraltaco_ <https://opensource.org/licenses/MIT>
#ifndef viraltaco_array_internals_numeric_hxx_included
#define viraltaco_array_internals_numeric_hxx_included
#include "size_t.hxx"  // vt::ssize_t
#include "utility.hxx" // vt::move

namespace vt::inline detail {
 /**
  * @brief Assigns to the given range, incrementing by 1 from the given value.
  *
  * @param beg   The beginning of the (in-out) range.
  * @param end   My only friend. (also in-out)
  * @param val   The initial value (assigned to *beg).
  *
  * @warning If val is signed and `(numeric_limits<T>::max() - (end-beg)) < val`
  *     (ie: `if val + length_range` overflows), then the behavior is UNDEFINED,
  *     and the code is ILL-FORMED, NO DIAGNOSYS REQUIRED. (Since c++98)
  *
  * @warning If `end` is NOT reachable by incrementing `beg` (ie: `++beg`),
  *  or if [beg, end) is NOT a valid range, then the program is ILL-FORMED.
  *
  * @throws noexcept
  */
 template <class FwdIt, class T>
 constexpr auto iota(FwdIt& beg, FwdIt& end, auto val) noexcept -> void {
    for (; beg != end; ++beg, static_cast<void> (++val))
      *beg = val;
  }
  
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
  * @param init  Container for the results range.
  * @param op    Function over the ranges.
  * @return      for i in [0, a.size()) do init[i] = op(a[i], b[i])
  *
  * @warning If the range pointed to by `b` has a size lower than that of `a`
  *          the behavior is undefined.
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
