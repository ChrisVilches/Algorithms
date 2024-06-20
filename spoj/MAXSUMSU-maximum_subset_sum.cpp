#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    int ans = INT_MIN;
    int curr = 0;
    for (const int x : a) {
      curr += x;
      ans = max(ans, curr);
      curr = max(curr, 0);
    }
    cout << ans << endl;
  }
}
