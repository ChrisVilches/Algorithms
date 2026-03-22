#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool is_upper(const char c) const { return 'A' <= c && c <= 'Z'; }

 public:
  int numberOfSpecialChars(const string word) {
    unordered_map<char, int> last_lower, first_upper;

    for (size_t i = 0; i < word.size(); i++) {
      const char c = tolower(word[i]);

      if (is_upper(word[i])) {
        if (first_upper.count(c)) continue;
        first_upper[c] = i;
      } else {
        last_lower[c] = i;
      }
    }

    int ans = 0;

    for (char c = 'a'; c <= 'z'; c++) {
      if (!last_lower.count(c)) continue;
      if (!first_upper.count(c)) continue;

      ans += last_lower[c] < first_upper[c];
    }

    return ans;
  }
};
