#include <bits/stdc++.h>
using namespace std;

struct Segtree {
  int sum_query(int p, int L, int R, int i, int j) {
    if (i > R || j < L) return 0;
    if (L >= i && R <= j) return tree[p];
    return sum_query(left(p), L, (L + R) / 2, i, j) +
           sum_query(right(p), (L + R) / 2 + 1, R, i, j);
  }

  void flip(int p, int L, int R, int pos) {
    if (L == R) {
      tree[p] = A[pos] = !tree[p];
    } else {
      int m = (L + R) / 2;
      if (pos <= m)
        flip(left(p), L, m, pos);
      else
        flip(right(p), m + 1, R, pos);
      tree[p] = tree[left(p)] + tree[right(p)];
    }
  }

  Segtree(short* arr, int _n) : n(_n), A(arr) { tree.assign(4 * n, 0); }

 private:
  vector<int> tree;
  int n;
  short* A;
  inline int left(int p) { return p << 1; }
  inline int right(int p) { return (p << 1) + 1; }
};

short bits[1'000'001];

int N, Q;

int main() {
  cin >> N >> Q;

  Segtree st(bits, N);

  while (Q--) {
    char query_type;
    int i, j;
    scanf(" %c", &query_type);

    if (query_type == 'F') {
      scanf("%d", &i);
      st.flip(1, 0, N - 1, i - 1);
    } else {
      scanf("%d %d", &i, &j);
      printf("%d\n", st.sum_query(1, 0, N - 1, i - 1, j - 1));
    }
  }
}
