#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  inline Point operator-(const Point& p) const { return Point{x - p.x, y - p.y}; }
  inline ll operator^(const Point& p) const { return (x * p.y) - (y * p.x); }
  inline Point to(const Point& p) const { return p - *this; }
};

bool point_inside_polygon(const Point& p, const vector<Point>& polygon) {
  for (int i = 0; i < (int)polygon.size(); i++)
    if ((polygon[i].to(polygon[(i + 1) % (int)polygon.size()]) ^ polygon[i].to(p)) <= 0)
      return false;

  return true;
}

ll C2(const ll n) { return n * (n - 1) / 2; }
ll C3(const ll n) { return n * (n - 1) * (n - 2) / 6; }

ll count(const Point& p, const vector<Point>& polygon) {
  if (!point_inside_polygon(p, polygon)) return 0;

  ll total = C3(polygon.size());

  for (int i = 0, j = 2; i < (int)polygon.size(); i++) {
    const Point v1 = polygon[i];

    for (;; j++) {
      const Point v2 = polygon[j % (int)polygon.size()];
      if ((v1.to(v2) ^ v2.to(p)) < 0) break;
    }

    total -= C2(j - i - 1);
  }

  return total;
}

void solve(const int N) {
  vector<Point> polygon(N);

  for (int i = 0; i < N; i++) {
    cin >> polygon[i].x >> polygon[i].y;
  }

  reverse(polygon.begin(), polygon.end());

  int T;
  cin >> T;

  while (T--) {
    Point query;
    cin >> query.x >> query.y;

    cout << count(query, polygon) << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N;

  while (cin >> N) solve(N);
}
