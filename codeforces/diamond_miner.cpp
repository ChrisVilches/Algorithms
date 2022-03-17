#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

void solve() {
  vector<ld> miners, mines;

  int N;
  scanf("%d", &N);

  for (int i = 0; i < 2 * N; i++) {
    ld x, y;
    scanf("%Lf%Lf", &x, &y);

    if (x == 0) {
      miners.push_back(fabs(y));
    } else {
      mines.push_back(fabs(x));
    }
  }

  sort(miners.begin(), miners.end());
  sort(mines.begin(), mines.end());

  ld total = 0;

  for (int i = 0; i < N; i++) {
    total += hypot(mines[i], miners[i]);
  }

  printf("%.15Lf\n", total);
}

int main() {
  int t;
  scanf("%d", &t);

  while (t--) solve();
}
