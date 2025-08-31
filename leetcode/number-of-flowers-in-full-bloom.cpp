#include <bits/stdc++.h>
using namespace std;

class Solution {
  using tiii = tuple<int, int, int>;

 public:
  vector<int> fullBloomFlowers(const vector<vector<int>>& flowers,
                               const vector<int>& people) {
    vector<tiii> events;

    for (const auto& f : flowers) {
      events.emplace_back(f.front(), 0, 1);
      events.emplace_back(f.back(), 2, -1);
    }

    for (size_t i = 0; i < people.size(); i++) {
      events.emplace_back(people[i], 1, i);
    }

    sort(events.begin(), events.end());

    vector<int> ans(people.size());
    int curr = 0;

    for (const auto& [_, type, data] : events) {
      if (type == 0 || type == 2) {
        curr += data;
      } else {
        const int idx = data;
        ans[idx] = curr;
      }
    }

    return ans;
  }
};
