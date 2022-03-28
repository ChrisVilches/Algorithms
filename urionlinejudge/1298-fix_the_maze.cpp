#include <bits/stdc++.h>
using namespace std;

#define MAX 301

enum { DOWN = 1, UP = 2, RIGHT = 4, LEFT = 8 };

int N;
const int di[] = {-1, 1, 0, 0};
const int dj[] = {0, 0, -1, 1};
short dir[3 * MAX][3 * MAX];

struct DisjointSets {
  DisjointSets(int n) : parent(n), rank(n, 0) { iota(parent.begin(), parent.end(), 0); }

  int find(int u) {
    if (u != parent[u]) parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y) {
    x = find(x), y = find(y);
    if (rank[x] > rank[y])
      parent[y] = x;
    else
      parent[x] = y;

    if (rank[x] == rank[y]) rank[y]++;
  }

 private:
  vector<int> parent, rank;
};

void solve() {
  memset(dir, 0, sizeof dir);

  for (int i = 0; i < 2 * N - 1; i++) {
    for (int j = 0; j < N; j++) {
      char barrier;
      cin >> barrier;

      int offset = i % 2 == 1;

      if (barrier == 'H') {
        dir[i][2 * j + offset] |= DOWN;
        dir[i][2 * j + 1 + offset] |= DOWN;
        dir[i + 1][2 * j + offset] |= UP;
        dir[i + 1][2 * j + 1 + offset] |= UP;
      } else {
        dir[i][2 * j + offset] |= RIGHT;
        dir[i][2 * j + 1 + offset] |= LEFT;
        dir[i + 1][2 * j + offset] |= RIGHT;
        dir[i + 1][2 * j + 1 + offset] |= LEFT;
      }
    }
  }

  const int total_rows = 2 * N;
  const int total_cols = 2 * N + 1;

  DisjointSets ds(total_rows * total_cols);

  for (int i = 0; i < 2 * N; i++) {
    for (int j = 0; j < 2 * N + 1; j++) {
      for (int d = 0; d < 4; d++) {
        const int i2 = i + di[d];
        const int j2 = j + dj[d];

        if (i2 < 0 || j2 < 0 || i2 >= 2 * N || j2 >= 2 * N + 1) continue;

        if (i < i2 && (dir[i][j] & DOWN) > 0) continue;
        if (i > i2 && (dir[i][j] & UP) > 0) continue;
        if (j < j2 && (dir[i][j] & RIGHT) > 0) continue;
        if (j > j2 && (dir[i][j] & LEFT) > 0) continue;

        const int element1 = total_cols * i + j;
        const int element2 = total_cols * i2 + j2;

        ds.merge(element1, element2);
      }
    }
  }

  set<int> components;

  for (int i = 0; i < total_rows * total_cols; i++) {
    components.insert(ds.find(i));
  }

  cout << components.size() - 1 << endl;
}

int main() {
  while (cin >> N) solve();
}
