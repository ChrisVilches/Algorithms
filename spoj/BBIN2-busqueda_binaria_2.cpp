#include <bits/stdc++.h>

using namespace std;

int main() {
  int N, Q;
  cin >> N >> Q;
  vector<int> nums;

  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    nums.push_back(x);
  }

  while (Q--) {
    int q;
    cin >> q;
    vector<int>::iterator it = lower_bound(nums.begin(), nums.end(), q);
    int idx = distance(nums.begin(), it);

    if (nums[idx] == q)
      cout << idx << endl;
    else
      cout << -1 << endl;
  }
}
