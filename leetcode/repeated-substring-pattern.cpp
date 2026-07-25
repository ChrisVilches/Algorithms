#include <bits/stdc++.h>
using namespace std;

vector<int> compute_z(const string& s) {
  const int n = s.size();
  vector<int> z(n, 0);

  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i < r) z[i] = min(r - i, z[i - l]);

    while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;

    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }

  return z;
}

class Solution {
 public:
  bool repeatedSubstringPattern(const string s) {
    const int n = s.size();
    const vector<int> z = compute_z(s);

    for (int k = 1; k < n; k++) {
      if (n % k == 0 && z[k] == n - k) return true;
    }

    return false;
  }
};
