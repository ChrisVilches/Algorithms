#include <bits/stdc++.h>
using namespace std;

class Solution {
  enum { NONE, UP, DOWN };

 public:
  int longestMountain(const vector<int>& arr) {
    int start = -1;
    int state = NONE;
    int ans = 0;

    for (int i = 1; i < static_cast<int>(arr.size()); i++) {
      const int prev = arr[i - 1];
      const int curr = arr[i];

      switch (state) {
        case NONE:
          if (prev < curr) {
            state = UP;
            start = i - 1;
          }
          break;
        case UP:
          if (curr == prev) {
            state = NONE;
          } else if (prev > curr) {
            state = DOWN;
          }
          break;
        case DOWN:
          if (prev == curr) {
            state = NONE;
          } else if (prev < curr) {
            state = UP;
            start = i - 1;
          }
          break;
      }

      if (state == DOWN) {
        ans = max(ans, i - start + 1);
      }
    }

    return ans;
  }
};
