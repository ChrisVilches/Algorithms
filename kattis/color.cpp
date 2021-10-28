#include <bits/stdc++.h>

using namespace std;

int main() {
  int S, C, K;
  cin >> S >> C >> K;

  vector<int> nums;

  for (int i = 0; i < S; i++) {
    int s;
    cin >> s;
    nums.push_back(s);
  }

  sort(nums.begin(), nums.end());

  int ans = 1;
  int start = 0;
  for (int i = 0; i < (int)nums.size(); i++) {
    if (nums[i] - nums[start] > K || i - start >= C) {
      start = i;
      ans++;
    }
  }

  cout << ans << endl;
}
