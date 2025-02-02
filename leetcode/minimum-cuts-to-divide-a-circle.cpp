#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int numberOfCuts(const int n) {
    if (n == 1) return 0;

    if (n % 2 == 0) {
      return n / 2;
    }

    return n;
  }
};
