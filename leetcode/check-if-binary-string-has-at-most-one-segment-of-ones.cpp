#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool checkOnesSegment(const string s) {
    int state = 0;

    for (const char c : s) {
      switch (state) {
        case 0:
          if (c == '1') state = 1;
          break;
        case 1:
          if (c == '0') state = 2;
          break;
        default:
          if (c == '1') return false;
      }
    }

    return true;
  }
};
