#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minimumRecolors(const string blocks, const int k) {
    const int n = blocks.size();
    int ans = 1e9;

    int curr_window = count(blocks.begin(), blocks.begin() + k, 'W');

    for (int i = 0; i <= n - k; i++) {
      ans = min(ans, curr_window);
      curr_window -= blocks[i] == 'W';

      if (i + k < n) {
        curr_window += blocks[i + k] == 'W';
      }
    }

    return ans;
  }
};
