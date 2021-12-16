#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX_N 100'001

ll A[MAX_N];
ll tree[4 * MAX_N];

ll query(int p, int L, int R, int i, int j) {
  if (i > R || j < L) return 0;
  if (i <= L && R <= j) return tree[p];

  int m = (L + R) / 2;
  return query(2 * p, L, m, i, j) | query(2 * p + 1, m + 1, R, i, j);
}

void update(int p, int L, int R, int pos, ll new_val) {
  if (L == R) {
    tree[p] = new_val;
  } else {
    int m = (L + R) / 2;
    if (pos <= m)
      update(2 * p, L, m, pos, new_val);
    else
      update(2 * p + 1, m + 1, R, pos, new_val);

    tree[p] = tree[2 * p] | tree[2 * p + 1];
  }
}

void build_tree(int p, int L, int R) {
  if (L == R)
    tree[p] = A[L];
  else {
    build_tree(2 * p, L, (L + R) / 2);
    build_tree(2 * p + 1, (L + R) / 2 + 1, R);
    tree[p] = tree[2 * p] | tree[2 * p + 1];
  }
}

int main() {
  int N, Q, M;
  scanf("%d %d %d", &N, &Q, &M);

  for (int i = 0; i < N; i++) {
    int x;
    scanf("%d", &x);
    A[i] = 1LL << x;
  }

  build_tree(1, 0, N - 1);

  while (Q--) {
    int query_type, a, b;
    scanf("%d %d %d", &query_type, &a, &b);

    if (query_type == 1) {
      cout << __builtin_popcountll(query(1, 0, N - 1, a - 1, b - 1)) << endl;
    } else {
      update(1, 0, N - 1, a - 1, 1LL << b);
    }
  }
}
