#include <bits/stdc++.h>
using namespace std;

struct Event {
  bool enter;
  int x, h;
  bool operator<(const Event ev) const {
    if (x != ev.x) return x < ev.x;
    if (enter != ev.enter) return enter;
    if (enter == ev.enter && enter) return h > ev.h;
    return h < ev.h;
  }
};

class Solution {
 public:
  vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
    vector<Event> events;

    for (const auto& input : buildings) {
      const int x1 = input[0];
      const int x2 = input[1];
      const int h = input[2];
      events.emplace_back(true, x1, h);
      events.emplace_back(false, x2, h);
    }

    sort(events.begin(), events.end());

    multiset<int> curr;

    vector<vector<int>> result;

    const auto curr_height = [&]() -> int {
      return curr.empty() ? 0 : *prev(curr.end());
    };

    for (const auto& [enter, x, h] : events) {
      if (enter) {
        if (curr_height() < h) {
          result.emplace_back(vector<int>{x, h});
        }

        curr.emplace(h);
      } else {
        curr.erase(curr.find(h));

        if (curr_height() < h) {
          result.emplace_back(vector<int>{x, curr_height()});
        }
      }
    }

    return result;
  }
};
