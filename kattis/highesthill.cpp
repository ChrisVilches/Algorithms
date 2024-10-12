#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> remove_adjacent_duplicates(vector<ll> nums) {
  int k = 0;
  for (const auto x : nums) {
    if (k == 0 || nums[k - 1] != x) {
      nums[k++] = x;
    }
  }

  nums.resize(k);
  return nums;
}

int main() {
  int n;

  while (cin >> n) {
    vector<ll> H(n);
    for (auto& x : H) cin >> x;

    H = remove_adjacent_duplicates(H);
    n = H.size();

    ll prev_valley = -1;
    ll curr_highest = 0;
    ll ans = 0;

    for (int i = 0; i < n; i++) {
      const bool valley = (i == 0 || H[i - 1] > H[i]) && (i == n - 1 || H[i] < H[i + 1]);

      curr_highest = max(curr_highest, H[i]);

      if (!valley) continue;

      if (prev_valley != -1) {
        ans = max(ans, curr_highest - max(prev_valley, H[i]));
      }

      prev_valley = H[i];
      curr_highest = 0;
    }

    cout << ans << endl;
  }
}
