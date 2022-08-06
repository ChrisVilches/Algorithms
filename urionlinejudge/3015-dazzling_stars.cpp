#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Point {
  ll x, y;

  Point() {}
  Point(ll x, ll y) : x(x), y(y) {}

  Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
  ll dot(const Point &p) const { return x * p.x + y * p.y; }
  ll cross(const Point &p) const { return x * p.y - y * p.x; }
  bool deg0(const Point &p) const { return cross(p) == 0 && dot(p) > 0; }

  int quadrant() const {
    if (y != 0) return y > 0 ? 0 : 1;
    return x > 0 ? 0 : 1;
  }
};

int N;
Point pts[1007];
int brightness[1007];

bool cmp(const Point &p, const Point &q) {
  int q1 = p.quadrant();
  int q2 = q.quadrant();

  if (q1 != q2) return q1 < q2;
  return p.cross(q) > 0;
}

bool possible() {
  vector<Point> p;

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (brightness[i] < brightness[j]) p.push_back(pts[j] - pts[i]);

  if (p.empty()) return true;

  sort(p.begin(), p.end(), cmp);

  if (p.front().deg0(p.back())) return true;
  p.push_back(p[0]);

  for (int i = 0; i < (int)p.size() - 1; i++) {
    ll dot = p[i].dot(p[i + 1]);
    ll cross = p[i].cross(p[i + 1]);

    if ((dot <= 0 || cross != 0) && cross <= 0) return true;
  }

  return false;
}

int main() {
  while (scanf("%d", &N) == 1) {
    for (int i = 0; i < N; i++) cin >> pts[i].x >> pts[i].y >> brightness[i];
    cout << (possible() ? 'Y' : 'N') << endl;
  }
}
