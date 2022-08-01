#include <bits/stdc++.h>
using namespace std;

array<long long, 200007> psum;

long long sum_range(const int l, const int r) { return psum[r + 1] - psum[l]; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, Q;

  cin >> N;

  vector<int> original_nums(N);

  for (int& x : original_nums) cin >> x;

  cin >> Q;

  vector<pair<int, int>> ops;

  vector<int> nums;

  for (int i = 0; i < Q; i++) {
    int type;
    cin >> type;

    if (type == 1) {
      int l, r;
      cin >> l >> r;
      ops.emplace_back(l - 1, r - 1);
    } else {
      int x;
      cin >> x;
      nums.push_back(x);
      ops.emplace_back(-1, -1);
    }
  }

  reverse(nums.begin(), nums.end());

  int start_idx = nums.size();

  copy(original_nums.begin(), original_nums.end(), back_inserter(nums));

  psum[0] = 0;

  for (int i = 0; i < (int)nums.size(); i++) {
    psum[i + 1] = psum[i] + nums[i];
  }

  for (const auto& [l, r] : ops) {
    if (l == -1 || r == -1) {
      start_idx--;
      continue;
    }

    cout << sum_range(start_idx + l, start_idx + r) << '\n';
  }
}
