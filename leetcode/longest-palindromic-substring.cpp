#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string longestPalindrome(const string s) {
    const int n = s.size();

    string ans = s.substr(0, 1);

    for (int i = 0; i < n - 1; i++) {
      {
        int k = 0;
        for (; i - k - 1 >= 0 && i + k + 1 < n; k++) {
          if (s[i - k - 1] != s[i + k + 1]) break;
        }

        const int len = 2 * k + 1;
        if (len > static_cast<int>(ans.size())) {
          ans = s.substr(i - k, len);
        }
      }

      if (s[i] == s[i + 1]) {
        int k = 0;
        for (; i - k - 1 >= 0 && i + k + 2 < n; k++) {
          if (s[i - k - 1] != s[i + k + 2]) break;
        }

        const int len = 2 * (k + 1);
        if (len > static_cast<int>(ans.size())) {
          ans = s.substr(i - k, len);
        }
      }
    }

    return ans;
  }
};
