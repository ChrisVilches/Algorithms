#include <bits/stdc++.h>
using namespace std;

class Solution {
  void compress(string& s) const {
    const int n = s.size();
    int i = 0;
    bool space = true;

    for (int j = 0; j < n; j++) {
      if (s[j] == ' ') {
        if (!space) {
          s[i++] = ' ';
          space = true;
        }
      } else {
        s[i++] = s[j];
        space = false;
      }
    }

    if (i > 0 && s[i - 1] == ' ') i--;
    s.resize(i);
  }

 public:
  string reverseWords(string s) {
    reverse(s.begin(), s.end());
    compress(s);

    for (auto start = s.begin();;) {
      const auto it = find(start, s.end(), ' ');
      reverse(start, it);

      if (it == s.end()) break;

      start = next(it);
    }

    return s;
  }
};
