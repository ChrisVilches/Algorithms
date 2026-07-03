#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
  ll x, y;
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  bool first_half() const { return y > 0 || (y == 0 && x > 0); }
  bool operator<(const Point p) const {
    return first_half() != p.first_half() ? first_half() : cross(p) > 0;
  }
};

int main() {
  int n;

  while (cin >> n) {
    vector<tuple<Point, int, int>> events;

    for (int i = 0; i < n; i++) {
      Point p, q;
      cin >> p.x >> p.y >> q.x >> q.y;

      if (p.cross(q) < 0) swap(p, q);

      events.emplace_back(p, 0, i);
      events.emplace_back(q, 1, i);
    }

    sort(events.begin(), events.end());

    int best_ans = INT_MAX;

    for (size_t ev_idx = 0; ev_idx < events.size(); ev_idx++) {
      if (get<1>(events[ev_idx]) != 0) continue;

      vector<bool> done(n, false);
      unordered_set<int> curr;

      for (int iter = events.size(), i = ev_idx; iter--; i = (i + 1) % events.size()) {
        const auto [_, type, idx] = events[i];
        if (type == 0) {
          curr.emplace(idx);
        } else {
          curr.erase(idx);
        }
      }

      int ans = 0;

      for (int iter = events.size(), i = ev_idx; iter--; i = (i + 1) % events.size()) {
        const auto [_, type, idx] = events[i];
        if (done[idx]) continue;

        if (type == 0) {
          curr.emplace(idx);
        } else if (type == 1) {
          ans++;

          while (!curr.empty()) {
            done[*curr.begin()] = true;
            curr.erase(curr.begin());
          }
        }
      }

      best_ans = min(best_ans, ans);
    }

    cout << best_ans << endl;
  }
}
