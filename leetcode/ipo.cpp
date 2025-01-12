#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int findMaximizedCapital(const int k, const int w, const vector<int>& profits,
                           const vector<int>& capital) {
    vector<pair<int, int>> projects;

    for (size_t i = 0; i < profits.size(); i++) {
      projects.emplace_back(capital[i], profits[i]);
    }

    sort(projects.begin(), projects.end());

    priority_queue<int> pq;

    int rem_k = k;
    int total_capital = w;

    auto it = projects.begin();

    while (rem_k > 0) {
      while (it < projects.end() && it->first <= total_capital) {
        pq.emplace(it->second);
        it++;
      }

      if (pq.empty()) break;

      total_capital += pq.top();
      rem_k--;
      pq.pop();
    }

    return total_capital;
  }
};
