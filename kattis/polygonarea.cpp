#include <bits/stdc++.h>

using namespace std;

double polygon_area(vector<pair<double, double> > pts) {
  double area = 0, diff = 0;
  unsigned int last = pts.size() - 1;
  for (unsigned int i = 1; i < last; i++) {
    diff = pts[i + 1].second - pts[i - 1].second;
    area += pts[i].first * diff;
  }

  diff = pts[1].second - pts[last].second;
  area += pts[0].first * diff;

  diff = pts[0].second - pts[last - 1].second;
  area += pts[last].first * diff;

  return 0.5 * area;
}

int main() {
  int n;
  while (scanf("%d", &n) == 1 && n > 0) {
    vector<pair<double, double> > v;

    while (n--) {
      double x, y;
      cin >> x >> y;
      v.push_back(make_pair(x, y));
    }

    double area = polygon_area(v);
    printf("%s %.1lf\n", area < 0 ? "CW" : "CCW", fabs(area));
  }
}
