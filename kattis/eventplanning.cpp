#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, b, h, w;

  while (cin >> n >> b >> h >> w) {
    int ans = INT_MAX;

    while (h--) {
      int p, a;
      cin >> p;
      int W = w;
      bool ok = false;

      while (W--) {
        cin >> a;
        if (a >= n) ok = true;
      }

      if (ok) {
        ans = min(ans, p * n);
      }
    }

    if (ans == INT_MAX || ans > b) {
      cout << "stay home" << endl;
    } else {
      cout << ans << endl;
    }
  }
}
