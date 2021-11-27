#include <bits/stdc++.h>

using namespace std;

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
      tree[p] = min(tree[left(p)], tree[right(p)]);
    }
  }

  int min_query(int p, int L, int R, int i, int j) {
    if (i > R || j < L) return INT_MAX;
    if (L >= i && R <= j) return tree[p];
    return min(min_query(left(p), L, (L + R) / 2, i, j),
               min_query(right(p), (L + R) / 2 + 1, R, i, j));
  }

 public:
  Segtree() {}
  Segtree(int* arr, int _n) : n(_n), A(arr) {
    tree.assign(4 * n, 0);
    build(1, 0, n - 1);
  }
  int min_query(int i, int j) { return min_query(1, 0, n - 1, i, j); }
};

int nums[100'000];

int main() {
  int N, Q;
  cin >> N;

  for (int i = 0; i < N; i++) cin >> nums[i];

  cin >> Q;

  Segtree st(nums, N);

  while (Q--) {
    int i, j;
    cin >> i >> j;
    cout << st.min_query(i, j) << endl;
  }
}
