#include <bits/stdc++.h>

using namespace std;

void solve() {
  int k, n, num;
  cin >> k >> n;

  vector<int> nums;
  vector<int> sorted;

  for (int i = 0; i < n; i++) {
    cin >> num;
    nums.push_back(num);
  }

  sorted = nums;
  sort(sorted.begin(), sorted.end());

  int ans = 0;
  vector<int>::iterator curr = sorted.begin();
  for (int x : nums) {
    if (x == *curr)
      curr++;
    else
      ans++;
  }

  cout << k << ' ' << ans << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
