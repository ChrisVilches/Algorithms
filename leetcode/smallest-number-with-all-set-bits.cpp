#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int smallestNumber(int n) {
    int i = 31;
    for (; i >= 0; i--) {
      if ((n & (1 << i))) break;
    }

    return (1 << (i + 1)) - 1;
  }
};
