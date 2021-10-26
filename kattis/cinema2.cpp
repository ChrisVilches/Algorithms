#include <bits/stdc++.h>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> nums;
  int groups = 0;
  for (int i = 0; i < m; i++) {
    if (n < 0) break;
    int g;
    cin >> g;
    n -= g;
    if (n >= 0) groups++;
  }

  cout << (m - groups) << endl;
}
