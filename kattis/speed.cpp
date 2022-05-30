#include <bits/stdc++.h>
using namespace std;

int N;
double T, D[1001], S[1001];

double total_time(const double c) {
  double total = 0;

  for (int i = 0; i < N; i++) total += D[i] / (S[i] + c);

  return total;
}

void solve() {
  double min_speed = 1e9;

  for (int i = 0; i < N; i++) {
    cin >> D[i] >> S[i];

    min_speed = min(min_speed, S[i]);
  }

  double lo = -min_speed;
  double hi = 10000000;

  int iters = 100;

  while (iters--) {
    const double mid = (lo + hi) / 2.0;

    if (total_time(mid) > T) {
      lo = mid;
    } else {
      hi = mid;
    }
  }

  cout << fixed << setprecision(8) << lo << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N >> T) solve();
}
