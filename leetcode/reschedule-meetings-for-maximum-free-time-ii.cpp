#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int maxFreeTime(const int t, const vector<int>& start, const vector<int>& end) {
    vector<pair<int, int>> spaces;

    spaces.emplace_back(0, start.front());
    for (size_t i = 1; i < start.size(); i++) spaces.emplace_back(end[i - 1], start[i]);
    spaces.emplace_back(end.back(), t);

    int ans = 0;

    unordered_map<int, pair<int, int>> by_start, by_end;

    for (const auto& s : spaces) {
      const int length = s.second - s.first;
      const pair<int, int> item{s.first, s.second};
      ans = max(length, ans);
      by_start[s.first] = item;
      by_end[s.second] = item;
    }

    for (size_t i = 0; i < spaces.size() - 1; i++) {
      const auto a = spaces[i];
      const auto b = spaces[i + 1];
      const int block_length = b.first - a.second;
      ans = max(ans, b.second - a.first - block_length);
    }

    sort(spaces.rbegin(), spaces.rend(), [](const auto a, const auto b) {
      return a.second - a.first < b.second - b.first;
    });

    for (size_t i = 0; i < start.size(); i++) {
      const int block_length = end[i] - start[i];

      const pair<int, int> adj1 = by_end[start[i]];
      const pair<int, int> adj2 = by_start[end[i]];

      for (const auto& s : spaces) {
        if (s == adj1 || s == adj2) continue;

        if (s.second - s.first >= block_length) {
          const int left = i == 0 ? start[i] : start[i] - end[i - 1];
          const int right = i == start.size() - 1 ? t - end[i] : start[i + 1] - end[i];

          ans = max(ans, block_length + left + right);
        }

        break;
      }
    }

    return ans;
  }
};
