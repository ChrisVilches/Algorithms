#include <bits/stdc++.h>
using namespace std;

class RangeFreqQuery {
  unordered_map<int, vector<pair<int, int>>> counts;

 public:
  RangeFreqQuery(const vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
      const int val = arr[i];
      counts[val].emplace_back(i, counts[val].size() + 1);
    }
  }

  int query(const int left, const int right, const int value) const {
    if (!counts.count(value)) return 0;
    const auto& m = counts.at(value);

    const auto a = lower_bound(m.begin(), m.end(), make_pair(left, 0));
    if (a == m.end() || right < a->first) return 0;
    const auto b = prev(upper_bound(m.begin(), m.end(), make_pair(right, INT_MAX)));

    return b->second - a->second + 1;
  }
};
