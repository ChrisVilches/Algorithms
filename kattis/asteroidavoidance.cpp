#include <bits/stdc++.h>
using namespace std;

struct Circle {
  int x, y, r;

  bool intersects_rectangle(const int x1, const int y1, const int x2,
                            const int y2) const {
    const int x0 = clamp(x, x1, x2);
    const int y0 = clamp(y, y1, y2);

    return hypot(x - x0, y - y0) <= r;
  }
} circles[101];

int n, w, h;

bool intersects(const int x, const int y) {
  for (int i = 0; i < n; i++) {
    if (circles[i].intersects_rectangle(x, y, x + w, y + h)) return true;
  }
  return false;
}

int main() {
  cin >> w >> h;
  int m;
  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    cin >> circles[i].x >> circles[i].y >> circles[i].r;
  }

  while (m--) {
    int x, y;
    cin >> x >> y;
    if (intersects(x, y)) {
      cout << "DOOMSLUG STOP!" << endl;
    } else {
      cout << "DOOMSLUG GO!" << endl;
    }
  }
}
