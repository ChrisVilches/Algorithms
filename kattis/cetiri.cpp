#include <bits/stdc++.h>

using namespace std;

int main() {
  int a, b, c;
  cin >> a >> b >> c;

  vector<int> nums{a, b, c};
  unordered_map<int, int> diffs;
  sort(nums.begin(), nums.end());

  for (int i = 0; i < (int)nums.size() - 1; i++) {
    int diff = nums[i + 1] - nums[i];
    if (diffs.find(diff) == diffs.end()) {
      diffs[diff] = 1;
    } else {
      diffs[diff]++;
    }
  }

  vector<int> possible_diffs;

  for (auto it = diffs.begin(); it != diffs.end(); ++it) {
    possible_diffs.push_back(it->first);
  }

  sort(possible_diffs.begin(), possible_diffs.end());

  int min_diff = possible_diffs[0];

  for (int i = 0; i < (int)nums.size() - 1; i++) {
    if (nums[i] + min_diff != nums[i + 1]) {
      cout << nums[i] + min_diff << endl;
      return 0;
    }
  }

  cout << nums[nums.size() - 1] + min_diff << endl;
}
