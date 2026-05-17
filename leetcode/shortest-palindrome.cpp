#include <bits/stdc++.h>
using namespace std;

class Solution {
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

 public:
  string shortestPalindrome(const string s) {
    const string inv{s.rbegin(), s.rend()};

    const vector<int> z = compute_z(s + '$' + inv);

    size_t size = inv.size();

    for (size_t i = s.size() + 1; i < z.size(); i++) {
      if (i + z[i] == z.size()) {
        size = min(size, inv.size() - z[i]);
      }
    }

    return inv.substr(0, size) + s;
  }
};
