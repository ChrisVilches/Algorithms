#include <bits/stdc++.h>

using namespace std;

int N;

int h_index(vector<int> &nums) {
  sort(nums.begin(), nums.end());

  int h = 0;

  for (int i = 0; i < (int)nums.size(); i++) {
    int citations = nums[i];
    int papers = (int)nums.size() - i;

    if (papers <= citations) h = max(h, papers);
  }
  return h;
}

void solve() {
  vector<int> nums;

  while (N--) {
    int x;
    cin >> x;
    nums.push_back(x);
  }

  cout << h_index(nums) << endl;
}

int main() {
  while (scanf("%d", &N) == 1) solve();
}
