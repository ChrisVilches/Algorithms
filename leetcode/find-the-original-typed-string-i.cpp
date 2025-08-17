#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int possibleStringCount(const string word) {
    vector<int> counts;
    char prev_char = '\0';

    for (const char c : word) {
      if (counts.empty() || c != prev_char) {
        counts.emplace_back(0);
      }

      counts.back()++;
      prev_char = c;
    }

    int ans = 1;

    for (const int c : counts) {
      ans += c - 1;
    }

    return ans;
  }
};
