#include <bits/stdc++.h>
using namespace std;

class Solution {
  using pii = pair<int, int>;

 public:
  int maxEvents(const vector<vector<int>>& input) {
    unordered_map<int, vector<int>> events;

    int max_day = 0;

    for (size_t i = 0; i < input.size(); i++) {
      const vector<int>& vec = input[i];
      events[vec.front()].emplace_back(i);
      max_day = max(max_day, vec.back());
    }

    priority_queue<pii, vector<pii>, greater<pii>> active;

    int ans = 0;

    for (int x = 0; x <= max_day; x++) {
      for (const int idx : events[x]) {
        active.push({input[idx].back(), idx});
      }

      while (!active.empty() && active.top().first < x) {
        active.pop();
      }

      if (!active.empty()) {
        ans++;
        active.pop();
      }
    }

    return ans;
  }
};
