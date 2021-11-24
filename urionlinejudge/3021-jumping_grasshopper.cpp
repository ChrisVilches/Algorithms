#include <bits/stdc++.h>

using namespace std;

const int SIZE = 200007;
int heights[SIZE];
int N, M;

struct Segtree {
 private:
  vector<int> tree;
  int n;
  int* A;
  inline int left(int p) { return p << 1; }
  inline int right(int p) { return (p << 1) + 1; }

  void build(int p, int L, int R) {
    if (L == R)
      tree[p] = A[L];
    else {
      build(left(p), L, (L + R) / 2);
      build(right(p), (L + R) / 2 + 1, R);
      tree[p] = max(tree[left(p)], tree[right(p)]);
    }
  }

  int max_query(int p, int L, int R, int i, int j) {
    if (i > R || j < L) return INT_MIN;
    if (L >= i && R <= j) return tree[p];
    return max(max_query(left(p), L, (L + R) / 2, i, j),
               max_query(right(p), (L + R) / 2 + 1, R, i, j));
  }

  void update(int p, int L, int R, int pos, int new_val) {
    if (L == R) {
      tree[p] = new_val;
      A[pos] = new_val;
    } else {
      int m = (L + R) / 2;
      if (pos <= m)
        update(left(p), L, m, pos, new_val);
      else
        update(right(p), m + 1, R, pos, new_val);
      tree[p] = max(tree[left(p)], tree[right(p)]);
    }
  }

  int query_first(int v, int lv, int rv, int l, int r, int x) {
    if (lv > r || rv < l) return -1;
    if (l <= lv && rv <= r) {
      if (tree[v] <= x) return -1;
      while (lv != rv) {
        int mid = (lv + rv) / 2;
        if (tree[left(v)] > x) {
          v = left(v);
          rv = mid;
        } else {
          v = right(v);
          lv = mid + 1;
        }
      }
      return lv;
    }

    int mid = lv + (rv - lv) / 2;
    int rs = query_first(left(v), lv, mid, l, r, x);
    if (rs != -1) return rs;
    return query_first(right(v), mid + 1, rv, l, r, x);
  }

  int query_first_reverse(int v, int lv, int rv, int l, int r, int x) {
    if (lv > r || rv < l) return -1;
    if (l <= lv && rv <= r) {
      if (tree[v] <= x) return -1;
      while (lv != rv) {
        int mid = (lv + rv) / 2;
        if (tree[right(v)] > x) {
          v = right(v);
          lv = mid + 1;
        } else {
          v = left(v);
          rv = mid;
        }
      }
      return lv;
    }

    int mid = lv + (rv - lv) / 2;
    int rs = query_first_reverse(right(v), mid + 1, rv, l, r, x);
    if (rs != -1) return rs;
    return query_first_reverse(left(v), lv, mid, l, r, x);
  }

 public:
  Segtree() {}
  Segtree(int* arr, int _n) : n(_n), A(arr) {
    tree.assign(4 * n, 0);
    build(1, 0, n - 1);
  }

  int query_first(int i, int j, int higher_than) {
    return query_first(1, 0, N - 1, i, j, higher_than);
  }

  int query_first_reverse(int i, int j, int higher_than) {
    return query_first_reverse(1, 0, N - 1, i, j, higher_than);
  }
  int max_query(int i, int j) { return max_query(1, 0, n - 1, i, j); }
  void update(int pos, int val) { return update(1, 0, n - 1, pos, val); }
};

Segtree st;

int query_jump(int from, bool to_right) {
  int first_taller_than_max = -1;

  if (to_right) {
    int left_max = max(st.max_query(0, from), heights[from]);
    first_taller_than_max = st.query_first(from + 1, N - 1, left_max);
  } else {
    int right_max = max(st.max_query(from + 1, N - 1), heights[from]);
    first_taller_than_max = st.query_first_reverse(0, from - 1, right_max);
  }

  if (first_taller_than_max != -1) return first_taller_than_max;
  return query_jump(from + (to_right ? 1 : -1), !to_right);
}

int main() {
  while (scanf("%d %d", &N, &M) == 2) {
    for (int i = 0; i < N; i++) scanf("%d", &heights[i]);

    st = Segtree(heights, N);
    char c;
    int jump_from, plant_idx, new_height;

    while (M--) {
      scanf(" %c", &c);
      if (c == 'L' || c == 'R') {
        scanf("%d", &jump_from);
        printf("%d\n", query_jump(jump_from - 1, c == 'R') + 1);
      } else if (c == 'U') {
        scanf("%d %d", &plant_idx, &new_height);
        st.update(plant_idx - 1, new_height);
      }
    }
  }
}
