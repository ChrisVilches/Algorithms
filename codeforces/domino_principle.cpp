#include <bits/stdc++.h>
using namespace std;

const int MAX = 100'007;
array<int, MAX> dp;
array<int, 4 * MAX> tree;

int max_idx(const int a, const int b) {
  if (a == -1 || b == -1) return max(a, b);
  return a + dp[a] > b + dp[b] ? a : b;
}

void build_tree(int p, int L, int R) {
  if (L == R) {
    tree[p] = L;
    dp[L] = 1;
  } else {
    build_tree(2 * p, L, (L + R) / 2);
    build_tree(2 * p + 1, (L + R) / 2 + 1, R);
    tree[p] = max_idx(tree[2 * p], tree[2 * p + 1]);
  }
}

int max_query(int p, int L, int R, int i, int j) {
  if (i > R || j < L) return -1;
  if (L >= i && R <= j) return tree[p];

  return max_idx(max_query(2 * p, L, (L + R) / 2, i, j),
                 max_query(2 * p + 1, (L + R) / 2 + 1, R, i, j));
}

void update(int p, int L, int R, int pos, int new_val) {
  if (L == R) {
    dp[pos] = new_val;
  } else {
    int m = (L + R) / 2;
    if (pos <= m)
      update(2 * p, L, m, pos, new_val);
    else
      update(2 * p + 1, m + 1, R, pos, new_val);

    tree[p] = max_idx(tree[2 * p], tree[2 * p + 1]);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  while (cin >> N) {
    vector<pair<int, int>> dominos(N);

    vector<int> x_order;
    map<int, int> x_sorted_order;

    for (int i = 0; i < N; i++) {
      cin >> dominos[i].first >> dominos[i].second;
      x_order.push_back(dominos[i].first);
    }

    sort(dominos.begin(), dominos.end());

    for (int i = 0; i < N; i++) x_sorted_order[dominos[i].first] = i;

    build_tree(1, 0, N - 1);

    for (int i = N - 2; i >= 0; i--) {
      const auto [x, h] = dominos[i];
      const pair<int, int> search = {x + h - 1, INT_MAX};

      const int j = lower_bound(dominos.begin(), dominos.end(), search) - dominos.begin();
      const int max_idx = max_query(1, 0, N - 1, i, j - 1);

      update(1, 0, N - 1, i, max_idx - i + dp[max_idx]);
    }

    for (const int x : x_order) {
      const int i = x_sorted_order[x];
      cout << dp[i] << ' ';
    }
    cout << endl;
  }
}
