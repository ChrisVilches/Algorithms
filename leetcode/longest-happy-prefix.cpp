#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string longestPrefix(const string s) {
    const int n = s.size();
    vector<int> lps(n);
    lps.front() = 0;

    for (int i = 1, len = 0; i < n; i++) {
      while (len != 0 && s[i] != s[len]) {
        len = lps[len - 1];
      }

      lps[i] = s[i] == s[len] ? ++len : 0;
    }

    return s.substr(0, lps.back());
  }
};
