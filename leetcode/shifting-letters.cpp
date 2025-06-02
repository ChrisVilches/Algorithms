#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string shiftingLetters(string s, const vector<int>& shifts) {
    long long accum = 0;

    for (int i = shifts.size() - 1; i >= 0; i--) {
      accum += shifts[i];
      s[i] = 'a' + ((s[i] - 'a' + accum) % 26);
    }

    return s;
  }
};
