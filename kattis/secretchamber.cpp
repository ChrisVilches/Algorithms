#include <bits/stdc++.h>
using namespace std;

int N, M;
map<char, vector<char>> graph;

bool path_exists(const char a, const char b) {
  unordered_set<char> visited;

  function<bool(int)> dfs = [&](const char u) {
    if (u == b) return true;
    visited.insert(u);

    for (const char v : graph[u]) {
      if (visited.count(v)) continue;
      if (dfs(v)) return true;
    }
    return false;
  };

  return dfs(a);
}

bool possible(const string& q1, const string& q2) {
  if (q1.size() != q2.size()) return false;

  for (int c = 0; c < (int)q1.size(); c++) {
    if (!path_exists(q1[c], q2[c])) return false;
  }

  return true;
}

void solve() {
  graph.clear();

  for (int i = 0; i < M; i++) {
    char a, b;
    cin >> a >> b;

    graph[a].push_back(b);
  }

  for (int i = 0; i < N; i++) {
    string q1, q2;
    cin >> q1 >> q2;

    if (possible(q1, q2)) {
      cout << "yes" << endl;
    } else {
      cout << "no" << endl;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> M >> N) solve();
}
