#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Point {
  ll x, y;
  Point operator-(const Point& p) const { return Point{x - p.x, y - p.y}; }
  ll cross(const Point& p) const { return x * p.y - y * p.x; }
  Point to(const Point& p) const { return p - *this; }
};

int N;

ll tetrahedral_number(ll n) { return n * (n + 1) * (n + 2) / 6; }

ll triangular_number(ll n) { return n * (n + 1) / 2; }

ll count(vector<Point>& points) {
  ll ans = tetrahedral_number(N - 2);

  for (int i = 0; i < N; i++) {
    Point vec1 = points[i].to(points[i + 1]);

    int lo = i + 1;
    int hi = N + i;

    while (lo < hi) {
      int mid = (lo + hi) / 2;

      Point vec2 = points[mid].to(points[mid + 1]);

      if (vec1.cross(vec2) >= 0) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }

    ans -= triangular_number(lo - i - 2);
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;
  vector<Point> points(N * 2);

  for (int i = 0; i < N; i++) {
    cin >> points[i].x >> points[i].y;
  }

  for (int i = 0; i < N; i++) {
    points[N + i] = points[i];
  }

  cout << count(points) << endl;
}
