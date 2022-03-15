#include <bits/stdc++.h>
using namespace std;

bool equals_mean(int a, int b, int c) {
  double mean = (a + b) / 2.0;
  return (double)c == mean;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  vector<int> nums(4);

  cin >> nums[0] >> nums[1] >> nums[2] >> nums[3];
  sort(nums.begin(), nums.end());

  bool yes = false;

  do {
    if (equals_mean(nums[0], nums[1], nums[2])) {
      yes = true;
    }
  } while (next_permutation(nums.begin(), nums.end()));

  cout << (yes ? "YES" : "NO") << endl;
}
