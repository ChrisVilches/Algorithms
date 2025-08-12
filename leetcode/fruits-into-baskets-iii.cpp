#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> tree;

  void update(int p, int L, int R, int pos, int new_val) {
    if (L == R) {
      tree[p] = new_val;
    } else {
      const int m = (L + R) / 2;
      if (pos <= m)
        update(2 * p, L, m, pos, new_val);
      else
        update(2 * p + 1, m + 1, R, pos, new_val);
      tree[p] = max(tree[2 * p], tree[2 * p + 1]);
    }
  }

  int first_equal_or_greater(const int n, const int val) {
    int p = 1;
    if (tree[p] < val) return -1;
    int l = 0, r = n - 1;

    while (l != r) {
      const int m = (l + r) / 2;
      if (tree[2 * p] >= val)
        r = m, p = 2 * p;
      else
        l = m + 1, p = 2 * p + 1;
    }

    return l;
  }

 public:
  int numOfUnplacedFruits(const vector<int>& fruits, const vector<int>& baskets) {
    const int n = fruits.size();

    tree.assign(n * 4, 0);

    for (size_t i = 0; i < baskets.size(); i++) {
      update(1, 0, n - 1, i, baskets[i]);
    }

    int ans = 0;

    for (size_t i = 0; i < fruits.size(); i++) {
      const int idx = first_equal_or_greater(n, fruits[i]);
      ans += idx == -1;

      if (idx != -1) update(1, 0, n - 1, idx, 0);
    }

    return ans;
  }
};
