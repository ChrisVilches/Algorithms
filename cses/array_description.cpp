#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll mod = 1e9 + 7;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  while (cin >> n >> m) {
    vector<int> nums(n);
    for (int& x : nums) cin >> x;

    vector<ll> curr(m + 1, 0), next(m + 1);

    for (int i = 1; i <= m; i++) {
      next[i] = nums.back() == 0 || nums.back() == i;
    }

    for (int i = n - 2; i >= 0; i--) {
      fill(curr.begin(), curr.end(), 0);

      for (int j = 1; j <= m; j++) {
        if (nums[i] != 0 && nums[i] != j) continue;

        for (int v = j - 1; v <= j + 1; v++) {
          if (v < 1 || v > m) continue;

          curr[j] += next[v];
          curr[j] %= mod;
        }
      }

      curr.swap(next);
    }

    ll res = 0;

    for (const ll x : next) {
      res = (res + x) % mod;
    }

    cout << res << endl;
  }
}
