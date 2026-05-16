#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string removeOccurrences(const string text, const string part) {
    stack<int> s;
    s.emplace(-1);

    string ans;

    vector<int> lps(part.size());
    lps.front() = 0;
    for (size_t i = 1, j = 0; i < part.size(); i++) {
      while (j != 0 && part[i] != part[j]) j = lps[j - 1];
      if (part[i] == part[j]) j++;
      lps[i] = j;
    }

    size_t j = 0;

    for (const char c : text) {
      ans += c;

      while (j != 0 && c != part[j]) {
        j = lps[j - 1];
      }

      if (c == part[j]) {
        s.emplace(j);
        j++;
      } else {
        s.emplace(-1);
      }

      if (j == part.size()) {
        for (size_t it = 0; it < part.size(); it++) {
          s.pop();
          ans.pop_back();
        }

        j = s.top() + 1;
      }
    }

    return ans;
  }
};
