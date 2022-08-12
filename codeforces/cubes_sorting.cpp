#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;
    vector<int> nums(N);
    for (int& n : nums) cin >> n;

    bool ok = false;

    for (int i = 0; i < N - 1; i++) {
      if (nums[i] <= nums[i + 1]) {
        ok = true;
        break;
      }
    }

    cout << (ok ? "YES" : "NO") << '\n';
  }
}
