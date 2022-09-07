#include <iostream>
#include <cassert>
#include "../src/array.hxx"
#include "../src/index_array.hxx"

namespace vt::info {
  static constexpr auto
    version   = "com.viraltaco.array v1.3.2",
    copyright = "Copyright 2022 viraltaco_ <https://viraltaco.com/array>\n",
    license   = "MIT License. See: <https://opensource.org/licenses/MIT>\n";
 } // namespace vt::info

int main() {

#define ECHO_PSEUDO_STRING(X)                                                  \
  std::cout.put('\n') << #X << ": '" << (X)                                    \
                      << "' " << #X << ".size(): " << (X).size()

#define ECHO_EXPR(X)                                                           \
  std::cout.put('\n') << #X << ": " << std::boolalpha << (X)

#define VT_PUTS(S)\
  std::cout.write("\n" S "\n", 2 + sizeof (S)).flush()


  vt::array<int, 5> a = { 1, 2, 3, 4, 5, };
  VT_PUTS("\nvt::array<int, 5> a = { 1, 2, 3, 4, 5, };");
  ECHO_EXPR(a);     assert ((     a  == vt::array{ 1, 2, 3, 4, 5, }));
  ECHO_EXPR(a & 1); assert (((a & 1) == vt::array{ 1, 0, 1, 0, 1, }));
  ECHO_EXPR(a + 5); assert (((a + 5) == vt::array{ 6, 7, 8, 9, 10, }));

  auto b = vt::array{ "Hello, World!" };
  VT_PUTS("\nauto b = vt::array{ \"Hello, World!\" };");
  ECHO_PSEUDO_STRING(b);
  ECHO_EXPR(b == b); assert (b == b);
  ECHO_EXPR(a == b); assert (a != b);

  auto c = b;
  VT_PUTS("auto c = b;");
  ECHO_EXPR(b = vt::array{"hello! world?"});
  ECHO_PSEUDO_STRING(b);
  ECHO_PSEUDO_STRING(c);
  ECHO_EXPR(c == b); assert (c != b);
  ECHO_EXPR(b = c);  assert (c == b);


  ECHO_PSEUDO_STRING(c);
  ECHO_EXPR(c -= 1);
  ECHO_PSEUDO_STRING(c);

  ECHO_EXPR(c = c - b + '1');

  auto d = vt::array<char, 14>{};
  d.fill('0');
  VT_PUTS("\nauto d = vt::array<char, 14>{};\nd.fill('0');");
  ECHO_PSEUDO_STRING(c);
  ECHO_PSEUDO_STRING(d);
  ECHO_EXPR(d == c) << std::endl;

  ECHO_EXPR(c = c - d + 'A');
  ECHO_EXPR(d = d - '0' + 'B');
  ECHO_EXPR((d - 1) == c); assert((d - 1) == c);
  VT_PUTS("Done.");

  VT_PUTS("\n-------------------------------"
          "\n--        index_array        --"
          "\n-------------------------------");
  auto e = vt::index_array<int, 10>();
  VT_PUTS("\nauto e = vt::index_array<int, 10>();");
  auto f = vt::iota<int, 10>();
  VT_PUTS("auto f = vt::iota<int, 10>();");
  ECHO_EXPR(e == f); assert (e == f);

  ECHO_EXPR((e == vt::array{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9  }));
  assert ((e == vt::array{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9  }));

  ECHO_EXPR(e += 1);
  assert ((e == vt::array{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10  }));
  ECHO_EXPR(e /= 2);
  assert ((e == vt::array{ 0, 1, 1, 2, 2, 3, 3, 4, 4, 5  }));

  VT_PUTS("Done.");
#undef ECHO_PSEUDO_STRING
#undef ECHO_EXPR
#undef VT_PUTS
}
