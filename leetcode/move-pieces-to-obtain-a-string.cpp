#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool canChange(string start, string target) {
    const int n = start.size();
    map<int, char> s, t;

    for (int i = 0; i < n; i++) {
      if (start[i] != '_') s[i] = start[i];
      if (target[i] != '_') t[i] = target[i];
    }

    if (s.size() != t.size()) return false;

    for (int i = 0; i < n; i++) {
      if (start[i] == 'L' && target[i] == 'R') return false;
      if (start[i] == 'R' && target[i] == 'L') return false;
      if (start[i] == '_' && target[i] == 'R') return false;
      if (start[i] == 'L' && target[i] == '_') return false;

      if (start[i] == '_' && target[i] == 'L') {
        if (s.begin()->second != 'L') return false;

        start[s.begin()->first] = '_';
        s.erase(s.begin());
      }

      if (start[i] == 'R' && target[i] == '_') {
        if (t.begin()->second != 'R') return false;

        target[t.begin()->first] = '_';
        t.erase(t.begin());
      }

      s.erase(i);
      t.erase(i);
    }

    return true;
  }
};
