#include <bits/stdc++.h>
using namespace std;

const int max_n = 100'007;
int n, nums[max_n], range[2][max_n];

void compute_ranges(const bool asc) {
  int prev = -1;
  deque<int> q;

  for (int i = n - 1, j = n - 1; i >= 0; i--) {
    if (prev != -1 && nums[i] > nums[prev]) {
      while (!q.empty() && prev < q.back()) q.pop_back();
      j = i;
    }

    range[asc][i] = q.empty() ? j : max(j, q.back());

    if (nums[i] == -1) {
      q.emplace_front(i);
    } else {
      prev = i;
    }
  }
}

bool is_mountain(const int from, const int to) {
  if (to - from + 1 < 3) return false;
  if (range[1][from] == from) return false;
  if (range[0][to] == to) return false;
  return range[1][from] >= range[0][to];
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
    reverse(range[0], range[0] + n);

    for (int i = 0; i < n; i++) {
      range[0][i] = n - range[0][i] - 1;
    }

    cout << "NY"[solve()] << endl;
  }
}
