#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e6 + 3;

ll mod(ll n) { return (n + MOD) % MOD; }
ll mult(const ll a, const ll b) { return mod(mod(a) * mod(b)); }
ll subtract(const ll a, const ll b) { return mod(mod(a) - mod(b)); }
ll add(const ll a, const ll b) { return mod(mod(a) + mod(b)); }
ll divide(ll a, const ll b) {
  while (a < 0 || a % b != 0) a += MOD;
  return a / b;
}

struct Point {
  ll x, y;

  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  Point operator+(const Point p) const { return {x + p.x, y + p.y}; }
  Point operator*(const ll f) const { return {x * f, y * f}; }
  ll cross(const Point p) const { return x * p.y - y * p.x; }
  bool is_above() const { return y > 0 || (y == 0 && x > 0); }
  bool operator<(const Point p) const {
    return is_above() != p.is_above() ? is_above() : cross(p) > 0;
  }
  ll mod_cross(const Point p) const { return subtract(mult(x, p.y), mult(y, p.x)); }
};

Point range_sum(const vector<Point>& v, int l, int r) { return v[r + 1] - v[l]; }

ll convex4_concave2;
ll convex4_concave1;
vector<Point> psum1, psum2;

void count_all(const vector<Point>& points) {
  const int n = points.size();

  for (int i = 0, j = 1; i < n; i++) {
    const Point diagonal = points[i];

    if (diagonal.cross(points[(i + 1) % n]) < 0) continue;
    while (j < i || diagonal.cross(points[(j + 1) % n]) > 0) j++;

    const ll count1 = j - i;
    const ll count2 = n - count1 - 1;
    const ll area1 = diagonal.mod_cross(range_sum(psum1, i + 1, j));
    const ll area2 = range_sum(psum1, j + 1, i - 1 + n).mod_cross(diagonal);

    convex4_concave2 = add(convex4_concave2, mult(area1, count2));
    convex4_concave2 = add(convex4_concave2, mult(area2, count1));

    // TODO: Why does this still work even if there are not enough points? (for example if
    //       i + 1 and j - 1 order becomes swapped). This is the only thing I don't
    //       understand.
    const ll area = diagonal.mod_cross(range_sum(psum1, i + 1, j - 1)) * (j + 1) -
                    diagonal.mod_cross(range_sum(psum2, i + 1, j - 1));

    convex4_concave1 = add(convex4_concave1, mult(area, 2));
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N) {
    vector<Point> points(N);
    for (Point& p : points) cin >> p.x >> p.y;

    convex4_concave2 = 0;
    convex4_concave1 = 0;

    for (int i = 0; i < N; i++) {
      vector<Point> centered_points;

      for (int j = 0; j < N; j++) {
        if (i == j) continue;
        centered_points.push_back(points[j] - points[i]);
      }

      sort(centered_points.begin(), centered_points.end());

      if (centered_points.size() < 3) continue;

      psum1 = {{0, 0}};
      psum2 = {{0, 0}};
      for (int i = 0; i < 2 * N; i++) {
        psum1.push_back(psum1.back() + centered_points[i % (N - 1)]);
        psum2.push_back(psum2.back() + centered_points[i % (N - 1)] * (i + 1));
      }

      count_all(centered_points);
    }

    const ll concave = subtract(convex4_concave2, convex4_concave1);
    const ll convex = divide(convex4_concave1 - concave, 4);

    cout << add(concave, convex) << endl;
  }
}
