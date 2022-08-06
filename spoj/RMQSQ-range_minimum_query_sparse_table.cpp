#include <bits/stdc++.h>
using namespace std;

int st[100000][18];

int min_query(const int L, const int R) {
  const int k = 31 - __builtin_clz(R - L + 1);
  return min(st[L][k], st[R - (1 << k) + 1][k]);
}

int main() {
  int N, Q;
  cin >> N;

  for (int i = 0; i < N; i++) cin >> st[i][0];

  const int size = ceil(log2(N));

  for (int k = 1; k < size; k++)
    for (int i = 0; i + (1 << k) <= N; i++)
      st[i][k] = min(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);

  cin >> Q;

  while (Q--) {
    int l, r;
    cin >> l >> r;

    cout << min_query(l, r) << '\n';
  }
}
