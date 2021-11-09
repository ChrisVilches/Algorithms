#include <bits/stdc++.h>

using namespace std;

int main() {
  int a, b;
  cin >> a >> b;

  int ans = 0;

  while (a != b) {
    if (a < b) {
      ans += b - a;
      break;
    }

    if (a % 2 == 0)
      a /= 2;
    else
      a++;

    ans++;
  }

  cout << ans << endl;
}
