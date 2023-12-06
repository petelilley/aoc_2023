#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  string::const_iterator curr_it = str.begin();

  uint64_t answer = 1;

  auto parse_numbers = [&]() {
    vector<uint64_t> nums;
    uint64_t temp = 0;
    while (*curr_it != '\n') {
      if (part == 1) {
        parse_while(curr_it, [](char c) { return !isdigit(c); });
        nums.push_back(parse_int(curr_it));
      }
      else if (part == 2) {
        if (isdigit(*curr_it)) {
          temp = temp * 10 + (*curr_it - '0');
        }
        ++curr_it;
      }
    }
    if (part == 2) nums.push_back(temp);

    return nums;
  };

  vector<uint64_t> times = parse_numbers();
  ++curr_it;
  vector<uint64_t> distances = parse_numbers();

  for (int i = 0; i < times.size(); i++) {
    // x^2 - tx = d

    long double t = times[i];
    long double d = distances[i];

    // x = (t ± √(t²-4d)) ÷ 2
    uint64_t x0 = ceil((t - sqrt(t*t-4.0L*d)) / 2.0L); // Regular doubles can't handle this equation!!
    uint64_t x1 = floor((t + sqrt(t*t-4.0L*d)) / 2.0L);

    answer *= (x1 - x0)+1;
  }

  print("{}\n", answer);

  return 0;
}
