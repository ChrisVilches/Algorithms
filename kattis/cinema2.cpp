#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, m, g, groups = 0;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    if (n < 0) break;
    cin >> g;
    n -= g;
    if (n >= 0) groups++;
  }

  cout << (m - groups) << endl;
}
