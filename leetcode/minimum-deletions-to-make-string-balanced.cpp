#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minimumDeletions(const string s) {
    const int n = s.size();

    int ans = INT_MAX;

    vector<int> a(n + 1, 0);

    for (int i = n - 1; i >= 0; i--) {
      a[i] = a[i + 1] + (s[i] == 'a');
    }

    int b = 0;

    for (int i = 0; i < n; i++) {
      ans = min(ans, b + a[i]);
      b += (s[i] == 'b');
    }

    ans = min(ans, b);

    return ans;
  }
};
