#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int bulbSwitch(int n) {
    int ans = 0;

    for (int odd = 3; n > 0; odd += 2) {
      n -= odd;
      ans++;
    }

    return ans;
  }
};
