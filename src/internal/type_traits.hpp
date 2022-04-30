#pragma once /// copyright 2022 viraltaco_ <https://opensource.org/licenses/MIT>
#ifndef com_viraltaco_type_traits_hxx
#define com_viraltaco_type_traits_hxx
static_assert (
  __cplusplus > 201700L,
  "Outdated C++ standard version. Please use C++20 and above."
);

namespace vt::inline detail {

template <class T, T v> struct integral_constant {
  using value_type = decltype (v);
  using type = integral_constant<T, v>;
  static constexpr value_type value = v;
  constexpr value_type operator()() const noexcept { return v; }
  explicit constexpr operator value_type() const noexcept { return v; }
};

using false_type = typename integral_constant<bool, false>::type;
using true_type  = typename integral_constant<bool, true>::type;

template <class T, class U> struct is_same       : false_type {};
template <class T>          struct is_same<T, T> : true_type  {};
template <class T, class U>
static constexpr auto is_same_v = vt::is_same<T, U>::value;

template <class T> struct remove_cv                   { using type = T; };
template <class T> struct remove_cv<const T>          { using type = T; };
template <class T> struct remove_cv<volatile T>       { using type = T; };
template <class T> struct remove_cv<const volatile T> { using type = T; };
template <class T>
using remove_cv_t = typename vt::remove_cv<T>::type;

template <class T> struct remove_ref      { using type = T; };
template <class T> struct remove_ref<T&>  { using type = T; };
template <class T> struct remove_ref<T&&> { using type = T; };
template <class T>
using remove_ref_t = typename vt::remove_ref<T>::type;
} // namespace vt::inline detail


#endif // com_viraltaco_type_traits_hxx