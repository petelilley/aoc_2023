#include <common.hpp>

string get_file(filesystem::path path) {
  ifstream file(path);
  if (!file) {
    print("Error: Could not open file \"{}\" from directory \"{}\"\n", path.string(), filesystem::current_path().string());
    exit(1);
  }

  string str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
  return str;
}

Init aoc_init(int argc, char** argv) {
  filesystem::path path;
  int part = 1;
  if (argc != 3) {
    print("Usage: {} [input file] [part number]\n", argv[0]);
    exit(1);
  }

  // Executable name (remove leading path)
  string day_substr = filesystem::path(argv[0]).filename().string().substr(0, 2);

  int day = stoi(day_substr);

  if (day < 1 || day > 25) {
    print("Error: Invalid day number: {}\n", day);
    exit(1);
  }

  path = argv[1];

  part = stoi(argv[2]);

  if (part != 1 && part != 2) {
    print("Error: Part number must be 1 or 2\n");
    exit(1);
  }

  print("Init day = {}, part = {}\n\n", day, part);

  return Init { get_file(path), day, part };
}

ptrdiff_t count_while(string::const_iterator curr_it, CharCondition cond_func) {
  ptrdiff_t count = 0;
  while (*curr_it && cond_func(*curr_it)) {
    ++curr_it;
    ++count;
  }
  return count;
}

string parse_while(string::const_iterator& curr_it, CharCondition cond_func) {
  ptrdiff_t count = count_while(curr_it, cond_func);
  string str(curr_it, curr_it + count);
  curr_it += count;
  return str;
}

ptrdiff_t count_until(string::const_iterator curr_it, string chars) {
  return count_while(curr_it, [&chars](char c) {
    return chars.find(c) == string::npos;
  });
}

string parse_until(string::const_iterator& curr_it, string chars) {
  ptrdiff_t count = count_until(curr_it, chars);
  string str(curr_it, curr_it + count);
  curr_it += count;
  return str;
}

string parse_line(string::const_iterator& curr_it) {
  string s = parse_until(curr_it, "\n");
  ++curr_it;
  return s;
}

double parse_double(string::const_iterator& curr_it) {
  // Handle + and -
  int sign = 1;
  if (*curr_it == '-') {
    sign = -1;
    ++curr_it;
  }
  else if (*curr_it == '+') {
    ++curr_it;
  }

  // Parse the integer part.
  string int_str = parse_while(curr_it, [](char c) {
    return isdigit(c);
  });
  
  if (*curr_it || (*curr_it != '.' && *curr_it != 'e' && *curr_it != 'E')) {
    return stoi(int_str) * sign;
  }

  double num = stoi(int_str);

  // Parse the decimal part.
  if (*curr_it == '.') {
    ++curr_it;
    string dec_str = parse_while(curr_it, [](char c) {
      return isdigit(c);
    });

    num = stod(int_str + "." + dec_str) * sign;
  }

  // Parse the exponent part.
  if (*curr_it == 'e' || *curr_it == 'E') {
    ++curr_it;
    int exp_sign = 1;
    if (*curr_it == '-') {
      exp_sign = -1;
      ++curr_it;
    }
    else if (*curr_it == '+') {
      ++curr_it;
    }

    string exp_str = parse_while(curr_it, [](char c) {
      return isdigit(c);
    });

    num *= pow(10, stoi(exp_str) * exp_sign);
  }

  return num;
}

int64_t parse_int(string::const_iterator& curr_it) {
  // Handle + and -
  int sign = 1;
  if (*curr_it == '-') {
    sign = -1;
    ++curr_it;
  }
  else if (*curr_it == '+') {
    ++curr_it;
  }

  // Parse the integer part.
  string int_str = parse_while(curr_it, [](char c) {
    return isdigit(c);
  });

  return stoll(int_str) * sign;
}

uint64_t parse_uint(string::const_iterator& curr_it) {
  // Parse the integer part.
  string int_str = parse_while(curr_it, [](char c) {
    return isdigit(c);
  });

  return stoull(int_str);
}
