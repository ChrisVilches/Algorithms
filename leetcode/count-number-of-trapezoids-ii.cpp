#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int safe(const double x) { return round(x * 100); }

struct Point {
  int x, y;
  int dist2(const Point p) const {
    const int dx = x - p.x;
    const int dy = y - p.y;
    return (dx * dx) + (dy * dy);
  }
};

struct Line {
  ll slope;
  int b;
  bool operator==(const Line l) const { return slope == l.slope && b == l.b; }
  Line static from_points(const Point p, const Point q) {
    if (p.x == q.x) {
      return {LONG_LONG_MAX, p.x};
    } else {
      ll dy = p.y - q.y;
      ll dx = p.x - q.x;
      const double sl = static_cast<double>(dy) / static_cast<double>(dx);
      const int g = gcd(dx, dy);
      dx /= g;
      dy /= g;
      if (dx < 0 || (dx == 0 && dy < 0)) {
        dx = -dx;
        dy = -dy;
      }

      return {dy + (dx << 30), safe(p.y - (sl * p.x))};
    }
  }
};

struct LineHash {
  size_t operator()(const Line l) const noexcept { return l.slope ^ l.b; }
};

class Solution {
 public:
  int countTrapezoids(const vector<vector<int>>& input) {
    vector<Point> points;
    for (const vector<int>& vec : input) {
      points.emplace_back(vec.front(), vec.back());
    }

    const int n = points.size();

    unordered_map<ll, int> count_by_slope;
    unordered_map<Line, int, LineHash> count_by_line;
    unordered_map<int, unordered_map<Line, int, LineHash>> count_by_sized_lines;
    unordered_map<int, unordered_map<ll, int>> slope_len_total;

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        const Line line = Line::from_points(points[i], points[j]);

        count_by_slope[line.slope]++;
        count_by_line[line]++;
        const int len = points[i].dist2(points[j]);
        slope_len_total[len][line.slope]++;
        count_by_sized_lines[len][line]++;
      }
    }

    int ans = 0;

    for (const auto& [line, count] : count_by_line) {
      const int other = count_by_slope[line.slope] - count;
      ans += count * other;
    }

    int minus = 0;

    for (const auto& [len, line_to_count] : count_by_sized_lines) {
      const auto& m = slope_len_total[len];

      for (const auto& [line, count] : line_to_count) {
        const int other = m.at(line.slope) - count;
        minus += count * other;
      }
    }

    return (ans / 2) - (minus / 4);
  }
};
