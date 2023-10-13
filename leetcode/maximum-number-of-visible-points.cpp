#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  Point operator-(const Point p) const { return {x - p.x, y - p.y}; }
  static Point from_vec(const vector<int>& point) {
    return Point{point.front(), point.back()};
  }
};

class Solution {
  int solve(const vector<Point>& points, const double max_angle) {
    vector<double> angles;

    for (const auto p : points) {
      const double ang = atan2(p.y, p.x);
      angles.push_back(ang);
      angles.push_back(ang + (M_PI * 2));
    }

    sort(angles.begin(), angles.end());

    int result = 0;

    for (int i = 0, j = 0; i < (int)angles.size(); i++) {
      while (j < (int)angles.size() && angles[j] - angles[i] <= max_angle) j++;

      result = max(result, j - i);
    }

    return result;
  }

  double deg_to_rad(const int deg) const { return M_PI * deg / 180.0; }

 public:
  int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
    vector<Point> clean_points;

    const Point clean_location = Point::from_vec(location);

    int in_origin = 0;

    for (const auto& point : points) {
      const Point p = Point::from_vec(point) - clean_location;

      if (p.x == 0 && p.y == 0) {
        in_origin++;
      } else {
        clean_points.push_back(p);
      }
    }

    return in_origin + solve(clean_points, deg_to_rad(angle));
  }
};
