#include <bits/stdc++.h>
using namespace std;

struct Printer {
  int C, M, Y, K;
  int total_ink() const { return C + M + Y + K; }
};

const int TARGET = 1'000'000;

void solve() {
  array<Printer, 3> printers;

  for (int i = 0; i < 3; i++) {
    cin >> printers[i].C;
    cin >> printers[i].M;
    cin >> printers[i].Y;
    cin >> printers[i].K;
  }

  Printer result{INT_MAX, INT_MAX, INT_MAX, INT_MAX};

  for (const Printer& p : printers) {
    result.C = min(result.C, p.C);
    result.M = min(result.M, p.M);
    result.Y = min(result.Y, p.Y);
    result.K = min(result.K, p.K);
  }

  int iters = TARGET * 4;

  while (iters-- && result.total_ink() != TARGET) {
    switch (iters % 4) {
      case 0:
        if (result.C > 0) result.C--;
        break;
      case 1:
        if (result.K > 0) result.K--;
        break;
      case 2:
        if (result.M > 0) result.M--;
        break;
      case 3:
        if (result.Y > 0) result.Y--;
        break;
    }
  }

  if (result.total_ink() != TARGET) {
    cout << "IMPOSSIBLE" << endl;
  } else {
    cout << result.C << " " << result.M << " " << result.Y << " " << result.K << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
}
