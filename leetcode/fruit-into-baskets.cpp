#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int totalFruit(const vector<int>& fruits) const {
    const int n = fruits.size();
    int ans = 0;

    unordered_map<int, int> freq;

    for (int i = 0, j = 0; i < n; i++) {
      while (j < n && (freq.size() != 2 || freq.count(fruits[j]) != 0)) {
        freq[fruits[j]]++;

        ans = max(ans, j - i + 1);
        j++;
      }

      if (--freq[fruits[i]] == 0) {
        freq.erase(fruits[i]);
      }
    }

    return ans;
  }
};
