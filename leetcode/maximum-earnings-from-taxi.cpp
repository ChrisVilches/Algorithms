#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAX = 100'007;
ll tree[4 * MAX];

ll max_query(const int p, const int l, const int r, const int i, const int j) {
  if (i > r || j < l) return INT_MIN;
  if (i <= l && r <= j) return tree[p];
  const int m = (l + r) / 2;
  return max(max_query(2 * p, l, m, i, j), max_query(2 * p + 1, m + 1, r, i, j));
}

void update(const int p, const int l, const int r, const int pos, const ll val) {
  if (l == r) {
    tree[p] = val;
  } else {
    int m = (l + r) / 2;
    if (pos <= m)
      update(2 * p, l, m, pos, val);
    else
      update(2 * p + 1, m + 1, r, pos, val);
    tree[p] = max(tree[2 * p], tree[2 * p + 1]);
  }
}

class Solution {
 public:
  long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
    memset(tree, 0, sizeof tree);

    map<int, vector<pair<int, ll>>> ride_map;

    for (const auto& ride : rides) {
      const int start = ride[0] - 1;
      const int end = ride[1] - 1;
      const ll tip = ride[2];

      ride_map[start].emplace_back(end, end - start + tip);
    }

    for (int idx = n - 2; idx >= 0; idx--) {
      ll result = max_query(1, 0, n - 1, idx, n - 1);

      for (const auto& [end, pay] : ride_map[idx]) {
        result = max(result, pay + max_query(1, 0, n - 1, end, n - 1));
      }

      update(1, 0, n - 1, idx, result);
    }

    return max_query(1, 0, n - 1, 0, 0);
  }
};
