#include <iostream>
#include "array.hxx"

namespace vt::info {
 static constexpr auto version = "com.viraltaco.array v0.0.2",
    copyright = "Copyright 2022 viraltaco_ <https://viraltaco.com/array>\n",
    license = "MIT License. See: <https://opensource.org/licenses/MIT>\n";
 } // namespace vt::info

int main() {
  vt::array<int, 5> a = { 1, 2, 3, 4, 5, };
  std::cout << a;
  auto b = vt::array<char, sizeof "Hello, World!">{ "Hello, World!" };
  std::cout.put('\n') << b;
}
