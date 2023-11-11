#include "../../src/interval_addition/actual/IntervalAddition.h"

#include <list>
#include <iostream>
#include <limits>

template <typename T>
struct min {
  constexpr T operator()(const T& l, const T& r) const noexcept {
    return std::less<T>()(l, r) ? l : r;
  }
};

int main() {
  std::list<int> l = {1, 2, 3, 4};
  IntervalAddition<int> tree(l.begin(), l.end(), min<int>(), std::plus<>(),
                         std::numeric_limits<int>::max(), 0);
  std::cout << tree.get_min(0, 3) << std::endl;
  tree.add(2, 0, 2);
  for (int i = 0; i < 4; ++i) {
    std::cout << tree.get_min(i, i) << " ";
  }
  std::cout << std::endl << tree.get_min(1, 2) << std::endl;
  return 0;
}
