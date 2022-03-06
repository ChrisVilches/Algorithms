#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

// Use dynamic memory for the Ford Fulkerson Algorithm because checking whether the V
// value is correct is cancer.

#define V 1000
int g[V][V], rgraph[V][V];
bool visited[V];
array<int, 50001> available;
int N, M, total_required;
const int S = 0;
const int T = 1;

// TODO: Use less maps and stuff (organize data in a more compact way)
map<int, int> times;
map<int, int> time_inverse;
vector<int> monkey_node_idx_list;
set<int> all_times;
map<int, tuple<int, int, int>> monkey_tuples;

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

pii get_time_range(int t) {
  auto t_it = all_times.find(t);
  return {*t_it, *next(t_it)};
}

void add_edge(int u, int v, int c) {
  edges.at(u).push_back(v);
  edges.at(v).push_back(u);
  g[u][v] = c;
}

int get_time_node(const int t) {
  auto it = all_times.lower_bound(t);

  if (*it > t) it--;

  int sanitized_t = *it;

  // TODO: Rename "sanitized"
  if (times.count(sanitized_t)) return times[sanitized_t];

  edges.push_back(vector<int>());
  const int idx = edges.size() - 1;
  times[sanitized_t] = idx;
  time_inverse[idx] = sanitized_t;

  return idx;
}

void build_graph() {
  times.clear();
  time_inverse.clear();
  monkey_node_idx_list.clear();
  all_times.clear();

  memset(g, 0, sizeof g);
  total_required = 0;

  edges.assign(2, vector<int>());

  vector<tuple<int, int, int>> monkeys;

  for (int i = 0; i < N; i++) {
    int v, a, b;
    cin >> v >> a >> b;
    monkeys.push_back({v, a, b});
  }

  for (tuple<int, int, int> m : monkeys) {
    all_times.emplace(get<1>(m));
    all_times.emplace(get<2>(m));
  }

  for (int i = 0; i < N; i++) {
    auto [v, a, b] = monkeys[i];

    edges.push_back(vector<int>());
    const int monkey_node_idx = edges.size() - 1;
    monkey_tuples[monkey_node_idx] = monkeys[i];

    for (int t = a; t < b;) {
      int time_node_idx = get_time_node(t);
      auto [from, to] = get_time_range(time_inverse[time_node_idx]);
      add_edge(monkey_node_idx, time_node_idx, to - from);
      t = to;
    }

    add_edge(S, monkey_node_idx, v);
    monkey_node_idx_list.push_back(monkey_node_idx);
    total_required += v;
  }

  for (auto it = times.begin(); it != times.end(); it++) {
    auto [time_value, time_node_idx] = *it;
    auto [from, to] = get_time_range(time_value);
    add_edge(time_node_idx, T, M * (to - from));
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

void print_allocation() {
  fill(available.begin(), available.end(), M);

  map<int, vector<int>> solutions;

  for (const auto [time_value, time_node_idx] : times) {
    set<pii, less<pii>> monkeys_to_allocate;

    for (const int monkey_idx : monkey_node_idx_list) {
      int flow = g[monkey_idx][time_node_idx] - rgraph[monkey_idx][time_node_idx];

      if (flow > 0) monkeys_to_allocate.insert({flow, monkey_idx});
    }

    const int end = *next(all_times.find(time_value));

    int t = time_value;

    for (const auto& [flow, monkey_idx] : monkeys_to_allocate) {
      for (int f = 0; f < flow; t++) {
        if (t == end) t = time_value;
        if (available[t] == 0) continue;

        solutions[monkey_idx].push_back(t);
        available.at(t)--;
        f++;
      }
    }
  }

  for (auto& [_, solution] : solutions) {
    vector<pii> pairs = group_numbers(solution);

    cout << pairs.size();

    for (const auto& [a, b] : pairs) {
      cout << " (" << a << "," << b + 1 << ")";
    }

    cout << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int test_case = 1;

  while (cin >> N >> M && N) {
    build_graph();

    const int flow = ford_fulkerson(g, rgraph, S, T);

    cout << "Case " << (test_case++) << ": " << (flow == total_required ? "Yes" : "No")
         << endl;

    if (flow == total_required) print_allocation();
  }
}
