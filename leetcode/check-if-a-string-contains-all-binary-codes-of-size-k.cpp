#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool hasAllCodes(const string s, const int k) {
    vector<bool> present(pow(2, k), false);
    const int n = s.size();

    int curr = 0;

    for (int i = 0; i < min(k - 1, n); i++) {
      if (s[i] == '0') continue;
      curr += 1 << i;
    }

    for (int i = 0; i < n - k + 1; i++) {
      if (s[i + k - 1] == '1') {
        curr += 1 << (k - 1);
      }

      present[curr] = true;

      curr -= s[i] == '1';
      curr >>= 1;
    }

    return all_of(present.begin(), present.end(), identity{});
  }
};
