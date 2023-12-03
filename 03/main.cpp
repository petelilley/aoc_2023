#include <common.hpp>

using Coordinate = pair<int, int>;

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  string::const_iterator curr_it = str.begin();

  int answer = 0;

  vector<string> lines;
  while (*curr_it) {
    string line = parse_line(curr_it) + '.'; // Give it an extra column to make numbers at the end work.
    lines.push_back(line);
  }

  int dim_x = lines.size(), dim_y = lines[0].length();

  map<Coordinate, vector<int>> gears;
  for (int x = 0; x < dim_x; x++) {
    int num = 0;
    bool part_num = false;
    set<Coordinate> num_gears;
    for (int y = 0; y < dim_y; y++) {
      char c = lines[x][y];
      if (isdigit(c)) {
        num = num*10 + c - '0';
        for (int dx = -1; dx <= 1; dx++) {
          for (int dy = -1; dy <= 1; dy++) {
            int a = x+dx, b = y+dy;
            if (a < 0 || b < 0 || a >= dim_x || b >= dim_y) continue;

            char v = lines[a][b];
            if (!isdigit(v) && v != '.') {
              part_num = true;
            }
            if (v == '*') {
              num_gears.insert(Coordinate(a,b));
            }
          }
        }
      }
      else if (num) {
        if (part_num) {
          if (part == 1) {
            answer += num;
          }
        }
        for (auto gear : num_gears) {
          if (!gears.count(gear)) gears[gear] = {};
          gears[gear].push_back(num);
        }
        num_gears.clear();

        part_num = false;
        num = 0;
      }
    }
  }

  if (part == 2) {
    for (auto& [coord, nums] : gears) {
      if (nums.size() == 2) {
        answer += nums[0] * nums[1];
      }
    }
  }

  print("{}\n", answer);

  return 0;
}
