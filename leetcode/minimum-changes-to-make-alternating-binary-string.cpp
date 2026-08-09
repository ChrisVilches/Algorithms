#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minOperations(const string s) {
    array<int, 2> vals{};

    for (size_t i = 0; i < s.size(); i++) {
      vals[0] += s[i] == "01"[i % 2];
      vals[1] += s[i] == "10"[i % 2];
    }

    return min(vals.front(), vals.back());
  }
};
