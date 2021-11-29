#include <bits/stdc++.h>

using namespace std;

bool arithmetic(vector<int> nums) {
  if (nums.size() <= 2) return true;

  int diff = nums[1] - nums[0];

  for (int i = 0; i < (int)nums.size() - 1; i++) {
    if (nums[i + 1] - nums[i] != diff) return false;
  }
  return true;
}

void solve() {
  int N;
  cin >> N;
  vector<int> nums;

  while (N--) {
    int x;
    cin >> x;
    nums.push_back(x);
  }

  if (arithmetic(nums)) {
    cout << "arithmetic" << endl;
    return;
  }

  sort(nums.begin(), nums.end());
  if (arithmetic(nums)) {
    cout << "permuted arithmetic" << endl;
    return;
  }

  cout << "non-arithmetic" << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
