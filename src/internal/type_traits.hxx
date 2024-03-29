#pragma once /// copyright 2022 viraltaco_ <https://opensource.org/licenses/MIT>
#ifndef viraltaco_array_internals_type_traits_hxx_included
#define viraltaco_array_internals_type_traits_hxx_included

namespace vt::inline detail {
template <class T, T v>
struct integral_constant {
  using value_type = T;
  using type = integral_constant<T, v>;
  static constexpr value_type value = v;
  constexpr value_type operator()() const noexcept { return v; }
  explicit constexpr operator value_type() const noexcept { return v; }
};

using false_type = typename vt::integral_constant<bool, false>::type;
using true_type = typename vt::integral_constant<bool, true>::type;

template <class T, class U>
struct is_same : false_type {};
template <class T>
struct is_same<T, T> : true_type {};
template <class T, class U>
static constexpr auto is_same_v = vt::is_same<T, U>::value;

template <class T>
struct remove_cv { using type = T; };
template <class T>
struct remove_cv<const T> { using type = T; };
template <class T>
struct remove_cv<volatile T> { using type = T; };
template <class T>
struct remove_cv<const volatile T> { using type = T; };
template <class T>
using remove_cv_t = typename vt::remove_cv<T>::type;

template <class T>
struct remove_ref { using type = T; };
template <class T>
struct remove_ref<T &> { using type = T; };
template <class T>
struct remove_ref<T &&> { using type = T; };
template <class T>
using remove_ref_t = typename vt::remove_ref<T>::type;

template <class T>
struct remove_cvref { using type = vt::remove_cv_t<vt::remove_ref_t<T>>; };
template <class T>
using remove_cvref_t = typename vt::remove_cvref<T>::type;
} // namespace vt::inline detail

#endif // viraltaco_array_internals_type_traits_hxx_included
