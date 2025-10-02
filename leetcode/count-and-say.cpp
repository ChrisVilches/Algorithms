#include <bits/stdc++.h>
using namespace std;

class Solution {
  string encode(const string& s) const {
    vector<pair<char, int>> chars;
    for (const char c : s) {
      if (chars.empty() || chars.back().first != c) {
        chars.emplace_back(c, 0);
      }

      chars.back().second++;
    }
    string res = "";
    for (const auto& [c, count] : chars) {
      res += to_string(count);
      res += c;
    }
    return res;
  }

 public:
  string countAndSay(const int n) {
    string s = "1";

    for (int i = 0; i < n - 1; i++) {
      s = encode(s);
    }

    return s;
  }
};
