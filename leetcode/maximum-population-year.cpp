#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maximumPopulation(vector<vector<int>>& logs) {
    vector<pair<int, int>> events;
    for (const auto& log : logs) {
      events.emplace_back(log[0], 1);
      events.emplace_back(log[1], -1);
    }
    sort(events.begin(), events.end());
    int best = 0;
    int curr = 0;
    int year = 0;
    for (const auto& [y, d] : events) {
      curr += d;
      if (curr > best) {
        year = y;
        best = curr;
      }
    }
    return year;
  }
};
