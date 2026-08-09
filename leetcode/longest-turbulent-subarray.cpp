#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxTurbulenceSize(const vector<int>& arr) {
    int sgn = 0;
    int ans = 1;
    int curr = 1;

    for (size_t i = 1; i < arr.size(); i++) {
      const int prev = arr[i - 1];
      const int x = arr[i];
      const int new_sgn = (x > prev) - (x < prev);

      if (new_sgn == 0) {
        curr = 1;
        sgn = 0;
        continue;
      }

      curr = sgn == new_sgn ? 2 : curr + 1;
      sgn = new_sgn;
      ans = max(ans, curr);
    }

    return ans;
  }
};
