#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;

  inline Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  inline ll cross(const Point& p) const { return x * p.y - y * p.x; }
};

struct Segment {
  Point p, q;
  bool from_floor;

  bool operator<(const Segment& s) const { return p.x < s.p.x; }
};

int N, H;
vector<Segment> segments;

ll cross(const Point& origin, const Point& p, const Point& q) {
  return (p - origin).cross(q - origin);
}

int count_right(const int center_idx) {
  const Point center = segments[center_idx].q;

  Point ceil_limit = {center.x, H};
  Point floor_limit = {center.x, 0};

  int ans = 0;

  for (int i = center_idx + 1; i < N; i++) {
    const Point endpoint = segments[i].q;

    ans += cross(center, floor_limit, endpoint) > 0 &&
           cross(center, ceil_limit, endpoint) < 0;

    if (segments[i].from_floor) {
      if (cross(center, floor_limit, endpoint) > 0) floor_limit = endpoint;
    } else {
      if (cross(center, ceil_limit, endpoint) < 0) ceil_limit = endpoint;
    }
  }

  return ans;
}

void solve() {
  cin >> H >> N;

  segments.assign(N, {});

  unordered_map<ll, int> x_values;

  for (int i = 0; i < N; i++) {
    int t;
    ll x, a;
    cin >> t >> x >> a;

    x_values[x]++;

    if (t == 0) {
      segments[i] = {{x, 0}, {x, a}, true};
    } else {
      segments[i] = {{x, H}, {x, a}, false};
    }
  }

  sort(segments.begin(), segments.end());

  vector<int> ans(N, 0);

  for (int i = 0; i < N; i++) {
    ans[i] += count_right(i);
    ans[i] += x_values[segments[i].p.x] - 1;
  }

  reverse(segments.begin(), segments.end());

  for (Segment& s : segments) {
    s.p.x *= -1;
    s.q.x *= -1;
  }

  for (int i = 0; i < N; i++) {
    ans[N - 1 - i] += count_right(i);
  }

  for (int i = 0; i < N; i++) {
    cout << ans[i] << " ";
  }

  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  while (T--) solve();
}
