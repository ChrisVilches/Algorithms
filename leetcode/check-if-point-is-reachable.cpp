#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool isReachable(int targetX, int targetY) {
    return __builtin_popcount(gcd(targetX, targetY)) == 1;
  }
};
