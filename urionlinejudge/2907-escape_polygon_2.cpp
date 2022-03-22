#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  inline Point operator-(const Point& p) const { return Point{x - p.x, y - p.y}; }
  inline ll cross(const Point& p) const { return x * p.y - y * p.x; }
  inline Point to(const Point& p) const { return p - *this; }
} points[100001];

int N;

ll C2(const ll n) { return n * (n - 1) / 2; }
ll C3(const ll n) { return n * (n - 1) * (n - 2) / 6; }

ll count() {
  ll ans = C3(N);

  for (int i = 0, j = 1; i < N; i++) {
    Point vec1 = points[i].to(points[(i + 1) % N]);

    for (;; j++) {
      Point vec2 = points[j % N].to(points[(j + 1) % N]);
      if (vec1.cross(vec2) < 0) break;
    }

    ans -= C2(j - i - 1);
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N) {
    for (int i = 0; i < N; i++) {
      cin >> points[i].x >> points[i].y;
    }

    cout << count() << endl;
  }
}
