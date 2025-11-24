#include <bits/stdc++.h>
using namespace std;

class CountIntervals {
  int cnt = 0;
  map<int, int> m;

 public:
  void add(int left, int right) {
    if (!m.empty()) {
      const auto [a, b] = *prev(m.upper_bound(left));

      if (a <= left && right <= b) return;
      if (a <= left && left <= b) left = b + 1;
    }

    while (!m.empty()) {
      const auto it = m.lower_bound(left);
      if (it == m.end()) break;
      const auto [a, b] = *it;

      if (right < a) break;

      cnt -= b - a + 1;
      right = max(right, b);
      m.erase(it);
    }

    cnt += right - left + 1;
    m[left] = right;
  }

  int count() const { return cnt; }
};
