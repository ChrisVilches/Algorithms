#include <bits/stdc++.h>
using namespace std;

class Solution {
  int length(const pair<int, int> p) { return p.second - p.first; }

 public:
  int maxFreeTime(const int event_time, const size_t k, const vector<int>& start,
                  const vector<int>& end) {
    vector<pair<int, int>> spaces;

    spaces.emplace_back(0, start.front());
    for (size_t i = 1; i < start.size(); i++) spaces.emplace_back(end[i - 1], start[i]);
    spaces.emplace_back(end.back(), event_time);

    int ans = 0;
    int curr = 0;

    const size_t win_size = k + 1;

    for (size_t i = 0; i < win_size; i++) {
      curr += length(spaces[i]);
    }

    ans = curr;

    for (size_t i = 0; i < spaces.size() - win_size; i++) {
      curr += length(spaces[i + win_size]);
      curr -= length(spaces[i]);
      ans = max(ans, curr);
    }

    return ans;
  }
};
