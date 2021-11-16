#include <bits/stdc++.h>

using namespace std;

int stepladders(vector<int>& nums) {
  if (nums.size() <= 2) return 1;

  int diff = abs(nums[0] - nums[1]);

  int ans = 1;

  for (int i = 0; i < (int)nums.size() - 1; i++) {
    if (abs(nums[i] - nums[i + 1]) == diff) continue;

    ans++;
    diff = abs(nums[i] - nums[i + 1]);
  }

  return ans;
}

int main() {
  int N;
  cin >> N;

  vector<int> nums;
  while (N--) {
    int x;
    cin >> x;
    nums.push_back(x);
  }

  cout << stepladders(nums) << endl;
}
