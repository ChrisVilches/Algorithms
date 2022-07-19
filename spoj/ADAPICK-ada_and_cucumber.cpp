#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  ll cross(const Point& p) const { return x * p.y - y * p.x; }
  ll operator*(const Point& p) const { return x * p.x + y * p.y; }
  bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
};

struct Segment {
  Point p, q;
  bool intersects_positive_x_axis() const {
    if (p.cross(q) > 0) return q < p;
    return p < q;
  }
};

void solve() {
  int N;
  cin >> N;

  vector<pair<Point, int>> events;

  unordered_set<int> active;

  int ans = 0;
  int curr = 0;
  int subtract = 0;

  for (int i = 0; i < N; i++) {
    Segment s;
    cin >> s.p.x >> s.p.y;
    cin >> s.q.x >> s.q.y;

    events.push_back({s.p, i});
    events.push_back({s.q, i});

    if (s.intersects_positive_x_axis()) {
      active.emplace(i);
      curr++;
    }
  }

  sort(events.begin(), events.end());

  for (int i = 0; i < (int)events.size(); i++) {
    const auto [point, idx] = events[i];
    const Point next_point = events[(i + 1) % events.size()].first;

    if (active.count(idx)) {
      subtract++;
      active.erase(idx);
    } else {
      curr++;
      active.emplace(idx);
    }

    ans = max(ans, curr);

    if (point.cross(next_point) == 0 && point * next_point > 0) continue;

    curr -= subtract;
    subtract = 0;
  }

  cout << ans << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
