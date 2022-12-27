#include <cstdio>
#include <functional>
#include <limits>

template <typename Fn, typename In, typename Out>
constexpr Out fold(Fn function, In* input, size_t length, Out initial) {
  if (length == 1) return function(initial, *input);
  return fold(function, input + 1, length - 1, function(initial, *input));
}

int main() {
  auto add = [](auto x, auto y) constexpr { return x + y; };
  auto min = [](auto x, auto y) constexpr { return x < y ? x : y; };
  auto max = [](auto x, auto y) constexpr { return x > y ? x : y; };
  auto greater_than_200 = [](size_t x, auto y) { return y > 200 ? x + 1 : x; };

  int data[]{100, 200, 300, 400, 500};
  size_t data_len = sizeof(data) / sizeof(data[0]);
  auto total = fold(add, data, data_len, 0);
  auto minimum = fold(min, data, data_len, std::numeric_limits<int>::max());
  auto maximum = fold(max, data, data_len, std::numeric_limits<int>::min());
  auto num_greater_than_200 = fold(greater_than_200, data, data_len, size_t{});
  printf("Sum: %d\nMinimum: %d\nMaximum: %d\nGreater than 200: %d\n", total,
         minimum, maximum, num_greater_than_200);
  return 0;
}
