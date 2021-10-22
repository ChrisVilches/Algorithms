#include <bits/stdc++.h>

using namespace std;

int memo[1001][1001];
int C, P;

struct Node {
  vector<int> parents;
};

Node cities[1001];

bool disjoint(int i, int j) {
  if (i > j) swap(i, j);
  if (i == 0) return true;
  if (memo[i][j] != -1) return memo[i][j];

  if (cities[j].parents.size() == 1 && cities[j].parents[0] == i)
    return (memo[i][j] = false);

  for (int j_parent : cities[j].parents)
    if (disjoint(i, j_parent)) return (memo[i][j] = true);

  return (memo[i][j] = false);
}

void solve() {
  memset(memo, -1, sizeof memo);
  for (int i = 0; i < C; i++) {
    cities[i].parents.clear();
  }

  for (int i = 0; i < P; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    cities[v].parents.push_back(u);
  }

  int total = 0;
  for (int i = 0; i < C; i++) {
    for (int j = i + 1; j < C; j++) {
      if (disjoint(i, j)) total++;
    }
  }
  cout << total << endl;
}

int main() {
  while (scanf("%d %d", &C, &P) == 2) solve();
}
