#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int minNumberOperations(const vector<int>& target) {
    stack<int> s;
    s.push(0);

    int ans = 0;

    for (const int x : target) {
      ans += max(x - s.top(), 0);

      while (!s.empty() && s.top() < x) s.pop();

      s.push(x);
    }

    return ans;
  }
};
