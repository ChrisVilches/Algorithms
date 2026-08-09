#include <bits/stdc++.h>
using namespace std;

class Solution {
  int aux(const string& s, const int k, const char c) const {
    const int n = s.size();
    int res = 0;
    int count_other = 0;

    for (int i = 0, j = 0; i < n; i++) {
      while (j < n && count_other < k) {
        count_other += s[j] != c;
        j++;
      }

      while (j < n && s[j] == c) j++;

      res = max(res, j - i);
      count_other -= s[i] != c;
    }

    return res;
  }

 public:
  int characterReplacement(const string s, const int k) const {
    int ans = 0;

    for (char c = 'A'; c <= 'Z'; c++) {
      ans = max(ans, aux(s, k, c));
    }

    return ans;
  }
};
