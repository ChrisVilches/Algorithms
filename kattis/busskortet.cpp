#include <bits/stdc++.h>
using namespace std;

int ceil_hundred(const int x) { return ((x + 99) / 100) * 100; }

int main() {
  int k;
  cin >> k;
  k = ceil_hundred(k);
  int ans = 0;
  array<int, 3> charges{500, 200, 100};
  while (k > 0) {
    int selected;
    for (const int c : charges) {
      selected = c;
      if (k >= c) break;
    }

    k -= selected;
    ans++;
  }
  cout << ans << endl;
}
