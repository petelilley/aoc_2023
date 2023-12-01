#include <common.hpp>

static const array<string, 9> NUMBERS = {
  "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
};

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  string::const_iterator curr_it = str.begin();

  int answer = 0;

  while (*curr_it) {
    string line = parse_line(curr_it);

    int first = 0, last = 0;
    for (int i = 0; i < line.size(); ++i) {
      if (isdigit(line[i])) {
        last = line[i] - '0';
        if (!first) {
          first = line[i] - '0';
        }
      }

      if (part == 2) {
        for (int j = 0; j < NUMBERS.size(); ++j) {
          string offset_str = string(line.c_str() + i);
          if (offset_str.starts_with(NUMBERS[j])) {
            last = j+1;
            if (!first) {
              first = j+1;
            }
            break;
          }
        }
      }
    }
    answer += first*10 + last;
  }

  print("{}\n", answer);

  return 0;
}
