#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, X;

  while (cin >> N >> X) {
    vector<pair<int, int>> activities;

    for (int i = 0; i < N; i++) {
      int s, d;
      cin >> s >> d;
      activities.push_back({s, d});
    }

    sort(activities.begin(), activities.end());

    int ans_t = INT_MAX;
    int ans_c = INT_MAX;

    for (int t = 0; t <= 480; t++) {
      int conflicts = 0;
      int curr_minute = t;

      for (const auto& [start, duration] : activities) {
        const int end = start + duration;

        while (curr_minute <= end) {
          if (curr_minute >= start) conflicts++;
          curr_minute += X;
        }

        if (conflicts >= ans_c) break;
      }

      if (conflicts < ans_c) {
        ans_c = conflicts;
        ans_t = t;
      }
    }

    cout << ans_t << " " << ans_c << endl;
  }
}
