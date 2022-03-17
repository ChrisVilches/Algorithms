#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;

  cin >> N;

  int ans = 0;

  while (N--) {
    int a, b, c;
    cin >> a >> b >> c;
    ans += (a + b + c) >= 2;
  }

  cout << ans << endl;
}
