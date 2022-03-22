#include <bits/stdc++.h>
using namespace std;

template <class T, class TFunc>
struct Segtree {
  Segtree(T* arr, int _n) : n(_n), A(arr) {
    tree.assign(4 * n, 0);
    build(1, 0, n - 1);
  }
  T query(int i, int j) { return query(1, 0, n - 1, i, j); }
  void update(int pos, T val) { return update(1, 0, n - 1, pos, val); }

 private:
  vector<T> tree;
  int n;
  TFunc fn;
  T* A;
  inline int left(int p) { return p << 1; }
  inline int right(int p) { return (p << 1) + 1; }

  void build(int p, int L, int R) {
    if (L == R)
      tree[p] = A[L];
    else {
      build(left(p), L, (L + R) / 2);
      build(right(p), (L + R) / 2 + 1, R);
      tree[p] = fn(tree[left(p)], tree[right(p)]);
    }
  }

  T query(int p, int L, int R, int i, int j) {
    if (i > R || j < L) return fn.neutral_value;
    if (L >= i && R <= j) return tree[p];
    return fn(query(left(p), L, (L + R) / 2, i, j),
              query(right(p), (L + R) / 2 + 1, R, i, j));
  }

  void update(int p, int L, int R, int pos, T new_val) {
    if (L == R) {
      tree[p] = new_val;
      A[pos] = new_val;
    } else {
      int m = (L + R) / 2;
      if (pos <= m)
        update(left(p), L, m, pos, new_val);
      else
        update(right(p), m + 1, R, pos, new_val);
      tree[p] = fn(tree[left(p)], tree[right(p)]);
    }
  }
};

int nums[100001];

char symbol(const int n) {
  if (n > 0) return '+';
  if (n == 0) return '0';
  return '-';
}

struct mult {
  const int neutral_value = 1;
  int sgn(const int n) const {
    if (n < 0) return -1;
    return n > 0;
  }

  int operator()(const int a, const int b) const { return sgn(a) * sgn(b); }
};

int main() {
  int N, K;

  while (cin >> N >> K) {
    for (int i = 0; i < N; i++) cin >> nums[i];

    Segtree<int, mult> st(nums, N);

    while (K--) {
      char type;
      int A, B;

      cin >> type >> A >> B;

      if (type == 'C')
        st.update(A - 1, B);
      else
        cout << symbol(st.query(A - 1, B - 1));
    }

    cout << endl;
  }
}
