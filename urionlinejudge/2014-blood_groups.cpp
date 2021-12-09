#include <bits/stdc++.h>

using namespace std;
typedef vector<vector<int>> graph;

int N, Q;
bool visited[200];
int match[200];

bool bpm(graph& g, int u) {
  for (int v : g[u])
    if (!visited[v]) {
      visited[v] = true;
      if (match[v] < 0 || bpm(g, match[v])) {
        match[v] = u;
        return true;
      }
    }
  return false;
}

int max_bipartite_matching(graph& g) {
  memset(match, -1, sizeof match);
  int result = 0;
  for (int u = 0; u < (int)g.size(); u++) {
    memset(visited, 0, sizeof visited);
    result += bpm(g, u);
  }
  return result;
}

bool lists_intersect(vector<int>& list, vector<int>& sorted_list) {
  for (int item : list)
    if (binary_search(sorted_list.begin(), sorted_list.end(), item))
      return true;
  return false;
}

bool possible(vector<vector<int>> parents, vector<int>& offspring) {
  graph g(N);

  map<int, vector<int>> antigen_index;

  for (int i = 0; i < (int)offspring.size(); i++)
    antigen_index[offspring[i]].push_back(i);

  for (int i = (int)offspring.size(); i < N; i++) antigen_index[0].push_back(i);

  for (int i = 0; i < N; i++)
    if (lists_intersect(parents[i], offspring) || (int)parents[i].size() < N)
      parents[i].push_back(0);

  for (int i = 0; i < N; i++)
    for (int j : parents[i])
      g[i].insert(g[i].end(), antigen_index[j].begin(), antigen_index[j].end());

  return max_bipartite_matching(g) == N;
}

void solve() {
  int B, c;
  vector<vector<int>> parents(N);

  for (int i = 0; i < N; i++) {
    scanf("%d", &B);
    while (B--) {
      scanf("%d", &c);
      parents[i].push_back(c);
    }
  }

  while (Q--) {
    scanf("%d", &B);
    vector<int> offspring;
    while (B--) {
      scanf("%d", &c);
      offspring.push_back(c);
    }
    sort(offspring.begin(), offspring.end());
    printf("%c\n", possible(parents, offspring) ? 'Y' : 'N');
  }
}

int main() {
  while (scanf("%d %d", &N, &Q) == 2) solve();
}
