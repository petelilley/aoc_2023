#include <common.hpp>

auto not_digit = [](char c) { return !isdigit(c); };
auto is_space = [](char c) { return c == ' '; };

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  string::const_iterator curr_it = str.begin();

  int answer = 0;

  map<int, int> copies;
  while (*curr_it) {
    parse_while(curr_it, not_digit); // 'Card '
    int round = parse_uint(curr_it);
    parse_while(curr_it, not_digit); // ': '
    
    set<int> winning;
    while (*curr_it != '|') {
      int num = parse_uint(curr_it);
      winning.insert(num);
      parse_while(curr_it, is_space);
    }
    parse_while(curr_it, not_digit);

    int matches = 0;
    while (*curr_it != '\n') {
      parse_while(curr_it, is_space);
      int num = parse_uint(curr_it);
      
      matches += winning.contains(num);
    }
    ++curr_it; // \n

    if (part == 1) {
      if (matches == 1) answer++;
      else if (matches) answer += pow(2, matches-1);
    }
    else if (part == 2) {
      if (!copies.count(round)) copies[round] = 1;

      for (int i = 1; i <= matches; i++) {
        if (!copies.count(round + i))
          copies[round+i] = 1+copies[round];
        else
          copies[round+i] += copies[round];
      }
    }
  }

  if (part == 2) {
    for (auto [round, num] : copies)
      answer += num;
  }

  print("{}\n", answer);

  return 0;
}
