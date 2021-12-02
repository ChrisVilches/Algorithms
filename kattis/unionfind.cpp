#include <bits/stdc++.h>

using namespace std;

struct DisjointSets {
  DisjointSets(int n) {
    rnk.assign(n, 0);
    for (int i = 0; i <= n; i++) parent.push_back(i);
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

 private:
  vector<int> parent, rnk;
};

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  DisjointSets ds(N);

  while (Q--) {
    char q;
    int a, b;
    scanf(" %c %d %d", &q, &a, &b);

    if (q == '?')
      printf("%s\n", ds.find(a) == ds.find(b) ? "yes" : "no");
    else
      ds.merge(a, b);
  }
}
