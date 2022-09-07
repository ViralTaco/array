#pragma once /// Copyright 2022 viraltaco_ <https://opensource.org/licenses/MIT>
#ifndef viraltaco_array_index_array_hxx_included
#define viraltaco_array_index_array_hxx_included
#include "array.hxx"

namespace vt::inline detail {

template <class T, size_t N>
constexpr auto iota(vt::array<T, N> self = {}, T i = {})
noexcept -> vt::array<T, N> { do self[i] = i; while (++i != N); return self; }

template <class T, size_t N>
constexpr auto index_array(const T from = T()) noexcept -> vt::array<T, N> {
  auto init = vt::array<T, N>{};
  return vt::iota(init, from);
}
} // namespace vt::inline detail

#endif // viraltaco_array_index_array_hxx_included
