#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, q;
    cin >> n >> q;
    assert(q == 0);
    vector<int> nums(n);
    for (int& x : nums) cin >> x;

    ll ans = nums.front();
    ll min_val = nums.front();

    for (const ll x : nums) {
      const ll sum = x + ans - min_val;

      if (sum > ans) {
        ans = sum;
        min_val = ans;
      }

      min_val = min(min_val, x);
    }

    cout << ans << endl;
  }
}
