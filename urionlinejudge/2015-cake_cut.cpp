#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
  ll x, y;
  inline Point operator-(const Point& p) const { return Point{x - p.x, y - p.y}; }
  inline ll operator^(const Point& p) const { return (x * p.y) - (y * p.x); }
  inline Point to(const Point& p) const { return p - *this; }
};

ll area2(const int i, const int j, const int k, const vector<Point>& polygon) {
  const Point& a = polygon[i % polygon.size()];
  const Point& b = polygon[j % polygon.size()];
  const Point& c = polygon[k % polygon.size()];
  return abs(a.to(b) ^ a.to(c));
}

ll total_area2(const vector<Point>& polygon) {
  ll accum = 0;
  for (int i = 1; i < (int)polygon.size() - 1; i++) {
    accum += area2(0, i, i + 1, polygon);
  }
  return accum;
}

pair<ll, ll> calculate(const vector<Point>& polygon) {
  const ll total = total_area2(polygon);
  ll best_piece = INT_MIN;
  ll curr_piece = 0;

  const auto diff = [total](const ll piece) {
    ll other_piece = total - piece;
    return abs(piece - other_piece);
  };

  for (int i = 0, j = 1; i < (int)polygon.size(); i++) {
    for (;; j++) {
      const ll next_piece = curr_piece + area2(i, j, j + 1, polygon);

      if (diff(next_piece) >= diff(curr_piece)) {
        best_piece = max({best_piece, curr_piece, total - curr_piece});
        break;
      }

      curr_piece += area2(i, j, j + 1, polygon);
    }

    curr_piece -= area2(i, i + 1, j, polygon);
  }

  return {best_piece, total - best_piece};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int N;

  while (cin >> N) {
    vector<Point> polygon(N);

    for (int i = 0; i < N; i++) cin >> polygon[i].x >> polygon[i].y;

    const auto [A, B] = calculate(polygon);

    cout << A << " " << B << endl;
  }
}
