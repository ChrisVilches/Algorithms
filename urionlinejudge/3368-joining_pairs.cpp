#include <bits/stdc++.h>
using namespace std;

int W, H;

struct Point {
  int x, y, value;

  bool is_border() const { return x == W || x == 0 || y == H || y == 0; }

  static Point from_stdin(const int value) {
    Point p;
    cin >> p.x >> p.y;
    p.value = value;
    return p;
  }
};

bool solve() {
  int N;
  cin >> N;

  vector<Point> points;

  for (int i = 0; i < N; i++) {
    const Point p = Point::from_stdin(i + 1);
    const Point q = Point::from_stdin(i + 1);

    if (p.is_border() && q.is_border()) {
      points.push_back(p);
      points.push_back(q);
    }
  }

  vector<pair<int, int>> bottom, top, left, right, border;

  for (const auto& [x, y, value] : points) {
    if (x == 0) {
      left.push_back({-y, value});
    } else if (y == 0) {
      bottom.push_back({x, value});
    } else if (x == W) {
      right.push_back({y, value});
    } else if (y == H) {
      top.push_back({-x, value});
    }
  }

  sort(bottom.begin(), bottom.end());
  sort(right.begin(), right.end());
  sort(top.begin(), top.end());
  sort(left.begin(), left.end());

  copy(bottom.begin(), bottom.end(), back_inserter(border));
  copy(right.begin(), right.end(), back_inserter(border));
  copy(top.begin(), top.end(), back_inserter(border));
  copy(left.begin(), left.end(), back_inserter(border));

  stack<int> active;

  for (const auto& [_, value] : border) {
    if (!active.empty() && active.top() == value) {
      active.pop();
    } else {
      active.push(value);
    }
  }

  return active.empty();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> W >> H) {
    cout << (solve() ? "Y" : "N") << endl;
  }
}
