#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  double maxAmount(const string initialCurrency, const vector<vector<string>>& pairs1,
                   const vector<double>& rates1, const vector<vector<string>>& pairs2,
                   const vector<double>& rates2) {
    queue<tuple<string, double, int>> q;
    q.emplace(initialCurrency, 1, 0);
    set<tuple<string, double, int>> visited;

    double ans = 0;

    while (!q.empty()) {
      if (visited.count(q.front())) {
        q.pop();
        continue;
      }
      visited.emplace(q.front());

      const auto [currency, money, day] = q.front();
      q.pop();

      if (currency == initialCurrency) {
        ans = max(ans, money);
      }

      if (day == 0) {
        for (int i = 0; i < (int)pairs1.size(); i++) {
          const string from = pairs1[i].front();
          const string to = pairs1[i].back();
          if (from == currency) {
            q.emplace(to, rates1[i] * money, 0);
            q.emplace(to, rates1[i] * money, 1);
          }
          if (to == currency) {
            q.emplace(from, money / rates1[i], 0);
            q.emplace(from, money / rates1[i], 1);
          }
        }
        q.emplace(currency, money, 1);
      } else {
        for (int i = 0; i < (int)pairs2.size(); i++) {
          const string from = pairs2[i].front();
          const string to = pairs2[i].back();
          if (from == currency) {
            q.emplace(to, rates2[i] * money, 1);
          }
          if (to == currency) {
            q.emplace(from, money / rates2[i], 1);
          }
        }
      }
    }

    return ans;
  }
};
