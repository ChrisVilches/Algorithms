#include <bits/stdc++.h>
using namespace std;

int N;
double W, speed_ships, speed_ferry;
double t1, t2;
double time_per_lane;

double calculate(const vector<pair<double, int>>& events) {
  double ans = 0;
  int curr = 0;

  for (const auto& [t, d] : events) {
    if (curr == 0 && t1 <= t2) {
      ans = max(ans, t - time_per_lane - t1);
    }

    curr += d;

    if (curr == 0) t1 = max(t1, t);
  }

  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N >> W >> speed_ships >> speed_ferry >> t1 >> t2) {
    time_per_lane = W / speed_ferry;

    vector<pair<double, int>> events;

    for (int i = 0; i < N; i++) {
      char dir;
      int m;
      cin >> dir >> m;

      for (int j = 0; j < m; j++) {
        double l, p;
        cin >> l >> p;

        const double offset = time_per_lane * speed_ships;

        if (dir == 'E') p = -p;

        p -= i * offset;

        const double time_enter = p / speed_ships;
        const double time_exit = (p + l) / speed_ships;

        events.push_back({time_enter, 1});
        events.push_back({time_exit, -1});
      }
    }

    events.push_back({t2 + time_per_lane, 0});

    sort(events.begin(), events.end());

    cout << fixed << setprecision(6) << calculate(events) << endl;
  }
}
