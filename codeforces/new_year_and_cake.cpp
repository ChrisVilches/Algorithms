#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

ll mod(ll n) {
  if (n < 0) n += MOD;
  return n % MOD;
}

ll mult(const ll a, const ll b) { return mod(mod(a) * mod(b)); }
ll subtract(const ll a, const ll b) { return mod(mod(a) - mod(b)); }
void add(ll& a, const ll b) { a = mod(mod(a) + mod(b)); }

struct Point {
  ll x, y;

  inline Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
  inline Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
  inline ll cross(const Point& p) const { return x * p.y - y * p.x; }

  ll mod_cross(const Point& p) const { return subtract(mult(x, p.y), mult(y, p.x)); }

  Point to(const Point& p) const { return p - *this; }

} points[500'001];

int N;

ll psum1[1'000'070], psum2[1'000'070];

ll range_sum(const int l, const int r, ll psum[]) {
  return subtract(psum[r + 1], psum[l]);
}

ll area2(const int i, const int j, const int k) {
  const Point& a = points[i % N];
  const Point& b = points[j % N];
  const Point& c = points[k % N];
  return abs(a.to(b).cross(a.to(c)));
}

ll compute_total_area() {
  ll result = 0;
  for (int i = 0; i < N; i++) result += points[i].cross(points[(i + 1) % N]);
  return result;
}

void compute_prefix_sum() {
  psum1[0] = 0;
  for (int i = 1; i <= 2 * N; i++) {
    psum1[i] = psum1[i - 1];
    psum1[i] += points[(i - 1) % N].mod_cross(points[i % N]);
  }

  psum2[0] = 0;
  for (int i = 1; i <= 2 * N; i++) {
    psum2[i] = psum2[i - 1];
    psum2[i] += mult(i, points[(i - 1) % N].mod_cross(points[i % N]));
  }
}

void solve() {
  for (int i = 0; i < N; i++) {
    cin >> points[i].x >> points[i].y;
  }

  reverse(points, points + N);

  const ll area_total = compute_total_area();
  const ll area_total_half = (area_total / 2) + (area_total % 2 == 1);

  compute_prefix_sum();

  ll ans = 0;
  ll curr_area = 0;
  ll smaller = 0;

  Point sum{0, 0};

  for (int i = 0, j = 0; i < N; i++) {
    sum = sum - points[i];

    for (;; j++) {
      const ll next_piece = curr_area + area2(i, j, j + 1);

      if (next_piece >= area_total_half) {
        add(ans, mult(area_total, j - i - 1));
        add(smaller, mult(j + 1, range_sum(i, j, psum1)) - range_sum(i, j, psum2));
        add(smaller, (sum + points[j % N]).mod_cross(points[i]));
        break;
      }

      sum = sum + points[j % N];
      curr_area += area2(i, j, j + 1);
    }

    curr_area -= area2(i, i + 1, j);
  }

  ans = subtract(ans, 2 * smaller);

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N) solve();
}
