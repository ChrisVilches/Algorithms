#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  int ans = 0;
  int side = 1;

  while (true) {
    N -= pow(side, 2);
    side += 2;
    if (N < 0) break;
    ans++;
  }

  cout << ans << endl;
}
