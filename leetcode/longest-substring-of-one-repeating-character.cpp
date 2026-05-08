#include <bits/stdc++.h>
using namespace std;

class Solution {
  using pii = pair<int, int>;
  vector<pii> tree, lazy;
  int n;
  const pii negative{1, 0};

  static bool cmp(const pii a, const pii b) {
    return a.second - a.first < b.second - b.first;
  }

  void propagate_one_level(int node, int a, int b) {
    if (lazy[node] == negative) return;

    if (a != b) {
      lazy[node * 2] = lazy[node];
      lazy[node * 2 + 1] = lazy[node];
    }

    tree[node] = lazy[node];
    lazy[node] = negative;
  }

  void update_tree(int node, int a, int b, int i, int j, pii x) {
    propagate_one_level(node, a, b);

    if (a > j || b < i) return;

    if (i <= a && b <= j) {
      lazy[node] = x;
      propagate_one_level(node, a, b);
    } else {
      update_tree(node * 2, a, (a + b) / 2, i, j, x);
      update_tree(1 + node * 2, 1 + (a + b) / 2, b, i, j, x);
      tree[node] = max(tree[node * 2], tree[node * 2 + 1], cmp);
    }
  }

  pii max_query(int node, int a, int b, int i, int j) {
    propagate_one_level(node, a, b);

    if (a > j || b < i) return negative;
    if (i <= a && b <= j) return tree[node];

    const pii q1 = max_query(node * 2, a, (a + b) / 2, i, j);
    const pii q2 = max_query(1 + node * 2, 1 + (a + b) / 2, b, i, j);

    return max(q1, q2, cmp);
  }

  pii get(const int i) { return max_query(1, 0, n - 1, i, i); }
  void update_range(const int l, const int r) { update_tree(1, 0, n - 1, l, r, {l, r}); }
  void split(const int i) {
    const pii left = get(i - 1);
    const pii right = get(i + 1);

    if (left.second >= i) update_range(left.first, i - 1);
    if (right.first <= i) update_range(i + 1, right.second);
    update_range(i, i);
  }

  vector<pii> string_ranges(const string s) const {
    vector<pair<int, int>> ranges;

    for (int i = 0; i < (int)s.size(); i++) {
      if (ranges.empty() || s[i - 1] != s[i]) {
        ranges.emplace_back(i, i);
      }
      ranges.back().second = i;
    }

    return ranges;
  }

 public:
  vector<int> longestRepeating(string s, const string queryCharacters,
                               const vector<int>& queryIndices) {
    s = '$' + s + '$';
    n = s.size();

    tree.assign(4 * n, negative);
    lazy.assign(4 * n, negative);

    for (const auto& [a, b] : string_ranges(s)) {
      update_range(a, b);
    }

    vector<int> ans;

    for (int i = 0; i < (int)queryCharacters.size(); i++) {
      const int idx = queryIndices[i] + 1;
      const char c = queryCharacters[i];

      split(idx);

      int l = idx, r = idx;

      if (c == s[idx - 1]) l = min(l, get(idx - 1).first);
      if (c == s[idx + 1]) r = max(r, get(idx + 1).second);

      update_range(l, r);

      s[idx] = c;

      const auto [a, b] = max_query(1, 0, n - 1, 0, n - 1);
      ans.emplace_back(b - a + 1);
    }

    return ans;
  }
};
