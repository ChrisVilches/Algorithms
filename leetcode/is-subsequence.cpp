#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool isSubsequence(const string s, const string t) {
    if (s.empty()) return true;

    int i = 0;

    for (const char c : t) {
      if (s[i] == c) i++;
      if (i == (int)s.size()) return true;
    }

    return false;
  }
};
