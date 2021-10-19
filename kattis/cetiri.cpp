#include <bits/stdc++.h>

using namespace std;

int main() {
  int a, b, c;
  cin >> a >> b >> c;

  vector<int> nums{a, b, c};
  vector<int> diffs;
  sort(nums.begin(), nums.end());

  for (int i = 0; i < (int)nums.size() - 1; i++)
    diffs.push_back(nums[i + 1] - nums[i]);

  sort(diffs.begin(), diffs.end());

  int min_diff = diffs[0];

  for (int i = 0; i < (int)nums.size() - 1; i++) {
    if (nums[i] + min_diff != nums[i + 1]) {
      cout << nums[i] + min_diff << endl;
      return 0;
    }
  }

  cout << nums[nums.size() - 1] + min_diff << endl;
}
