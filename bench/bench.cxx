// Based on https://gist.github.com/pudov/b158af49f449209b1be2
#include "../src/array.hxx"
#include <algorithm>
#include <numeric>
#include <array>
#include <cassert>
#include <chrono>
#include <deque>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <ratio>
#include <vector>

namespace {
using  vt::literals::operator ""_z;
static constexpr auto kSize = 2'000'000_z;
static constexpr auto kElem = 36'546_z;
using u32 = std::uint_least32_t;
using u64 = std::uint_least64_t;

template <class Cont>
auto init() -> Cont {
  using T = typename Cont::value_type;
  static Cont c;
  if constexpr (std::is_same_v<Cont, std::vector<T>>) {
    c = std::vector<T>(kSize);
  }
  std::iota(std::begin(c), std::end(c), T{});
  return c;
}

template <class Cont>
auto do_find(const Cont& c) -> decltype (c.cend()) {
  return std::find(c.cbegin(), c.cend(), kElem);
}

template <class Cont>
void benchmark() {
  auto cont = init<Cont>();
  using clock = std::chrono::high_resolution_clock;

  auto start = clock::now();
  typename Cont::value_type sum = 0;
  for (const auto e : cont) {
    sum += e;
  }
  auto iter_dur =
      std::chrono::duration<double, std::milli>(clock::now() - start).count();

  start = clock::now();
  auto it = do_find(cont);
  assert(it != cont.end());
  auto find_dur =
      std::chrono::duration<double, std::milli>(clock::now() - start).count();

  std::cout << std::setprecision(5) << "iter ms= " << std::setw(7) << iter_dur
            << "\tfind ms= " << std::setw(7) << find_dur
            << "\telems= " << cont.size() << " sum= " << sum << " find=" << *it
            << "\tcontainer= " << typeid(cont).name() << std::endl;
}
} // namespace (anonymous)

namespace vt {
  inline namespace detail {
    template <const auto kCols = 80_z>
    consteval auto line(char sep) noexcept -> vt::array<char, kCols> {
      return vt::array<char, kCols>().fill(sep);
    }
  } // namespace vt::inline detail

  template <class T> void run_bench() try {
    benchmark<vt::array<T, kSize>>();
    benchmark<std::array<T, kSize>>();
    benchmark<std::vector<T>>();

    std::cout.put('\n')
      << "+---------------------------------------------------------------+\n"
      << "|                         Reverse Order                         |\n"
      << "+---------------------------------------------------------------+\n"
      << std::endl;

    benchmark<std::vector<T>>();
    benchmark<std::array<T, kSize>>();
    benchmark<vt::array<T, kSize>>();
  }  catch (std::exception const& e) {
    std::clog << "Caught exception:\t" << std::quoted(e.what()) << '\n';
    throw; // rethrow e
  }
} // namespace vt
auto main() -> int {
  vt::run_bench<u32>();
  vt::run_bench<u64>();
}
