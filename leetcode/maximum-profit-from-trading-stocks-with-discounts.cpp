#include <bits/stdc++.h>
using namespace std;

class Solution {
  int memo[167][167][2];
  int budget;
  vector<int> future, present;
  vector<vector<int>> graph;

  vector<int> table[167][2];

  void merge_children(const int u, const bool discount) {
    vector<int>& curr = table[u][discount];
    curr.assign(budget + 1, 0);
    vector<int> next(budget + 1, 0);

    for (const int v : graph[u]) {
      for (int b = 0; b <= budget; b++) {
        next[b] = curr[b];

        for (int i = 0; i <= b; i++) {
          next[b] = max(next[b], dp(v, i, discount) + curr[b - i]);
        }
      }

      curr.swap(next);
    }
  }

  int dp(const int u, const int budg, const bool discount) {
    int& m = memo[u][budg][discount];
    if (~m) return m;

    const int price = discount ? present[u] / 2 : present[u];

    if (table[u][false].empty()) merge_children(u, false);
    if (table[u][true].empty()) merge_children(u, true);

    const int buy = budg >= price ? future[u] - price + table[u][true][budg - price] : 0;
    const int not_buy = table[u][false][budg];

    return m = max(buy, not_buy);
  }

 public:
  int maxProfit(const int n, const vector<int>& input_present,
                const vector<int>& input_future, const vector<vector<int>>& hierarchy,
                const int input_budget) {
    memset(memo, -1, sizeof memo);
    graph.resize(n);
    this->present = input_present;
    this->future = input_future;
    this->budget = input_budget;

    for (const vector<int>& hier : hierarchy) {
      const int u = hier.front() - 1;
      const int v = hier.back() - 1;
      graph[u].emplace_back(v);
    }

    return dp(0, budget, false);
  }
};
