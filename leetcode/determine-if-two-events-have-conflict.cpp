#include <bits/stdc++.h>
using namespace std;

class Solution {
  double parse(const char a, const char b) {
    const int x = a - '0';
    const int y = b - '0';
    return double(10 * x + y);
  }

  double parse_time(const string& time) {
    const double hh = parse(time[0], time[1]);
    const double mm = parse(time[3], time[4]);
    return hh + (mm / 60);
  }

  bool contains(const double a, const double b, const double x) {
    return a <= x && x <= b;
  }

 public:
  bool haveConflict(vector<string>& event1, vector<string>& event2) {
    const double a = parse_time(event1[0]);
    const double b = parse_time(event1[1]);
    const double x = parse_time(event2[0]);
    const double y = parse_time(event2[1]);

    return contains(a, b, x) || contains(a, b, y) || contains(x, y, a) ||
           contains(x, y, b);
  }
};
