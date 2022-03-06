#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

#define V 1000
int g[V][V], rgraph[V][V];
bool visited[V];
array<int, 50001> available;
int N, M;
const int S = 0;
const int T = 1;

struct Monkey {
  int v, a, b, node_idx;
};

struct Time {
  Time(int t) : start(t) {}
  int start, end = -1, node_idx = -1;
  int amount() const { return end - start; }
};

vector<Monkey> monkeys;
map<int, Time> times;
vector<vector<int>> edges;

bool bfs(int rgraph[][V], int s, int t, array<int, V>& parent) {
  memset(visited, 0, sizeof(visited));
  queue<int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v : edges[u]) {
      if (!visited[v] && rgraph[u][v] > 0) {
        if (v == t) {
          parent[v] = u;
          return true;
        }
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  return false;
}

int ford_fulkerson(int (&g)[V][V], int rgraph[][V], int s, int t) {
  int u, v;
  array<int, V> parent;
  int max_flow = 0;

  memcpy(rgraph, g, sizeof g);

  while (bfs(rgraph, s, t, parent)) {
    int path_flow = INT_MAX;
    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      path_flow = min(path_flow, rgraph[u][v]);
    }

    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      rgraph[u][v] -= path_flow;
      rgraph[v][u] += path_flow;
    }

    max_flow += path_flow;
  }

  return max_flow;
}

void add_edge(int u, int v, int c) {
  edges.at(u).push_back(v);
  edges.at(v).push_back(u);
  g[u][v] = c;
}

void build_graph() {
  times.clear();

  memset(g, 0, sizeof g);

  edges.assign(2, vector<int>());

  for (const Monkey& m : monkeys) {
    times.emplace(m.a, m.a);
    times.emplace(m.b, m.b);
  }

  for (auto it = times.begin(); it != times.end(); it++) {
    if (next(it) == times.end()) break;

    Time& curr_time = it->second;
    Time next_time = next(it)->second;
    curr_time.end = next_time.start;
  }

  times.erase(prev(times.end()));

  for (auto& [_, time] : times) {
    edges.push_back(vector<int>());
    time.node_idx = edges.size() - 1;
  }

  for (Monkey& m : monkeys) {
    edges.push_back(vector<int>());
    const int monkey_node_idx = edges.size() - 1;

    for (int t = m.a; t < m.b;) {
      const Time& time = times.at(t);
      add_edge(monkey_node_idx, time.node_idx, time.amount());
      t = time.end;
    }

    add_edge(S, monkey_node_idx, m.v);
    m.node_idx = monkey_node_idx;
  }

  for (const auto [_, time] : times) {
    add_edge(time.node_idx, T, M * time.amount());
  }
}

vector<pii> group_numbers(vector<int>& nums) {
  sort(nums.begin(), nums.end());

  vector<pii> res;

  for (int n : nums)
    if (!res.empty() && res.back().second + 1 == n)
      res.back().second = n;
    else
      res.push_back({n, n});

  return res;
}

int edge_flow(int u, int v) { return g[u][v] - rgraph[u][v]; }

vector<vector<pii>> get_allocation() {
  fill(available.begin(), available.end(), M);

  map<int, vector<int>> solutions;

  for (const auto& [_, time] : times) {
    set<pii, less<pii>> monkeys_to_allocate;

    for (const Monkey& monkey : monkeys) {
      int flow = edge_flow(monkey.node_idx, time.node_idx);

      if (flow > 0) monkeys_to_allocate.emplace(flow, monkey.node_idx);
    }

    int t = time.start;

    for (const auto& [flow, monkey_idx] : monkeys_to_allocate) {
      for (int f = 0; f < flow; t++) {
        if (t == time.end) t = time.start;
        if (available[t] == 0) continue;

        solutions[monkey_idx].push_back(t);
        available[t]--;
        f++;
      }
    }
  }

  vector<vector<pii>> res;

  for (auto& [_, solution] : solutions) res.push_back(group_numbers(solution));

  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int test_case = 1;

  while (cin >> N >> M && N) {
    int total_required = 0;

    monkeys.clear();

    for (int i = 0; i < N; i++) {
      Monkey m;
      cin >> m.v >> m.a >> m.b;
      monkeys.push_back(m);
      total_required += m.v;
    }

    build_graph();

    const int flow = ford_fulkerson(g, rgraph, S, T);

    cout << "Case " << (test_case++) << ": " << (flow == total_required ? "Yes" : "No")
         << endl;

    if (flow == total_required) {
      auto allocation = get_allocation();

      for (auto& alloc : allocation) {
        cout << alloc.size();

        for (const auto& [a, b] : alloc) {
          cout << " (" << a << "," << b + 1 << ")";
        }

        cout << endl;
      }
    }
  }
}
