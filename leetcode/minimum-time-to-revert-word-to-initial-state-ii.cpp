#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> z_function(string s) {
    const int n = s.size();
    vector<int> Z(n);

    int L = 0, R = 0;

    for (int i = 1; i < n; i++) {
      if (i <= R) Z[i] = min(R - i + 1, Z[i - L]);

      while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) Z[i]++;

      if (i + Z[i] - 1 > R) {
        L = i;
        R = i + Z[i] - 1;
      }
    }

    return Z;
  }

 public:
  int minimumTimeToInitialState(const string word, const int k) {
    const int n = word.size();

    const vector<int> z = z_function(word);

    int ans = 1;

    for (int i = k; i < n; i += k) {
      if (i + z[i] == n) break;

      ans++;
    }

    return ans;
  }
};
