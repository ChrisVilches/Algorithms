#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

struct Point {
  ll x, y;
  Point(ll x, ll y) : x(x), y(y) {}
  Point() {}

  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
  inline ll operator^(const Point& p) const { return x * p.y - y * p.x; }
  inline bool operator==(const Point& p) const { return x == p.x && y == p.y; }
  bool operator<(const Point& p) const {
    return quad() != p.quad() ? quad() > p.quad() : (*this ^ p) > 0;
  }
  Point to(const Point& p) const { return p - *this; }
  inline int quad() const { return y != 0 ? (y > 0) : x > 0; }
};

int N;

Point house, gate;
vector<Point> points;

ll memo[400][400];

ll build(int p, int prev_idx) {
  if (memo[p][prev_idx] != -1) return memo[p][prev_idx];

  Point prev = points[prev_idx];
  Point curr = points[p];

  bool enclose_house = (prev.to(curr) ^ curr.to(house)) > 0;
  if (!enclose_house) return 0;

  ll ret = 0;

  bool convex_to_house = (curr.to(gate) ^ gate.to(house)) > 0;
  bool convex_to_gate = (prev.to(curr) ^ curr.to(gate)) > 0;
  bool can_close_wall = convex_to_gate && convex_to_house;
  if (can_close_wall) ret++;

  for (int i = p + 1;; i++) {
    i %= points.size();

    Point next = points[i];
    if (next == gate) break;
    if ((prev.to(curr) ^ curr.to(next)) <= 0) continue;

    ret = (ret + build(i, p)) % MOD;
  }

  return memo[p][prev_idx] = ret;
}

int main() {
  cin >> house.x >> house.y;
  cin >> gate.x >> gate.y >> N;

  memset(memo, -1, sizeof memo);

  while (N--) {
    Point p;
    cin >> p.x >> p.y;
    points.push_back(p - house);
  }

  gate = gate - house;
  house = Point(0, 0);

  points.push_back(gate);
  sort(points.begin(), points.end());

  ll ans = 0;

  int gate_idx = find(points.begin(), points.end(), gate) - points.begin();

  for (int i = 0; i < (int)points.size(); i++)
    if (i != gate_idx) ans = (ans + build(i, gate_idx)) % MOD;

  cout << ans << endl;
}
