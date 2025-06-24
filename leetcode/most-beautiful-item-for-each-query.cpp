#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
    unordered_map<int, int> ans;

    sort(items.begin(), items.end());
    items.emplace_back(vector<int>{INT_MAX, INT_MAX});

    const set<int> sorted_queries{queries.begin(), queries.end()};

    int best = 0;

    auto it = sorted_queries.begin();

    for (const auto& item : items) {
      const int price = item.front();
      const int beauty = item.back();

      while (it != sorted_queries.end() && *it < price) {
        ans[*it] = best;
        it++;
      }

      best = max(best, beauty);
    }

    vector<int> ans_list;

    for (const int q : queries) {
      ans_list.emplace_back(ans[q]);
    }

    return ans_list;
  }
};
