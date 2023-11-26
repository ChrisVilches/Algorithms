#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> Graph;

hash<string> hasher;

bool bpm(const Graph& g, const int u, vector<bool>& visited, vector<int>& match) {
  for (const int v : g[u]) {
    if (visited[v]) continue;
    visited[v] = true;

    if (match[v] == -1 || bpm(g, match[v], visited, match)) {
      match[v] = u;
      return true;
    }
  }

  return false;
}

int max_bipartite_matching(const Graph& g, const int match_set_size) {
  vector<int> match(match_set_size, -1);
  vector<bool> visited(match_set_size);
  int result = 0;
  for (int u = 0; u < (int)g.size(); u++) {
    fill(visited.begin(), visited.end(), false);
    result += bpm(g, u, visited, match);
  }
  return result;
}

vector<size_t> extract_subset(const vector<size_t>& all, const int subset) {
  vector<size_t> res;
  for (int i = 0; i < (int)all.size(); i++)
    if (subset & (1 << i)) res.push_back(all[i]);
  return res;
}

vector<size_t> read_algorithms() {
  int A;
  cin >> A;
  set<size_t> algo;
  while (A--) {
    string a;
    cin >> a;
    algo.emplace(hasher(a));
  }
  return vector<size_t>{algo.begin(), algo.end()};
}

int main() {
  int N;

  while (cin >> N) {
    map<vector<size_t>, int> node_idx;
    Graph g;

    const auto get_node_idx = [&](const vector<size_t>& algo_idx_list) -> int {
      if (!node_idx.count(algo_idx_list)) {
        node_idx[algo_idx_list] = node_idx.size();
        g.resize(g.size() + 1);
      }
      return node_idx[algo_idx_list];
    };

    for (int t = 0; t < N; t++) {
      const vector<size_t> can_teach = read_algorithms();

      for (int subset = 1; subset < (1 << can_teach.size()); subset++) {
        const vector<size_t> algo_subset = extract_subset(can_teach, subset);

        const int v = get_node_idx(algo_subset);

        for (int i = 0; i < (int)algo_subset.size(); i++) {
          const vector<size_t> remove_one = extract_subset(algo_subset, ~(1 << i));
          const int u = get_node_idx(remove_one);

          g[u].push_back(v);
        }
      }
    }

    cout << node_idx.size() - max_bipartite_matching(g, node_idx.size()) << endl;
  }
}
