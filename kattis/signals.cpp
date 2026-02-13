#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;

  while (cin >> n) {
    vector<int> nums;

    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;

      if (nums.empty() || x > nums.back()) {
        nums.emplace_back(x);
      } else {
        const auto it = lower_bound(nums.begin(), nums.end(), x);
        const int idx = distance(nums.begin(), it);
        nums[idx] = x;
      }
    }

    cout << nums.size() << endl;
  }
}
