#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minFlips(const string s) {
    const size_t n = s.size();

    int ans = INT_MAX;

    int counts[2][2];
    memset(counts, 0, sizeof counts);

    for (size_t i = 0; i < n; i++) {
      counts[i % 2][s[i] == '0']++;
    }

    for (size_t i = 0; i < n; i++) {
      ans = min(ans, counts[0][0] + counts[1][1]);
      ans = min(ans, counts[0][1] + counts[1][0]);

      counts[i % 2][s[i] == '0']--;
      counts[(i + n) % 2][s[(i + n) % n] == '0']++;
    }

    return ans;
  }
};
