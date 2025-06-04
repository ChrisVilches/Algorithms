#include <bits/stdc++.h>
using namespace std;

class Solution {
  template <typename T>
  using min_heap = priority_queue<T, vector<T>, greater<T>>;

 public:
  int mostBooked(const int n, vector<vector<int>>& meetings) {
    sort(meetings.begin(), meetings.end());

    min_heap<int> available;
    for (int i = 0; i < n; i++) available.push(i);

    min_heap<pair<long long, int>> busy;
    vector<int> ans(n, 0);

    for (const auto& m : meetings) {
      const long long start = m[0], end = m[1];

      while (!busy.empty() && busy.top().first <= start) {
        available.push(busy.top().second);
        busy.pop();
      }

      if (available.empty()) {
        const auto [end_time, room] = busy.top();
        busy.pop();
        const long long new_end = end_time + (end - start);
        busy.emplace(new_end, room);
        ans[room]++;
      } else {
        const int room = available.top();
        available.pop();
        busy.emplace(end, room);
        ans[room]++;
      }
    }

    return max_element(ans.begin(), ans.end()) - ans.begin();
  }
};
