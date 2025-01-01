#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxChunksToSorted(const vector<int>& arr) {
    stack<pair<int, int>> s;

    for (const int x : arr) {
      int a = x;
      int b = x;

      while (!s.empty() && x < s.top().second) {
        a = min(a, s.top().first);
        b = max(b, s.top().second);
        s.pop();
      }

      s.emplace(a, b);
    }

    return s.size();
  }
};
