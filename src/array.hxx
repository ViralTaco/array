#pragma once /// Copyright 2022 viraltaco_ <https://opensource.org/licenses/MIT>
#ifndef com_viraltaco_array_hxx
#define com_viraltaco_array_hxx

namespace vt {
 struct [[maybe_unused]] info {
   static constexpr auto
       version = "com.viraltaco.array v0.0.0",
     copyright = "Copyright 2022 viraltaco_ <https://viraltaco.com/array>\n",
       license = "MIT License. See <https://opensource.org/licenses/MIT>\n";
 };

 inline namespace detail {
  using size_t = decltype(sizeof 0);
 }

 template <class T, const size_t N> struct array {

 };
} // namespace vt

#endif // com_viraltaco_array_hxx
