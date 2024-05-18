#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool isIsomorphic(string s, string t) {
    map<char, char> change;

    if (s.size() != t.size()) {
      return false;
    }

    set<char> used;

    for (int i = 0; i < (int)s.size(); i++) {
      if (change.count(s[i])) continue;
      if (used.count(t[i])) continue;

      change[s[i]] = t[i];
      used.emplace(t[i]);
    }

    for (auto& c : s) {
      c = change[c];
    }

    return s == t;
  }
};
