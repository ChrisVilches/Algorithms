#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

const int SIZE = 200000;
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
        int mid = lv + (rv - lv) / 2;
        if (tree[2 * v] > x) {
          v = 2 * v;
          rv = mid;
        } else {
          v = 2 * v + 1;
          lv = mid + 1;
        }
      }
      return lv;
    }

    int mid = lv + (rv - lv) / 2;
    int rs = query_first(2 * v, lv, mid, l, r, x);
    if (rs != -1) return rs;
    return query_first(2 * v + 1, mid + 1, rv, l, r, x);
  }

  int query_first_reverse(int v, int lv, int rv, int l, int r, int x) {
    if (lv > r || rv < l) return -1;
    if (l <= lv && rv <= r) {
      if (tree[v] <= x) return -1;
      while (lv != rv) {
        int mid = lv + (rv - lv) / 2;
        if (tree[2 * v + 1] < x) {
          v = 2 * v;
          rv = mid;
        } else {
          v = 2 * v + 1;
          lv = mid + 1;
        }
      }
      return lv;
    }

    int mid = lv + (rv - lv) / 2;
    int rs = query_first_reverse(2 * v + 1, mid + 1, rv, l, r, x);
    if (rs != -1) return rs;
    return query_first_reverse(2 * v, lv, mid, l, r, x);
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
  int next_tallest_idx = from;

  if (to_right) {
    int tallest = max(st.max_query(0, from), heights[from]);

    int next_taller_than_tallest_idx = st.query_first(from + 1, N - 1, tallest);

    if (next_taller_than_tallest_idx != -1) return next_taller_than_tallest_idx;

    // O(N)
    for (int i = from + 1; i < N; i++)
      if (heights[i] > heights[from]) {
        next_tallest_idx = i;
        break;
      }
  } else {
    int tallest = max(st.max_query(from + 1, N - 1), heights[from]);

    int next_taller_than_tallest_idx =
        st.query_first_reverse(0, from - 1, tallest);

    if (next_taller_than_tallest_idx != -1) return next_taller_than_tallest_idx;

    // O(N)
    for (int i = from - 1; i >= 0; i--)
      if (heights[i] > heights[from]) {
        next_tallest_idx = i;
        break;
      }
  }

  if (next_tallest_idx == from) return from;
  return query_jump(from, !to_right);
}

int main() {
  while (scanf("%d %d", &N, &M) == 2) {
    for (int i = 0; i < N; i++) scanf("%d", &heights[i]);

    st = Segtree(heights, N);

    while (M--) {
      char c;
      int jump_from;
      scanf(" %c ", &c);
      if (c == 'L' || c == 'R') {
        scanf("%d", &jump_from);
        jump_from--;
        printf("%d\n", query_jump(jump_from, c == 'R') + 1);
      } else if (c == 'U') {
        int plant, new_height;
        scanf("%d %d", &plant, &new_height);
        plant--;
        st.update(plant, new_height);
      }
    }
  }
}
