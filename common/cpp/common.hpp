#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cctype>
#include <ctime>
#include <cassert>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <functional>
#include <memory>
#include <utility>
#include <limits>
#include <numeric>
#include <iterator>
#include <chrono>
#include <random>
#include <array>
#include <tuple>
#include <initializer_list>
#include <filesystem>
#include <variant>
#include <optional>
#include <queue>
#include <regex>
#include <stack>

#include <fmt/core.h>

using namespace std;
using namespace fmt;

// --- File Stuff ---

// Returns the contents of a file as a string.
string get_file(filesystem::path path = "input.txt");

struct Init {
  string file;
  int day;
  int part = 1;
};

// Returns the initial data for the program.
Init aoc_init(int argc, char** argv);

using CharCondition = function<bool(char)>;

// Count/parse characters while a condition is true.
ptrdiff_t count_while(string::const_iterator curr_it, CharCondition cond_func);
string parse_while(string::const_iterator& curr_it, CharCondition cond_func);

// Count/parse characters until a character is met.
ptrdiff_t count_until(string::const_iterator curr_it, string chars);
string parse_until(string::const_iterator& curr_it, string chars);

// Parses characters until a \n. The \n is then skipped.
string parse_line(string::const_iterator& curr_it);

double parse_double(string::const_iterator& curr_it);
int64_t parse_int(string::const_iterator& curr_it);
uint64_t parse_uint(string::const_iterator& curr_it);
