#include <bits/stdc++.h>
using namespace std;

class StockSpanner {
  stack<pair<int, int>> s;
  int idx = 0;

 public:
  StockSpanner() { s.emplace(INT_MAX, -1); }

  int next(const int price) {
    while (s.top().first <= price) s.pop();

    const int res = idx - s.top().second;

    s.emplace(price, idx++);

    return res;
  }
};
