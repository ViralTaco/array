#include <iostream>
#include "array.hxx"

namespace vt::info {
 static constexpr auto version = "com.viraltaco.array v0.0.2",
    copyright = "Copyright 2022 viraltaco_ <https://viraltaco.com/array>\n",
    license = "MIT License. See: <https://opensource.org/licenses/MIT>\n";
 } // namespace vt::info

#include <algorithm>
int main() {
  vt::array<int, 5> a = { 1, 2, 3, 4, 5, };
  std::for_each(a.rbegin(), a.rend(), [](auto& i) { std::cout << i << " "; });
}
