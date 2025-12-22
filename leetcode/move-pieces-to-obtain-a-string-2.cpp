#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool canChange(const string start, const string target) {
    const int n = start.size();

    const int count1 = count(start.begin(), start.end(), '_');
    const int count2 = count(target.begin(), target.end(), '_');
    if (count1 != count2) return false;

    for (int i = 0, j = 0; i < n; i++) {
      if (start[i] == '_') continue;

      for (; j < n; j++) {
        if (target[j] == '_') continue;
        if (start[i] != target[j]) return false;
        if (start[i] == 'L') {
          if (i < j) return false;
        } else {
          if (i > j) return false;
        }
        j++;
        break;
      }
    }

    return true;
  }
};
