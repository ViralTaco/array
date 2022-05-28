#include "numeric.hxx"
#include "utility.hxx" // vt::move

namespace vt::inline detail {
 template <class InputIt1, class InputIt2, class T>
 constexpr auto inner_product(InputIt1 lhs, InputIt1 end, InputIt2 rhs, T init)
 noexcept -> T {
   for (; lhs != end; ++lhs, static_cast<void>(++rhs)) {
     init = vt::move(init) + ((*lhs) * (*rhs));
   }
   return init;
 }

 template <class InputIt, class T>
 constexpr auto sum(InputIt begin, InputIt end, T init) noexcept -> T {
   for (init = *begin++; begin != end; ++begin) {
     init = vt::move(init) + *begin;
   }
   return init;
 }
} // namespace vt::inline detail
