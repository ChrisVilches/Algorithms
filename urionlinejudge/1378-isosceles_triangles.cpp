#include <bits/stdc++.h>

using namespace std;

int N, x[1001], y[1001];

double dist(int i, int j) {
  return sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
}

int count(int n) {
  if (n <= 1) return 0;
  if (n == 2) return 1;
  return (n - 2) * 3;
}

void solve() {
  for (int i = 0; i < N; i++) cin >> x[i] >> y[i];

  int ans = 0;

  for (int i = 0; i < N; i++) {
    vector<double> dists;

    for (int j = 0; j < N; j++) dists.push_back(dist(i, j));

    sort(dists.begin(), dists.end());

    double prev = dists[0];
    int same = 1;

    for (int j = 1; j <= (int)dists.size(); j++) {
      if (j < (int)dists.size() && prev == dists[j]) {
        same++;
      } else {
        ans += count(same);
        prev = dists[j];
        same = 1;
      }
    }
  }

  cout << ans << endl;
}

int main() {
  while (scanf("%d", &N) == 1 && N > 0) solve();
}
