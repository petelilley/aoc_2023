#include <common.hpp>

static const string COLORS[3] = { "red", "green", "blue" };

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  string::const_iterator curr_it = str.begin();

  int answer = 0;

  while (curr_it != str.end()) {
    curr_it += 5; // 'Game '
    int game_num = parse_uint(curr_it);
    curr_it++; // ':'

    int cubes[3] = {0, 0, 0};
    int set_cubes[3] = {0, 0, 0};

    while (true) {
      ++curr_it; // space
      int num = parse_uint(curr_it);
      ++curr_it; // space

      string color = parse_until(curr_it, ",;\n");
      for (int i = 0; i < 3; ++i) {
        if (color == COLORS[i]) {
          set_cubes[i] += num;
          break;
        }
      }

      char delim = *curr_it;

      if (delim == ';' || delim == '\n') { // End of set.
        for (int i = 0; i < 3; ++i) {
          cubes[i] = max(cubes[i], set_cubes[i]);
          set_cubes[i] = 0;
        }
      }

      ++curr_it;

      if (delim == '\n') break;
    }

    if (part == 1) {
      if (cubes[0] <= 12 && cubes[1] <= 13 && cubes[2] <= 14)
        answer += game_num;
    }
    else if (part == 2) {
      answer += cubes[0] * cubes[1] * cubes[2];
    }
  }

  print("{}\n", answer);

  return 0;
}
