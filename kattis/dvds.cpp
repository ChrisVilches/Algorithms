#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n, dvd;
  cin >> n;

  int ans = 0;
  int curr = 1;
  for (int i = 0; i < n; i++) {
    cin >> dvd;
    if (dvd == curr)
      curr++;
    else
      ans++;
  }

  cout << ans << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
