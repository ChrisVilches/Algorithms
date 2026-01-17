#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  while (cin >> n >> k) {
    vector<int> nums(n);
    for (int& x : nums) cin >> x;
    assert(n > 0);

    if (nums.front() == k) {
      cout << "fyrst" << endl;
    } else if (nums[1] == k) {
      cout << "naestfyrst" << endl;
    } else {
      const auto it = find(nums.begin(), nums.end(), k);
      const int pos = distance(nums.begin(), it) + 1;
      cout << pos << " fyrst" << endl;
    }
  }
}
