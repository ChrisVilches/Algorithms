#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
  ll x, y;
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  ll cross(const Point p) const { return x * p.y - y * p.x; }
};

struct Segment {
  Point p, q;

  bool operator<(const Segment s) const {
    if (p.x < s.p.x)
      return (q - p).cross(s.p - p) > 0;
    else
      return (s.q - s.p).cross(p - s.p) < 0;
  }
};

int main() {
  // All official test cases, plus custom test cases that break the event
  // ordering if it is not implemented correctly.
  assert(freopen("usaco/hillwalk.in", "r", stdin) != NULL);

  int n;
  while (cin >> n) {
    vector<Segment> segments(n);
    for (Segment& s : segments) {
      cin >> s.p.x >> s.p.y >> s.q.x >> s.q.y;
    }

    vector<tuple<int, int, int, int>> events;

    for (int i = 0; i < n; i++) {
      const Segment s = segments[i];
      events.emplace_back(s.p.x, 0, -s.p.y, i);
      events.emplace_back(s.q.x, 1, s.q.y, i);
    }

    sort(events.begin(), events.end());

    set<pair<Segment, int>> s;

    vector<int> next_idx(n, -1);

    for (const auto& [_, type, __, idx] : events) {
      if (type == 0) {
        const Segment lower = segments[idx];
        const auto it = s.lower_bound({lower, -1});

        if (it != s.end()) {
          const Segment upper = it->first;
          if (upper.q.x < lower.q.x) next_idx[it->second] = idx;
        }

        s.emplace(lower, idx);
      } else {
        const auto it = s.find({segments[idx], idx});

        if (it != s.begin()) {
          const Segment upper = it->first;
          const Segment lower = prev(it)->first;
          if (upper.q.x < lower.q.x) next_idx[idx] = prev(it)->second;
        }

        s.erase(it);
      }
    }

    int ans = 0;
    int idx = 0;

    while (idx != -1) {
      ans++;
      idx = next_idx[idx];
    }

    cout << ans << endl;
  }
}
