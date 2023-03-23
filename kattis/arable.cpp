#include <bits/stdc++.h>
using namespace std;

struct Point {
  int x, y;
};

double fix_integer(const double x) { return fabs(round(x) - x) < 1e-6 ? round(x) : x; }

int sweep_line(vector<pair<double, double>> events) {
  sort(events.begin(), events.end());

  int res = 0;

  for (int i = 0; i < (int)events.size(); i += 2) {
    const auto [l1, l2] = events[i];
    const auto [r1, r2] = events[i + 1];

    const int enter = ceil(max(l1, l2));
    const int exit = floor(min(r1, r2));

    res += max(0, exit - enter);
  }

  return res;
}

int count(const vector<Point>& polygon) {
  int res = 0;

  unordered_map<int, vector<pair<double, double>>> y_events;

  for (int i = 0; i < (int)polygon.size(); i++) {
    const Point p = polygon[i];
    const Point q = polygon[(i + 1) % polygon.size()];
    if (p.y == q.y) continue;

    const auto [min_y, max_y] = minmax(p.y, q.y);
    const double slope = (p.x - q.x) / (double)(p.y - q.y);

    for (int y = min_y; y < max_y; y++) {
      y_events[y].emplace_back(fix_integer(p.x + slope * (y - p.y)),
                               fix_integer(p.x + slope * (y + 1 - p.y)));
    }
  }

  for (int y = -100; y <= 100; y++) {
    res += sweep_line(y_events[y]);
  }

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N && N != 0) {
    vector<Point> polygon(N);
    for (Point& p : polygon) cin >> p.x >> p.y;
    cout << count(polygon) << '\n';
  }
}
