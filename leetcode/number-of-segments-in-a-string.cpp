#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int countSegments(const string s) {
    if (s.empty()) return 0;

    bool seg = s.front() != ' ';
    int ans = seg;

    for (const char c : s) {
      if (seg) {
        if (c == ' ') {
          seg = false;
        }
      } else {
        if (c != ' ') {
          ans++;
          seg = true;
        }
      }
    }

    return ans;
  }
};
