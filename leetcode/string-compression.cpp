#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int compress(vector<char>& chars) {
    vector<pair<char, int>> res;

    for (const char c : chars) {
      if (res.empty() || res.back().first != c) {
        res.emplace_back(c, 0);
      }

      res.back().second++;
    }

    int k = 0;

    for (const auto& [c, count] : res) {
      chars[k++] = c;
      if (count > 1) {
        for (const char d : to_string(count)) {
          chars[k++] = d;
        }
      }
    }

    return k;
  }
};
