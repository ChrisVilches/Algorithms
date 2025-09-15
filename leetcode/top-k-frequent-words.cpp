#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<string> topKFrequent(const vector<string>& words, const int k) {
    unordered_map<string, int> freq;

    for (const auto& w : words) {
      freq[w]++;
    }

    priority_queue<pair<int, string>> pq;

    for (const auto& [w, f] : freq) {
      pq.emplace(-f, w);

      if (pq.size() > static_cast<size_t>(k)) {
        pq.pop();
      }
    }

    vector<string> res;

    while (!pq.empty()) {
      res.emplace_back(pq.top().second);
      pq.pop();
    }

    reverse(res.begin(), res.end());

    return res;
  }
};
