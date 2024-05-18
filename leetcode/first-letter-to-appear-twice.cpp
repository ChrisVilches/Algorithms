#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  char repeatedCharacter(const string s) {
    int seen = 0;

    for (const char c : s) {
      const int index = c - 'a';
      if ((seen & (1 << index)) != 0) return c;

      seen = seen | (1 << index);
    }

    assert(false);
  }
};
