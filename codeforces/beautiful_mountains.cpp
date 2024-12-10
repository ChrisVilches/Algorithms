#include <bits/stdc++.h>
using namespace std;

const int max_n = 100'007;
int n, nums[max_n], ranges[2][max_n];

void compute_ranges(const bool asc) {
  int prev = -1;
  int missing_idx = -1;

  for (int i = n - 1, j = n - 1; i >= 0; i--) {
    if (prev != -1 && nums[i] > nums[prev]) {
      if (prev < missing_idx) missing_idx = -1;
      j = i;
    }

    ranges[asc][i] = max(missing_idx, j);

    if (nums[i] == -1) {
      missing_idx = i;
    } else {
      prev = i;
    }
  }
}

bool is_mountain(const int from, const int to) {
  if (to - from + 1 < 3) return false;
  if (ranges[1][from] == from) return false;
  if (ranges[0][to] == to) return false;
  return ranges[1][from] >= ranges[0][to];
}

bool solve() {
  for (int size = 3; size <= n; size++) {
    for (int i = 0;; i += size) {
      const int j = min(i + size - 1, n - 1);

      if (!is_mountain(i, j)) break;

      if (j == n - 1) return true;
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> n) {
    for (int i = 0; i < n; i++) cin >> nums[i];

    compute_ranges(true);
    reverse(nums, nums + n);
    compute_ranges(false);
    reverse(ranges[0], ranges[0] + n);

    for (int i = 0; i < n; i++) {
      ranges[0][i] = n - ranges[0][i] - 1;
    }

    cout << "NY"[solve()] << endl;
  }
}
