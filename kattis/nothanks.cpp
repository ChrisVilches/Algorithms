#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> nums;
  while (n--) {
    int x;
    cin >> x;
    nums.push_back(x);
  }

  sort(nums.begin(), nums.end());

  int ans = 0;

  int smallest = nums[0];
  for (int i = 1; i < (int)nums.size(); i++) {
    if (nums[i] != nums[i - 1] + 1) {
      ans += smallest;
      smallest = nums[i];
    }
  }

  ans += smallest;

  cout << ans << endl;
}
