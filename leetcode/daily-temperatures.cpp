#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> dailyTemperatures(const vector<int>& temperatures) {
    vector<int> ans(temperatures.size(), 0);

    stack<int> s;

    for (size_t i = 0; i < temperatures.size(); i++) {
      while (!s.empty() && temperatures[s.top()] < temperatures[i]) {
        ans[s.top()] = i - s.top();
        s.pop();
      }

      s.emplace(i);
    }

    return ans;
  }
};
