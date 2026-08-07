#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> avoidFlood(const vector<int>& rains) {
    const int n = rains.size();

    unordered_map<int, int> latest_idx;
    vector<int> ans(n, -1), next_idx(n, -1);

    for (int i = 0; i < n; i++) {
      if (rains[i] == 0) continue;

      if (latest_idx.count(rains[i])) {
        const int idx = latest_idx[rains[i]];
        next_idx[idx] = i;
      }

      latest_idx[rains[i]] = i;
    }

    unordered_set<int> active;
    priority_queue<int> pq;

    for (int i = 0; i < n; i++) {
      if (rains[i] > 0) {
        if (active.count(rains[i])) return {};

        active.emplace(rains[i]);

        if (next_idx[i] != -1) pq.emplace(-next_idx[i]);
      } else {
        ans[i] = 1;

        if (!pq.empty()) {
          const int idx = -pq.top();
          pq.pop();
          const int r = rains[idx];
          active.erase(r);
          ans[i] = r;
        }
      }
    }

    return ans;
  }
};
