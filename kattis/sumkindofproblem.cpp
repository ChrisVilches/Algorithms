#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int k, n;
    cin >> k >> n;

    int all = 0, odd = 0, even = 0;

    for (int i = 0; i <= n; i++) all += i;
    for (int i = 2; i <= 2 * n; i += 2) even += i;
    for (int i = 1; i <= 2 * n - 1; i += 2) odd += i;

    cout << k << ' ' << all << ' ' << odd << ' ' << even << endl;
  }
}
