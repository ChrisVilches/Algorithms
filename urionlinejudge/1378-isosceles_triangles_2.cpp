#include <bits/stdc++.h>

using namespace std;

int N, x[1001], y[1001];

// Using a map to store 'long double' as keys (with precision hack).

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
    map<long double, int> dists;

    for (int j = 0; j < N; j++) {
      long double d = round(dist(i, j) * 1000000L);
      if (dists.count(d))
        dists[d]++;
      else
        dists[d] = 1;
    }

    for (auto it = dists.begin(); it != dists.end(); it++)
      ans += count(it->second);
  }

  cout << ans << endl;
}

int main() {
  while (scanf("%d", &N) == 1 && N > 0) solve();
}
