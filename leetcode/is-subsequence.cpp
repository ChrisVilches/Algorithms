#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool isSubsequence(const string s, const string t) {
    int i = 0;
    for (const char c : t) i += s[i] == c;

    return i == (int)s.size();
  }
};
