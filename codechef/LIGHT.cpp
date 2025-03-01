#include <bits/stdc++.h>
using namespace std;

struct Triangle {
  const double x, y, tan_ang;

  Triangle(const double x, const double y, const double ang)
      : x(x), y(y), tan_ang(tan(M_PI * ang / 180)) {}

  double dx(const double y0) const { return tan_ang * (y - y0); }
  double eval_left(const double y0) const { return x - dx(y0); }
  double eval_right(const double y0) const { return x + dx(y0); }
};

vector<Triangle> triangles;

bool sweep(const double L, const double R, const double y) {
  vector<pair<double, int>> events;

  for (const Triangle& t : triangles) {
    if (y > t.y) continue;

    events.emplace_back(t.eval_left(y), 1);
    events.emplace_back(t.eval_right(y), -1);
  }
  events.emplace_back(L, 0);
  events.emplace_back(R, 0);

  sort(events.begin(), events.end());

  int curr = 0;
  bool inside = false;

  for (const auto& [x, delta] : events) {
    if (x == L && delta == 0) {
      inside = true;
      continue;
    }

    if (x == R && delta == 0) break;

    if (inside && curr == 0) {
      return false;
    }

    curr += delta;
  }

  return curr > 0;
}

int main() {
  int n;
  double L, R;
  cin >> n >> L >> R;

  for (int i = 0; i < n; i++) {
    double x, y, ang;
    cin >> x >> y >> ang;
    triangles.emplace_back(x, y, ang);
  }

  double lo = 0;
  double hi = 1000;

  for (int iter = 0; iter < 200; iter++) {
    const double mid = (lo + hi) / 2;

    if (sweep(L, R, mid)) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  cout << fixed << setprecision(9) << lo << endl;
}
