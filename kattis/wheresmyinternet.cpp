#include <bits/stdc++.h>
using namespace std;

struct DisjointSets {
  vector<int> parent, rnk;

  DisjointSets(int n) {
    for (int i = 0; i <= n; i++) {
      rnk.push_back(0);
      parent.push_back(i);
    }
  }

  int find(int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y) {
    x = find(x), y = find(y);
    if (rnk[x] > rnk[y])
      parent[y] = x;
    else
      parent[x] = y;

    if (rnk[x] == rnk[y]) rnk[y]++;
  }
};

int N, M;

void solve() {
  DisjointSets ds(N);

  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    ds.merge(a - 1, b - 1);
  }

  bool connected = true;

  for (int i = 0; i < N; i++)
    if (ds.find(i) != ds.find(0)) {
      connected = false;
      cout << i + 1 << endl;
    }

  if (connected) cout << "Connected" << endl;
}

int main() {
  while (scanf("%d %d", &N, &M) == 2) solve();
}
