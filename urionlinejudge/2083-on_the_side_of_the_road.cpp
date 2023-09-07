#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  bool operator<(const Point p) const {
    if (x == p.x) return y < p.y;
    return x < p.x;
  }
};

int main() {
  int N;
  while (cin >> N) {
    vector<Point> points(N);
    for (auto& p : points) cin >> p.x >> p.y;

    vector<tuple<double, ll, Point, Point>> intersections;

    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        const Point p = points[i];
        const Point q = points[j];

        if (p.y == q.y) continue;

        if (p.x == q.x) {
          intersections.emplace_back(p.x, LONG_LONG_MAX, p, q);
          continue;
        }

        const double slope = (p.y - q.y) / (double)(p.x - q.x);
        const double b = p.y - slope * p.x;
        const ll slope_int = round(slope * 1000000);
        intersections.emplace_back(-b / slope, slope_int, p, q);
      }
    }

    vector<int> counts{N};
    set<Point> blocked;
    set<ll> slopes;

    double prev = -numeric_limits<double>::infinity();
    sort(intersections.begin(), intersections.end());

    for (const auto [x, slope, p, q] : intersections) {
      if (fabs(x - prev) > 1e-8) {
        counts.push_back(0);
        blocked.clear();
        slopes.clear();
        prev = x;
      }

      blocked.emplace(p);
      blocked.emplace(q);
      slopes.emplace(slope);
      counts.back() = N - blocked.size() + slopes.size();
      prev = x;
    }

    cout << set<int>{counts.begin(), counts.end()}.size() << endl;
  }
}
