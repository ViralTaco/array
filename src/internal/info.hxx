#pragma once /// copyright 2024 viraltaco_ <https://opensource.org/licenses/MIT>
#ifndef viraltaco_array_internals_info_hxx_included
#define viraltaco_array_internals_info_hxx_included
namespace vt::inline detail {
 struct array_info final {
   static constexpr auto
     version   = "com.viraltaco.array v2.1.0"
   , copyright = "Copyright 2022,2023,2024 viraltaco_ <viraltaco.com/array>\n"
   , license   = "MIT License. See: <opensource.org/licenses/MIT>\n"
   ;

   template <class Ostream, class Info = const array_info>
   friend Ostream& operator <<(Ostream& out, Info) {
     return out << version << '\n' << copyright << license;
   }
 } info {};
 } // namespace vt::inline detail

#endif// viraltaco_array_internals_info_hxx_included
