#include <bits/stdc++.h>
using namespace std;

vector<int> sums(const vector<int>& nums) {
  const int n = nums.size();
  vector<int> res(1 << n, 0);

  for (int subset = 0; subset < 1 << n; subset++) {
    for (int i = 0; i < n; i++) {
      res[subset] += ((subset & (1 << i)) == 0) * nums[i];
    }
  }

  return res;
}

int main() {
  int n;
  while (cin >> n && n > 0) {
    vector<int> nums(n);
    for (auto& x : nums) cin >> x;
    const int total = accumulate(nums.begin(), nums.end(), 0, plus<int>());

    const vector<int> sums1 = sums({nums.begin(), nums.begin() + n / 2});
    const vector<int> sums2 = sums({nums.begin() + n / 2, nums.end()});

    int diff = 1e9;

    for (const int a : sums1) {
      for (const int b : sums2) {
        const int sum = a + b;
        const int other = total - sum;
        diff = min(diff, abs(other - sum));
      }
    }

    const int a = (diff + total) / 2;
    const int b = total - a;
    cout << a << ' ' << b << endl;
  }
}
