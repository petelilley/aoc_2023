#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  string::const_iterator curr_it = str.begin();

  int64_t answer = 0;



  print("{}\n", answer);

  return 0;
}
