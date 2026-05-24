#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxDistance(const vector<int>& colors) {
    const int n = colors.size();
    vector<int> mn(n), mx(n);
    mn.back() = colors.back();
    mx.back() = colors.back();

    for (int i = n - 2; i >= 0; i--) {
      mn[i] = min(colors[i], mn[i + 1]);
      mx[i] = max(colors[i], mx[i + 1]);
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
      int lo = i;
      int hi = n - 1;

      while (lo <= hi) {
        const int mid = (lo + hi) / 2;

        if (colors[i] != mn[mid] || colors[i] != mx[mid]) {
          lo = mid + 1;
        } else {
          hi = mid - 1;
        }
      }
      ans = max(ans, hi - i);
    }

    return ans;
  }
};
