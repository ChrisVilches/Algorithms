#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y, v;

  inline Point operator-(const Point& p) const { return {x - p.x, y - p.y, v}; }
  inline ll cross(const Point& p) const { return x * p.y - y * p.x; }
} polygon[201];

int N;
ll memo[201][201];

int mod(const int i) { return (i + N) % N; }
Point vertex_at(const int i) { return polygon[mod(i)]; }

ll area2(const int i, const int j, const int k) {
  const Point& o = vertex_at(i);
  const Point& a = vertex_at(j);
  const Point& b = vertex_at(k);
  return abs((a - o).cross(b - o));
}

ll compute_total_area() {
  ll result = 0;
  for (int i = 0; i < N; i++) result += vertex_at(i).cross(vertex_at(i + 1));
  return result;
}

ll dp(const int curr_idx, const int init_idx) {
  if (curr_idx - init_idx == N) return 0;
  if (curr_idx - init_idx > N) return INT_MIN;

  ll& res = memo[mod(curr_idx)][init_idx];

  if (~res) return res;

  res = max(0LL, dp(curr_idx + 1, init_idx));

  ll area2_removed = 0;
  ll vertices_value = 0;

  for (int i = curr_idx + 2, it = N; it--; i++) {
    area2_removed += area2(curr_idx, i - 1, i);
    vertices_value += vertex_at(i - 1).v;

    const ll next_state = dp(i, init_idx);
    if (next_state == INT_MIN) break;

    res = max(res, vertices_value - area2_removed + next_state);
  }

  return res;
}

int main() {
  while (cin >> N) {
    memset(memo, -1, sizeof memo);

    ll ans = 0;

    for (int i = 0; i < N; i++) {
      cin >> polygon[i].x >> polygon[i].y >> polygon[i].v;
      ans += polygon[i].v;
    }

    const ll total_area2 = compute_total_area();

    for (int i = 0; i < N; i++) {
      ans = max(ans, total_area2 + dp(i, i));
    }

    cout << ans << endl;
  }
}
