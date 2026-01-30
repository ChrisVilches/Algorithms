#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

array<pii, 4 * 100'007> tree;

pii max_query(const int p, const int l, const int r, const int i, const int j) {
  if (i > r || j < l) return {INT_MIN, -1};
  if (i <= l && r <= j) return tree[p];
  const int m = (l + r) / 2;
  return max(max_query(2 * p, l, m, i, j), max_query(2 * p + 1, m + 1, r, i, j));
}

void update(const int p, const int l, const int r, const int pos, const int val) {
  if (l == r) {
    tree[p] = {val, pos};
  } else {
    int m = (l + r) / 2;
    if (pos <= m)
      update(2 * p, l, m, pos, val);
    else
      update(2 * p + 1, m + 1, r, pos, val);
    tree[p] = max(tree[2 * p], tree[2 * p + 1]);
  }
}

vector<pii> to_sorted(const vector<int>& nums) {
  vector<pii> result;

  for (size_t i = 0; i < nums.size(); i++) {
    result.emplace_back(nums[i], -i);
  }

  sort(result.begin(), result.end());
  for (auto& [_, idx] : result) idx = -idx;

  return result;
}

int main() {
  int n;

  while (cin >> n) {
    vector<int> nums(n);
    for (auto& x : nums) cin >> x;
    fill(tree.begin(), tree.end(), pii{0, -1});

    const vector<pii> sorted = to_sorted(nums);

    update(1, 0, n - 1, sorted.back().second, 1);
    vector<int> next_idx(n, -1);

    for (int i = n - 2; i >= 0; i--) {
      const int idx = sorted[i].second;
      const auto [max_value, idx_max] = max_query(1, 0, n - 1, idx, n - 1);
      next_idx[idx] = idx_max;
      update(1, 0, n - 1, idx, 1 + max_value);
    }

    int curr_idx = max_query(1, 0, n - 1, 0, n - 1).second;

    vector<int> result;

    while (curr_idx != -1) {
      result.emplace_back(curr_idx);
      curr_idx = next_idx[curr_idx];
    }

    cout << result.size() << endl;

    for (size_t i = 0; i < result.size(); i++) {
      cout << result[i] << " \n"[i == result.size() - 1];
    }
  }
}
