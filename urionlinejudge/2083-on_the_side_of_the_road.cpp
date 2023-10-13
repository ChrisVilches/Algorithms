#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define x first
#define y second

int main() {
  int N;
  while (cin >> N) {
    vector<pii> points(N);
    for (auto& p : points) cin >> p.x >> p.y;

    vector<tuple<double, ll, pii, pii>> intersections;

    for (int i = 0; i < N; i++) {
      for (int j = i + 1; j < N; j++) {
        const pii p = points[i];
        const pii q = points[j];

        if (p.y == q.y) continue;

        if (p.x == q.x) {
          intersections.emplace_back(p.x, LONG_LONG_MAX, p, q);
          continue;
        }

        const double slope = (p.y - q.y) / (double)(p.x - q.x);
        const double b = p.y - slope * p.x;
        const ll slope_int = round(slope * 1000000);
        intersections.emplace_back(-b / slope, slope_int, p, q);
      }
    }

    vector<int> counts{N};
    set<pii> blocked;
    set<ll> slopes;

    double prev = -numeric_limits<double>::infinity();
    sort(intersections.begin(), intersections.end());

    for (const auto& [x, slope, p, q] : intersections) {
      if (fabs(x - prev) > 1e-8) {
        counts.push_back(0);
        blocked.clear();
        slopes.clear();
        prev = x;
      }

      blocked.emplace(p);
      blocked.emplace(q);
      slopes.emplace(slope);
      counts.back() = N - blocked.size() + slopes.size();
      prev = x;
    }

    cout << set<int>{counts.begin(), counts.end()}.size() << endl;
  }
}
