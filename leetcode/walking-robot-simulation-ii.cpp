#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
#define x first
#define y second

pii operator+(const pii a, const pii b) { return {a.x + b.x, a.y + b.y}; }
pii operator*(const pii p, const int k) { return {p.x * k, p.y * k}; }
pii rotate(const pii p) { return {-p.y, p.x}; }

class Robot {
  const int w, h, perimeter;
  pii dir{1, 0};
  pii pos{0, 0};

  bool is_inside(const pii p) const { return p.x >= 0 && p.y >= 0 && p.x < w && p.y < h; }

  bool is_corner(const pii p) const {
    if (p == pii{0, 0}) return true;
    if (p == pii{w - 1, 0}) return true;
    if (p == pii{w - 1, h - 1}) return true;
    return p == pii{0, h - 1};
  }

 public:
  Robot(const int width, const int height)
      : w(width), h(height), perimeter(2 * (w + h - 2)) {}

  void step(const int num) {
    const pii next = pos + (dir * num);

    if (is_inside(next)) {
      pos = next;
      return;
    }

    const pii inside{clamp(next.x, 0, w - 1), clamp(next.y, 0, h - 1)};
    const int moved = abs(inside.x - pos.x) + abs(inside.y - pos.y);

    pos = inside;
    dir = rotate(dir);

    if (is_corner(pos) && (num - moved) % perimeter == 0) {
      dir = rotate(dir * -1);
      return;
    }

    step((num - moved) % perimeter);
  }

  vector<int> getPos() const { return {pos.x, pos.y}; }

  string getDir() const {
    if (dir.x == 1) return "East";
    if (dir.y == 1) return "North";
    if (dir.x == -1) return "West";
    return "South";
  }
};
