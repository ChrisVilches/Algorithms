#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> tree, lazy;

  void update_aux(int a, int b, int node, int x) {
    tree[node] = x;

    if (a == b) return;
    lazy[node * 2] = x;
    lazy[node * 2 + 1] = x;
  }

  void propagate_one_level(int node, int a, int b) {
    if (!lazy[node]) return;
    update_aux(a, b, node, lazy[node]);

    lazy[node] = 0;
  }

  void update_tree(int node, int a, int b, int i, int j, int x) {
    propagate_one_level(node, a, b);

    if (a > j || b < i) return;

    if (i <= a && b <= j) {
      update_aux(a, b, node, x);
      return;
    }

    update_tree(node * 2, a, (a + b) / 2, i, j, x);
    update_tree(1 + node * 2, 1 + (a + b) / 2, b, i, j, x);

    tree[node] = x;
  }

  int max_query(int node, int a, int b, int i, int j) {
    if (a > j || b < i) return 0;

    propagate_one_level(node, a, b);

    if (i <= a && b <= j) return tree[node];

    const int q1 = max_query(node * 2, a, (a + b) / 2, i, j);
    const int q2 = max_query(1 + node * 2, 1 + (a + b) / 2, b, i, j);

    return max(q1, q2);
  }

  pair<int, vector<tuple<int, int, int>>> compress(vector<vector<int>>& positions) {
    vector<tuple<int, int, int>> result(positions.size());

    for (int i = 0; i < (int)positions.size(); i++) {
      const int h = positions[i][1];
      get<2>(result[i]) = h;
    }

    vector<tuple<int, bool, int>> events;

    for (int i = 0; i < (int)positions.size(); i++) {
      const int x0 = positions[i][0];
      const int x1 = x0 + positions[i][1];
      events.emplace_back(x0, true, i);
      events.emplace_back(x1, false, i);
    }

    sort(events.begin(), events.end());
    int curr_x = 0;

    for (const auto& [x, left, idx] : events) {
      if (left) {
        get<0>(result[idx]) = curr_x;
      } else {
        get<1>(result[idx]) = curr_x;
      }
      curr_x += 2;
    }

    return {curr_x, result};
  }

 public:
  vector<int> fallingSquares(vector<vector<int>>& positions) {
    const auto [total_x, positions2] = compress(positions);
    const int n = total_x + 1;
    tree.assign(4 * n, 0);
    lazy.assign(4 * n, 0);
    vector<int> ans;

    int curr_tallest = 0;

    for (const auto& [x0, x1, h] : positions2) {
      const int tallest = max_query(1, 0, n - 1, x0, x1);
      const int new_height = tallest + h;
      update_tree(1, 0, n - 1, x0, x1, new_height);
      curr_tallest = max(new_height, curr_tallest);
      ans.emplace_back(curr_tallest);
    }

    return ans;
  }
};
