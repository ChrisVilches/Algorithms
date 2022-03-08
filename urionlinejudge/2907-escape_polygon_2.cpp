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

ll triangular_number(ll n) { return n * (n + 1) / 2; }

ll count() {
  ll ans = 0;

  for (int i = 0, j = 1; i < N; i++) {
    Point vec1 = points[i].to(points[(i + 1) % N]);

    ans += triangular_number(i - 1);

    for (;; j++) {
      Point vec2 = points[j % N].to(points[(j + 1) % N]);
      if (vec1.cross(vec2) < 0) break;
    }

    ans -= triangular_number(j - i - 2);
  }

  return ans;
}

int main() {
  scanf("%d", &N);

  for (int i = 0; i < N; i++) {
    scanf("%lld %lld", &points[i].x, &points[i].y);
  }

  cout << count() << endl;
}
