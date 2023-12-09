#include <common.hpp>

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  string::const_iterator curr_it = str.begin();

  int answer = 0;

  function<int(vector<int>)> extrapolate_val = [&](vector<int> nums) -> int {
    vector<int> diffs;
    for (int i = 0; i < nums.size()-1; i++) {
      diffs.push_back(nums[i+1]-nums[i]);
    }
    
    if (all_of(diffs.begin(), diffs.end(), [](int i) { return !i; }))
      return nums.back();

    return nums.back() + extrapolate_val(diffs);
  };

  while (*curr_it) {
    vector<int> nums;

    while (true) {
      nums.push_back(parse_int(curr_it));
      if (*curr_it++ == '\n') break;
    }

    if (part == 2)
      std::reverse(nums.begin(), nums.end());
    
    answer += extrapolate_val(nums);
  }

  print("{}\n", answer);

  return 0;
}
