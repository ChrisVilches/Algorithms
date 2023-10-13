#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> read(const int N, int K) {
  map<int, int> camera_map;
  for (int i = 0; i < K; i++) {
    int a, b;
    cin >> a >> b;
    if (a > b) b += N;
    camera_map[a] = max(camera_map[a], b);
  }
  vector<pair<int, int>> res;
  for (const auto& [k, v] : camera_map) res.emplace_back(k, v);
  K = res.size();
  for (int i = 0; i < K; i++) {
    res.emplace_back(res[i].first + N, res[i].second + N);
  }
  for (int i = 0; i < K; i++) {
    res.emplace_back(res[i].first + 2 * N, res[i].second + 2 * N);
  }
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K;
  while (cin >> N >> K) {
    int ans = INT_MAX;

    vector<pair<int, int>> cameras = read(N, K);
    deque<pair<int, int>> curr{cameras.front()};

    for (int i = 1; i < (int)cameras.size();) {
      pair<int, int> best{-1, -1};

      while (i < (int)cameras.size()) {
        const auto [a, b] = cameras[i];

        if (curr.back().second < a - 1) break;

        if (best.second < b) {
          best = {a, b};
        }

        i++;
      }

      if (best.first == -1) {
        curr = {cameras[i]};
      } else if (curr.back().second < best.second) {
        curr.push_back(best);
      }

      while (!curr.empty()) {
        const int covered = curr.back().second - curr.front().first + 1;

        if (covered >= N) {
          ans = min(ans, (int)curr.size());
          curr.pop_front();
        } else {
          break;
        }
      }
    }

    if (ans == INT_MAX) {
      cout << "impossible" << endl;
    } else {
      cout << ans << endl;
    }
  }
}
