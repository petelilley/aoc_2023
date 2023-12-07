#include <common.hpp>

int g_part;

enum HandType {
  FIVE_OF_KIND,
  FOUR_OF_KIND,
  FULL_HOUSE,
  THREE_OF_KIND,
  TWO_PAIR,
  ONE_PAIR,
  HIGH_CARD,
};

HandType find_type(map<char, int> counts) {
  HandType t = HIGH_CARD;
  for (auto& [card, count] : counts) {
    if (count == 5)
      t = FIVE_OF_KIND;
    else if (count == 4)
      t = FOUR_OF_KIND;
    else if (count == 3) {
      if (t == ONE_PAIR)
        t = FULL_HOUSE;
      else
        t = THREE_OF_KIND;
    }
    else if (count == 2) {
      if (t == ONE_PAIR)
        t = TWO_PAIR;
      else if (t == THREE_OF_KIND)
        t = FULL_HOUSE;
      else
        t = ONE_PAIR;
    }
  }
  return t;
}

struct Hand {
  char cards[5];
  int bid;
  HandType type = HIGH_CARD;

  Hand(char* cards, int bid) {
    memcpy(this->cards, cards, 5);
    this->bid = bid;

    map<char, int> counts;
    for (int i = 0; i < 5; i++) {
      if (counts.count(cards[i]))
        counts[cards[i]]++;
      else
        counts[cards[i]] = 1;
    }

    if (g_part == 1) {
      type = find_type(counts);
    }
    else if (g_part == 2) {
      int j_num = counts.count('J') ? counts['J'] : 0;
      if (j_num == 5)
        type = FIVE_OF_KIND;
      else {
        for (auto& [card, count] : counts) {
          if (card == 'J') continue;

          map<char, int> new_counts = counts;
          new_counts.erase('J');
          new_counts[card] += j_num;

          type = min(type, find_type(new_counts));
        }
      }
    }
  }

  bool operator<(const Hand& other) const {
    if (type != other.type) {
      return type > other.type;
    }

    for (int i = 0; i < 5; i++) {
      char c = cards[i];
      if (c == other.cards[i]) continue;

#define CHECK_CARD(card) \
      do { \
        if (c == (card)) return false; \
        if (other.cards[i] == (card)) return true; \
      } while (0)

      CHECK_CARD('A');
      CHECK_CARD('K');
      CHECK_CARD('Q');

      if (g_part == 1) {
        CHECK_CARD('J');
      }

      CHECK_CARD('T');

      for (int j = 9; j >= 2; j--) {
        CHECK_CARD('0' + j);
      }
    }
  }
};

int main(int argc, char** argv) {
  auto [str, day, part] = aoc_init(argc, argv);
  string::const_iterator curr_it = str.begin();
  g_part = part;

  int answer = 0;

  vector<Hand> hands;

  while (*curr_it) {
    char cards[5];
    for (int i = 0; i < 5; i++) {
      cards[i] = *curr_it++;
    }
    ++curr_it;

    int bid = parse_uint(curr_it);
    ++curr_it;

    hands.emplace_back(cards, bid);
  }

  sort(hands.begin(), hands.end());

  for (int i = 0; i < hands.size(); i++) {
    answer += hands[i].bid * (i + 1);
  }

  print("{}\n", answer);

  return 0;
}
