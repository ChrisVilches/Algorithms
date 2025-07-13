#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int pivotInteger(const int n) {
    int total = 0;
    for (int i = 1; i <= n; i++) total += i;

    int curr = 0;

    for (int i = 1; i <= n; i++) {
      curr += i;
      const int other = total - curr + i;
      if (curr == other) {
        return i;
      }
    }

    return -1;
  }
};
