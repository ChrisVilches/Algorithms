#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool carPooling(const vector<vector<int>>& trips, const int capacity) {
    vector<pair<int, int>> events;

    for (const auto& trip : trips) {
      const int people = trip[0];
      const int from = trip[1];
      const int to = trip[2];
      events.emplace_back(from, people);
      events.emplace_back(to, -people);
    }

    sort(events.begin(), events.end());

    int curr = 0;

    for (const auto& [_, d] : events) {
      curr += d;
      if (curr > capacity) return false;
    }

    return true;
  }
};
