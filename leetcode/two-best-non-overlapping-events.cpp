#include <bits/stdc++.h>
using namespace std;

class Solution {
  using pii = pair<int, int>;

 public:
  int maxTwoEvents(vector<vector<int>>& events) {
    sort(events.begin(), events.end());

    int best_seen = 0;
    int ans = 0;

    priority_queue<pii, vector<pii>, greater<pii>> pq;

    for (const auto& ev : events) {
      const int start = ev[0];
      const int end = ev[1];
      const int value = ev[2];

      while (!pq.empty() && pq.top().first < start) {
        best_seen = max(best_seen, pq.top().second);
        pq.pop();
      }

      ans = max(ans, value + best_seen);
      pq.emplace(end, value);
    }

    return ans;
  }
};
