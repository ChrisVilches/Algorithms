#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string compressedString(const string word) {
    vector<pair<char, int>> counts;

    for (const char c : word) {
      if (counts.empty() || counts.back().first != c) {
        counts.emplace_back(c, 0);
      }

      counts.back().second++;
    }

    string comp;

    for (const auto& [c, count] : counts) {
      int k = count;

      while (k > 0) {
        const int curr = min(k, 9);
        comp += to_string(curr);
        comp += c;
        k -= curr;
      }
    }

    return comp;
  }
};
