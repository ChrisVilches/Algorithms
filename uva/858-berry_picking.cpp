#include <bits/stdc++.h>
using namespace std;
using pii = pair<double, double>;
#define x first
#define y second

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N;
    double threshold, x0;
    cin >> N;

    vector<pii> points(N);
    for (auto& p : points) cin >> p.x >> p.y;

    cin >> threshold >> x0;

    vector<double> ys;

    for (int i = 0; i < N; i++) {
      pii p = points[i];
      pii q = points[(i + 1) % N];
      if (p.x == q.x) continue;
      if (p.x > q.x) swap(p, q);
      if (x0 < p.x) continue;
      if (q.x < x0) continue;

      const double slope = (p.y - q.y) / (p.x - q.x);
      const double dx = x0 - p.x;
      ys.emplace_back(p.y + slope * dx);
    }

    sort(ys.begin(), ys.end());

    double total = 0;

    for (int i = 0; i < (int)ys.size() - 1; i += 2) {
      const double y0 = ys[i];
      const double y1 = ys[i + 1];

      total += fabs(y1 - y0);
    }

    cout << (total > threshold ? "YES" : "NO") << endl;
  }
}
