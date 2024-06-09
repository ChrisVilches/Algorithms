#include <bits/stdc++.h>
using namespace std;

struct Rectangle {
  int x1, y1, x2, y2;

  bool intersects(const Rectangle& r) const {
    if (r.x2 <= x1) return false;
    if (x2 <= r.x1) return false;
    if (r.y2 <= y1) return false;
    if (y2 <= r.y1) return false;

    return true;
  }
};

void solve() {
  int n, w, h;
  cin >> n >> w >> h;
  vector<Rectangle> rectangles(n);
  for (auto& r : rectangles) cin >> r.x1 >> r.y1 >> r.x2 >> r.y2;
  int w0, h0;
  cin >> w0 >> h0;

  set<int> xs{0, w - w0};
  set<int> ys{0, h - h0};

  for (const auto& r : rectangles) {
    xs.emplace(r.x1 - w0);
    xs.emplace(r.x2);
    ys.emplace(r.y1 - h0);
    ys.emplace(r.y2);
  }

  for (const auto y : ys) {
    if (y < 0 || y + h0 > h) continue;
    for (const auto x : xs) {
      if (x < 0 || x + w0 > w) continue;

      const Rectangle candidate{x, y, x + w0, y + h0};

      if (!any_of(rectangles.begin(), rectangles.end(),
                  [&](const Rectangle& r) { return r.intersects(candidate); })) {
        cout << x << " " << y << endl;
        return;
      }
    }
  }

  cout << "Fail!" << endl;
}

int main() {
  int t;
  cin >> t;

  while (t--) solve();
}
