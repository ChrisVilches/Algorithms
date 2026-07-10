#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    int ans = INT_MAX;

    for (int pos = 0; pos <= 1000; pos++) {
      int res = 0;
      for (const int x : a) {
        res = max(res, abs(pos - x));
      }

      ans = min(ans, res);
    }

    cout << ans << endl;
  }
}
