#include <bits/stdc++.h>

using namespace std;

struct Point {
  int x, y, value;
  bool operator<(const Point& p) const {
    if (x == p.x) return y < p.y;
    return x < p.x;
  }
};

struct BIT {
  BIT(int n) : bit_n(n + 1) { A.assign(bit_n, 0); }

  void range_update(int i, int j, int v) {
    update(i, v);
    update(j + 1, -v);
  }

  int query(int i) {
    i++;
    int sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

 private:
  int bit_n;
  vector<int> A;
  void update(int i, int v) {
    i++;
    for (; i < bit_n; i += i & -i) A[i] += v;
  }
};

int P, V;

void compress(vector<Point>& points) {
  sort(points.begin(), points.end(),
       [](const Point& p, const Point& q) { return p.y < q.y; });

  int y = 0;
  int curr = points[0].y;

  for (Point& p : points) {
    if (p.y != curr) {
      y += 2;
      curr = p.y;
    }
    p.y = y;
  }
}

void solve() {
  vector<Point> points;

  for (int i = 0; i < P + V; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    int value = i < P ? i + 1 : -1;
    points.push_back({x, y, value});
  }

  compress(points);

  BIT bit(points.back().y + 2);

  sort(points.begin(), points.end());

  long long int total = 0;

  for (int i = 0; i < (int)points.size(); i++) {
    Point& p = points[i];
    if (p.value == -1)
      bit.range_update(p.y, points[++i].y, 1);
    else if (bit.query(p.y + 1) % 2 == 0)
      total += p.value;
  }

  printf("%lld\n", total);
}

int main() {
  while (scanf("%d %d", &P, &V) == 2) solve();
}
