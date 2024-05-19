#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  long long minimumSteps(string s) {
    long long ans = 0;
    const int n = s.size();

    for (int i = 0, j = 0; i < n; i++) {
      if (s[i] == '0') {
        ans += i - j;
        j++;
      }
    }

    return ans;
  }
};
