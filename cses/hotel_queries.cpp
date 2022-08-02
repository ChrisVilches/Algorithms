#include <bits/stdc++.h>
using namespace std;

#define MAX_N 200007

struct Segtree {
 private:
  int n;
  int* A;
  vector<int> tree;

  void build(int p, int L, int R) {
    if (L == R)
      tree[p] = A[L];
    else {
      build(2 * p, L, (L + R) / 2);
      build(2 * p + 1, (L + R) / 2 + 1, R);
      tree[p] = max(tree[2 * p], tree[2 * p + 1]);
    }
  }

  void update(int p, int L, int R, int pos, int new_val) {
    if (L == R) {
      tree[p] = new_val;
      A[pos] = new_val;
    } else {
      int m = (L + R) / 2;
      if (pos <= m)
        update(2 * p, L, m, pos, new_val);
      else
        update(2 * p + 1, m + 1, R, pos, new_val);
      tree[p] = max(tree[2 * p], tree[2 * p + 1]);
    }
  }

 public:
  Segtree(int* arr, int n) : n(n), A(arr), tree(4 * n, 0) { build(1, 0, n - 1); }

  void update(int pos, int val) { return update(1, 0, n - 1, pos, val); }

  int first_greater(int val) {
    int p = 1;
    int l = 0, r = n - 1;

    while (l != r && tree[p] >= val) {
      const int m = (l + r) / 2;
      if (tree[2 * p] >= val)
        r = m, p = 2 * p;
      else
        l = m + 1, p = 2 * p + 1;
    }

    return tree[p] >= val ? l : -1;
  }
};

int free_rooms[MAX_N];
int required[MAX_N];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  cin >> N >> M;

  for (int i = 0; i < N; i++) cin >> free_rooms[i];
  for (int i = 0; i < M; i++) cin >> required[i];

  Segtree segtree(free_rooms, N);

  for (int i = 0; i < M; i++) {
    const int idx = segtree.first_greater(required[i]);

    cout << idx + 1 << ' ';

    if (idx == -1) continue;

    segtree.update(idx, free_rooms[idx] - required[i]);
  }

  cout << '\n';
}
