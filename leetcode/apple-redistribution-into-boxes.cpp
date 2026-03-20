#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minimumBoxes(const vector<int>& apple, vector<int>& capacity) {
    sort(capacity.begin(), capacity.end());
    int apples = accumulate(apple.begin(), apple.end(), 0);

    int ans = 0;

    for (const int c : views::reverse(capacity)) {
      if (apples <= 0) break;

      apples -= c;
      ans++;
    }

    return ans;
  }
};
