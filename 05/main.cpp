#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  string::const_iterator curr_it = str.begin();

  if (part == 2) {
    print("AAAAAAAHHHHH!!\n");
    return 0;
  }

  uint64_t answer = 0;

  curr_it += 7;
  vector<uint64_t> values;
  while (true) {
    values.push_back(parse_uint(curr_it));
    if (*curr_it == '\n') break;
    ++curr_it;
  }

  curr_it += 2;

  map<uint64_t, uint64_t> mapped;

  for (int i = 0; i < 7; i++) {
    parse_line(curr_it);

    for (auto value : values) {
      mapped[value] = value;
    }

    while (*curr_it && *curr_it != '\n') {
      uint64_t dest_start = parse_uint(curr_it);
      ++curr_it;
      uint64_t src_start = parse_uint(curr_it);
      ++curr_it;
      uint64_t len = parse_uint(curr_it);
      ++curr_it;

      for (auto value : values) {
        if (value >= src_start && value < src_start + len) {
          mapped[value] = dest_start + (value - src_start);
        }
      }
    }
    if (*curr_it == '\n')
      ++curr_it;

    values.clear();
    for (auto& [from, to] : mapped) {
      values.push_back(to);
    }
    mapped.clear();

  }

  answer = UINT64_MAX;

  for (int i = 0; i < values.size(); i++) {
    answer = min(answer, values[i]);
  }

  print("{}\n", answer);

  return 0;
}
