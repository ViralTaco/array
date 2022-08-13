#include <iostream>
#include "../src/array.hxx"

namespace vt::info {
  static constexpr auto
    version   = "com.viraltaco.array v1.0.0",
    copyright = "Copyright 2022 viraltaco_ <https://viraltaco.com/array>\n",
    license   = "MIT License. See: <https://opensource.org/licenses/MIT>\n";
 } // namespace vt::info

int main() {
  vt::array<int, 5> a = { 1, 2, 3, 4, 5, };
  std::cout << "a: " << a;
  auto b = vt::array{ "Hello, World!"  };
  std::cout.put('\n') << "b: " << b << "\tsize: " << b.size();
  std::cout.put('\n') << "b == b: " << std::boolalpha << (b == b);
  std::cout.put('\n') << "a + 5: " << (a + 5);
  std::cout.put('\n') << "a & 1: " << (a & 1);
}
