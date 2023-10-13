#include <bits/stdc++.h>
using namespace std;

double ternary_search_min(double lo, double hi, const function<double(double)>& fn) {
  if (fn(lo) < fn(lo + 0.1)) {
    return min(fn(lo), fn(hi));
  }

  for (int it = 0; it < 50; it++) {
    const double third = (hi - lo) / 3;
    const double t1 = lo + third;
    const double t2 = hi - third;

    if (fn(t1) < fn(t2)) {
      hi = t2;
    } else {
      lo = t1;
    }
  }

  return fn(lo);
}

struct SemiCircle {
  int sign;
  int x, y, radius;

  double eval(const double x0) const {
    return sign * sqrt(pow(radius, 2) - pow(x - x0, 2)) + y;
  }

  double vertical_dist(const SemiCircle sc) const {
    const double lo = max(x - radius, sc.x - sc.radius);
    const double hi = min(x + radius, sc.x + sc.radius);

    return ternary_search_min(
        lo, hi, [&](const double x0) { return fabs(eval(x0) - sc.eval(x0)); });
  }
};

vector<SemiCircle> read(const int y) {
  int n;
  cin >> n;
  char dir1;
  cin >> dir1;
  vector<SemiCircle> result(n);
  bool upper = dir1 == 'N';
  int x_accum = 0;
  for (int i = 0; i < n; i++) {
    result[i].y = y;
    result[i].sign = upper ? 1 : -1;
    cin >> result[i].radius;
    result[i].x = result[i].radius + x_accum;
    x_accum += result[i].radius * 2;
    upper = !upper;
  }
  return result;
}

int main() {
  int A;

  while (cin >> A && A != -1) {
    const auto shore1 = read(A);
    const auto shore2 = read(0);

    double result = DBL_MAX;

    for (int i = 0, j = 0; i < (int)shore1.size(); i++) {
      for (; j < (int)shore2.size(); j++) {
        result = min(result, shore1[i].vertical_dist(shore2[j]));

        if (shore1[i].x + shore1[i].radius < shore2[j].x + shore2[j].radius) {
          break;
        }
      }
    }

    cout << fixed << setprecision(2) << result << endl;
  }
}
