#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  ll cross(const Point p) const { return x * p.y - y * p.x; }
} points[100'007];

int N;
ll total, psum[2 * 100'007];

ll range_sum(int l, int r) { return psum[r + 1] - psum[l]; }

pair<ll, ll> f(const ll i, const ll v) {
  const ll piece1 = range_sum(i, i + v - 1) + points[(i + v) % N].cross(points[i]);
  const ll piece2 = total - piece1;

  const ll diff = abs(piece1 - piece2);
  const ll biggest_piece = max(piece1, piece2);

  return {diff, biggest_piece};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N) {
    for (int i = 0; i < N; i++) cin >> points[i].x >> points[i].y;

    psum[0] = 0;
    for (int i = 0; i < 2 * N; i++) {
      psum[i + 1] = psum[i] + points[i % N].cross(points[(i + 1) % N]);
    }

    total = range_sum(0, N - 1);

    ll biggest = 0;

    for (int i = 0; i < N; i++) {
      ll lo = 0;
      ll hi = N - 1;

      while (lo < hi) {
        const ll third = (hi - lo) / 3;
        const ll v1 = lo + third;
        const ll v2 = hi - third;

        if (f(i, v1) > f(i, v2)) {
          lo = v1 + 1;
        } else {
          hi = v2 - 1;
        }
      }

      biggest = max(biggest, f(i, lo).second);
    }

    cout << biggest << " " << total - biggest << endl;
  }
}
