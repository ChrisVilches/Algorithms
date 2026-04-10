#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int closestTarget(const vector<string>& words, const string target, const int start) {
    int ans = INT_MAX;
    const int n = words.size();

    for (int i = start; i <= start + n; i++) {
      if (words[i % n] == target) {
        ans = min(ans, i - start);
        break;
      }
    }

    for (int i = start; i >= start - n; i--) {
      if (words[(i + n) % n] == target) {
        ans = min(ans, start - i);
        break;
      }
    }

    return ans == INT_MAX ? -1 : ans;
  }
};
