#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

struct PiecewiseFunction {
  PiecewiseFunction(const vector<pii>& points) {
    for (int i = 0; i < (int)points.size() - 1; i++) {
      const double x = points[i].first;
      const double dy = points[i].second - points[i + 1].second;
      const double dx = points[i].first - points[i + 1].first;
      const double slope = dy / dx;
      fn.emplace(x, points[i].second, slope);
    }
  }

  double operator()(const double x) const {
    auto it = fn.lower_bound({x, INT_MAX, INT_MAX});
    if (it != fn.begin()) it--;
    const auto [x0, y, slope] = *it;
    const double dx = x - x0;
    return y + dx * slope;
  };

 private:
  set<tuple<int, double, double>> fn;
};

pair<PiecewiseFunction, PiecewiseFunction> read_functions(const int A, const int D) {
  vector<pair<int, int>> fn1, fn2;

  int h, t;
  double curr_height = 0;

  fn1.emplace_back(0, 0);

  for (int i = 0, accum_time = 0; i < A; i++) {
    cin >> h >> t;
    accum_time += t;
    curr_height += h;
    fn1.emplace_back(accum_time, curr_height);
  }

  fn1.emplace_back(INT_MIN, -curr_height);
  fn2.emplace_back(0, curr_height);

  for (int i = 0, accum_time = 0; i < D; i++) {
    cin >> h >> t;
    accum_time += t;
    curr_height -= h;
    fn2.emplace_back(accum_time, curr_height);
  }

  fn2.emplace_back(INT_MAX, 0);

  return {fn1, fn2};
}

int main() {
  int A, D;

  while (cin >> A >> D) {
    const auto [fn1, fn2] = read_functions(A, D);
    double lo = 0;
    double hi = 5000 * 100;

    for (int it = 0; it < 100; it++) {
      const double mid = (lo + hi) / 2;

      if (fn2(mid) > fn1(mid)) {
        lo = mid;
      } else {
        hi = mid;
      }
    }

    cout << fixed << setprecision(9) << lo << endl;
  }
}
