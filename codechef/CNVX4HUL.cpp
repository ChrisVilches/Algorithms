#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

short sgn(const ll n) {
  if (n < 0) return -1;
  return n > 0;
}

struct Point {
  ll x, y;
  int idx;

  inline Point operator-(const Point& p) const { return {x - p.x, y - p.y, idx}; }
  inline ll cross(const Point& p) const { return x * p.y - y * p.x; }
  inline bool is_above() const { return y > 0 || (y == 0 && x > 0); }
  inline bool operator<(const Point& p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }

  Point to(const Point& p) const { return p - *this; }

  bool inside_triangle(const Point A, const Point B, const Point C) const {
    const short o1 = sgn(A.to(B).cross(A.to(*this)));
    const short o2 = sgn(B.to(C).cross(B.to(*this)));
    const short o3 = sgn(C.to(A).cross(C.to(*this)));
    return o1 == o2 && o2 == o3;
  }
} points[307];

int N;
const ll MOD = 1e9 + 7;
int points_in_triangle[302][302];
ll two_power[307];
ll total, total_concave;

ll points_inside_aux(const int i, const int j, const int k) {
  return points_in_triangle[j][k] - points_in_triangle[i][j] - points_in_triangle[i][k] -
         1;
}

ll points_inside(const int i, const int j, const int k) {
  if (i == 0) return points_in_triangle[j][k];
  if (j == 0) return points_in_triangle[i][k];
  if (k == 0) return points_in_triangle[i][j];

  const Point& A = points[i];
  const Point& B = points[j];
  const Point& C = points[k];
  const Point& O = points[0];

  if (O.inside_triangle(A, B, C)) {
    return points_in_triangle[i][j] + points_in_triangle[i][k] +
           points_in_triangle[j][k] + 1;
  }

  if (A.inside_triangle(O, B, C)) return points_inside_aux(i, j, k);
  if (B.inside_triangle(O, A, C)) return points_inside_aux(j, i, k);
  if (C.inside_triangle(O, A, B)) return points_inside_aux(k, i, j);

  array<Point, 3> vec{A - O, B - O, C - O};
  sort(vec.begin(), vec.end(),
       [](const Point& v1, const Point& v2) { return v1.cross(v2) > 0; });

  const int a = vec[0].idx;
  const int b = vec[1].idx;
  const int c = vec[2].idx;

  return points_in_triangle[a][b] + points_in_triangle[b][c] - points_in_triangle[a][c];
}

void precompute_points_inside_triangles() {
  for (int i = 1; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      for (int p = 1; p < N; p++) {
        if (p == i || p == j) continue;

        if (points[p].inside_triangle(points[0], points[i], points[j]))
          points_in_triangle[i][j]++;
      }

      points_in_triangle[j][i] = points_in_triangle[i][j];
    }
  }
}

void count_all(const vector<Point>& points, const int center_idx) {
  const int n = points.size();

  for (int i = 0; i < n; i++) {
    const Point diagonal = points[i];

    ll all = 0;

    for (const Point& p : points) {
      if (diagonal.cross(p) < 0) {
        const ll inside = points_inside(center_idx, diagonal.idx, p.idx);

        all = (all + two_power[inside]) % MOD;
      }
    }

    if (all == 0) continue;

    const int first_i = (i + 1) % n;
    if (diagonal.cross(points[first_i]) < 0) continue;

    Point p1, p2;

    int k = first_i;

    for (;; k = (k + 1) % n) {
      p2 = points[k];
      if (diagonal.cross(p2) < 0) break;
    }

    ll concave = 0;

    for (int j = first_i;; j++) {
      p1 = points[j % n];
      if (diagonal.cross(p1) < 0) break;

      while (diagonal.cross(p2) < 0) {
        if (p1.cross(p2) < 0) break;

        const ll inside = points_inside(center_idx, diagonal.idx, p2.idx);

        concave = (concave + two_power[inside]) % MOD;

        k = (k + 1) % n;
        p2 = points[k];
      }

      const ll inside_p1 = points_inside(center_idx, diagonal.idx, p1.idx);

      total = (total + all * two_power[inside_p1]) % MOD;
      total_concave = (total_concave + concave * two_power[inside_p1]) % MOD;
    }
  }
}

ll gcd_extended(ll a, ll b, ll& x, ll& y) {
  if (a == 0) {
    x = 0, y = 1;
    return b;
  }

  ll x1, y1;
  ll gcd = gcd_extended(b % a, a, x1, y1);

  x = y1 - (b / a) * x1;
  y = x1;

  return gcd;
}

ll mod_inverse(ll b, ll m) {
  ll x, y;
  ll g = gcd_extended(b, m, x, y);
  if (g != 1) return -1;
  return (x % m + m) % m;
}

ll mod_divide(ll a, ll b, ll m) {
  a = a % m;
  ll inv = mod_inverse(b, m);
  assert(~inv);
  return (inv * a) % m;
}

void solve() {
  for (int i = 0; i < N; i++) {
    cin >> points[i].x >> points[i].y;
    points[i].idx = i;
  }

  memset(points_in_triangle, 0, sizeof points_in_triangle);

  precompute_points_inside_triangles();

  total = 0;
  total_concave = 0;

  for (int i = 0; i < N; i++) {
    vector<Point> centered_points;

    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      centered_points.push_back(points[j] - points[i]);
    }

    sort(centered_points.begin(), centered_points.end());

    count_all(centered_points, i);
  }

  total += (-2 * total_concave) + MOD;
  total = mod_divide(total, 4, MOD) + MOD;
  total %= MOD;

  cout << total << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  two_power[0] = 1;

  for (int i = 1; i <= 305; i++) {
    two_power[i] = two_power[i - 1] * 2;
    two_power[i] %= MOD;
  }

  while (cin >> N) solve();
}
