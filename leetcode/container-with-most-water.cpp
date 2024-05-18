#include <bits/stdc++.h>
using namespace std;

struct Segtree {
 private:
  vector<int> tree;
  int n;

  void build(const vector<int>& arr, int v, int L, int R) {
    if (L == R) {
      tree[v] = arr[L];
    } else {
      build(arr, 2 * v, L, (L + R) / 2);
      build(arr, 2 * v + 1, (L + R) / 2 + 1, R);
      tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    }
  }

  int rightmost_greater(int v, int lv, int rv, int l, int r, int x) {
    if (lv > r || rv < l) return -1;
    if (l <= lv && rv <= r) {
      if (tree[v] < x) return -1;
      while (lv != rv) {
        const int mid = (lv + rv) / 2;
        if (tree[2 * v + 1] >= x) {
          v = 2 * v + 1;
          lv = mid + 1;
        } else {
          v = 2 * v;
          rv = mid;
        }
      }
      return lv;
    }

    const int mid = (lv + rv) / 2;
    const int val = rightmost_greater(2 * v + 1, mid + 1, rv, l, r, x);
    if (val != -1) return val;
    return rightmost_greater(2 * v, lv, mid, l, r, x);
  }

 public:
  Segtree(const vector<int>& arr) : n(arr.size()) {
    tree.assign(4 * n, 0);
    build(arr, 1, 0, n - 1);
  }

  int rightmost_greater(int i, int x) {
    return rightmost_greater(1, 0, n - 1, i, n - 1, x);
  }
};

class Solution {
  int max_area_aux(const vector<int>& height) {
    const int n = height.size();
    int ans = 0;

    Segtree st(height);

    for (int i = 0; i < n; i++) {
      const int j = st.rightmost_greater(i + 1, height[i]);
      if (j == -1) continue;

      const int w = j - i;
      ans = max(ans, height[i] * w);
    }

    return ans;
  }

 public:
  int maxArea(vector<int>& height) {
    const int a = max_area_aux(height);
    reverse(height.begin(), height.end());
    const int b = max_area_aux(height);
    return max(a, b);
  }
};
