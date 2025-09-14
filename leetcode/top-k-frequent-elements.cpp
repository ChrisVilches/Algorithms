#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> topKFrequent(const vector<int>& nums, const int k) {
    unordered_map<int, int> freq;

    for (const auto& x : nums) {
      freq[x]++;
    }

    priority_queue<pair<int, int>> pq;

    for (const auto& [x, f] : freq) {
      pq.emplace(-f, x);

      if (pq.size() > static_cast<size_t>(k)) {
        pq.pop();
      }
    }

    vector<int> res;

    while (!pq.empty()) {
      res.emplace_back(pq.top().second);
      pq.pop();
    }

    return res;
  }
};
