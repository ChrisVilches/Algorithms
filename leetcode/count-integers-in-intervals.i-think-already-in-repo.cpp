#include <bits/stdc++.h>
using namespace std;

class CountIntervals {
  int cnt = 0;
  map<int, int> m;

  map<int, int>::iterator find_prev(const int left) {
    if (m.empty()) return m.end();

    auto it = m.lower_bound(left);

    if (it == m.end()) --it;

    if (left < it->first) {
      if (it != m.begin()) --it;
    }

    return it;
  }

 public:
  void add(int left, int right) {
    const auto prev_it = find_prev(left);
    if (prev_it != m.end()) {
      if (prev_it->first <= left) {
        if (right <= prev_it->second) return;
        if (left <= prev_it->second) {
          left = prev_it->second + 1;
        }
      }
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
