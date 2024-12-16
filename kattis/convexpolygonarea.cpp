#include <bits/stdc++.h>
using namespace std;

struct Point {
  double x, y;
  double cross(const Point p) const { return x * p.y - y * p.x; }
};

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<Point> polygon(n);
    for (auto& p : polygon) cin >> p.x >> p.y;
    double total = 0;
    for (int i = n - 1, j = 0; j < n; i = j++) {
      const Point p = polygon[i];
      const Point q = polygon[j];
      total += p.cross(q) / 2;
    }
    cout << total << endl;
  }
}
