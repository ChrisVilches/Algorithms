#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int numberOfSubstrings(const string s) {
    const int n = s.size();
    array<int, 3> freq{};

    int ans = 0;

    const auto ok = [&freq]() { return freq[0] && freq[1] && freq[2]; };

    for (int i = 0, j = 0; i < n; i++) {
      while (j < n && !ok()) {
        freq[s[j] - 'a']++;
        j++;
      }

      if (ok()) ans += n - j + 1;

      freq[s[i] - 'a']--;
    }

    return ans;
  }
};
