#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maximumSwap(const int num) {
    string s = to_string(num);

    set<tuple<pair<char, int>, char, size_t>> digits;

    for (size_t i = 0; i < s.size(); i++) {
      const pair<char, int> sort{-s[i], -i};
      digits.emplace(sort, s[i], i);
    }

    for (const auto& [_, digit, idx] : digits) {
      for (size_t i = 0; i < idx; i++) {
        if (digit <= s[i]) continue;

        swap(s[idx], s[i]);
        return stoi(s);
      }
    }

    return stoi(s);
  }
};
