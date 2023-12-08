#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  string::const_iterator curr_it = str.begin();

  uint64_t answer = 1;

  map<string, pair<string,string>> elements;

  string instructions = parse_line(curr_it);
  ++curr_it;
  while (*curr_it) {
    string node = parse_until(curr_it, " ");
    curr_it += 4;
    string left = parse_until(curr_it, ",");
    curr_it += 2;
    string right = parse_until(curr_it, ")");
    curr_it += 2;
    elements[node] = make_pair(left, right);
  }

  vector<string> nodes;
  map<int, int> zposes;

  if (part == 1) {
    nodes.push_back("AAA");
  }
  else if (part == 2) {
    for (auto& [node, p] : elements) {
      if (node[2] == 'A') {
        nodes.push_back(node);
      }
    }
  }

  uint64_t n = 0;
  while (true) {
    for (int i = 0; i < nodes.size(); ++i) {
      const auto& [left, right] = elements[nodes[i]];

      char c = instructions[n % instructions.size()];
      if (c == 'R') nodes[i] = right;
      if (c == 'L') nodes[i] = left;

      if (nodes[i][2] == 'Z')
        zposes[i] = n+1;
    }
    n++;

    if (part == 1) {
      answer = n;
      if (nodes[0] == "ZZZ") break;
    }
    else if (part == 2) {
      if (zposes.size() == nodes.size()) {
        for (auto& [i, pos] : zposes) { // lcm
          answer = answer * pos / gcd(answer, pos);
        }
        break;
      }
    }
  }

  print("{}\n", answer);

  return 0;
}
