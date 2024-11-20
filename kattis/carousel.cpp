#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, m;

  while (cin >> n >> m && n > 0 && m > 0) {
    pair<int, int> ans{-1, -1};
    double min_price = DBL_MAX;

    while (n--) {
      int a, b;
      cin >> a >> b;
      if (a > m) continue;

      const double price = (double)b / a;

      if (price < min_price || (price == min_price && a > ans.first)) {
        ans = {a, b};
        min_price = price;
      }
    }

    if (ans.first == -1) {
      cout << "No suitable tickets offered" << endl;
    } else {
      cout << "Buy " << ans.first << " tickets for $" << ans.second << endl;
    }
  }
}
