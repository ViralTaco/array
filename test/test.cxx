#include <iostream>
#include "../src/array.hxx"

namespace vt::info {
  static constexpr auto
    version   = "com.viraltaco.array v1.2.1",
    copyright = "Copyright 2022 viraltaco_ <https://viraltaco.com/array>\n",
    license   = "MIT License. See: <https://opensource.org/licenses/MIT>\n";
 } // namespace vt::info

int main() {

#define ECHO_PSEUDO_STRING(X)                                                  \
  std::cout.put('\n') << #X << ": '" << X                                      \
                      << "' " << #X << ".size(): " << X.size()

#define ECHO_EXPR(X)                                                           \
  std::cout.put('\n') << #X << ": " << std::boolalpha << (X)

  vt::array<int, 5> a = { 1, 2, 3, 4, 5, };
  std::cout << "\nvt::array<int, 5> a = { 1, 2, 3, 4, 5, };";
  ECHO_EXPR(a);
  ECHO_EXPR(a + 5);
  ECHO_EXPR(a & 1);

  auto b = vt::array{ "Hello, World!" };
  std::cout << "\n\nauto b = vt::array{ \"Hello, World!\" };";
  ECHO_PSEUDO_STRING(b);
  ECHO_EXPR(b == b);
  ECHO_EXPR(a == b);

  auto c = b;
  std::cout << "\n\nauto c = b;";
  ECHO_PSEUDO_STRING(c);
  ECHO_EXPR(c == b);

  ECHO_PSEUDO_STRING(c);
  ECHO_EXPR(c -= 1);
  // next line doesn't work yet
  // ignore: ECHO_EXPR(c *= (b & '1'));
  ECHO_PSEUDO_STRING(c);
  ECHO_EXPR(c = c - b + '1');

  auto d = vt::array<char, 14>{};
  d.fill('0');
  std::cout << "\n\nauto d = vt::array<char, 14>{};\nd.fill('0');";
  ECHO_PSEUDO_STRING(c);
  ECHO_PSEUDO_STRING(d);
  ECHO_EXPR(d == c) << std::endl;
  ECHO_EXPR(c = c - d + 'A');
  ECHO_EXPR(d = d - '0' + 'B');
  ECHO_EXPR((d - 1) == c);
#undef ECHO_PSEUDO_STRING
#undef ECHO_EXPR
}
