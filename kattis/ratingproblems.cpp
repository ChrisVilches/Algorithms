#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  cin >> n >> k;

  double total = 0;

  for (int i = 0; i < k; i++) {
    int x;
    cin >> x;
    total += x;
  }

  const double extra = (k - n) * 3;
  const double min_avg = (total + extra) / n;
  const double max_avg = (total - extra) / n;

  cout << fixed << setprecision(6) << min_avg << ' ' << max_avg << endl;
}
