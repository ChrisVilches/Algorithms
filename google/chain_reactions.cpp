#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define MAX 100007

int N;
ll fun[MAX], max_value[MAX];
bool connected[MAX];
vector<vector<int>> parents;

ll dfs(const int u) {
  if (!connected[u]) return 0;
  connected[u] = false;
  if (parents[u].empty()) return fun[u];

  int min_v = parents[u].front();

  for (const int v : parents[u]) {
    if (max_value[v] < max_value[min_v]) min_v = v;
  }

  return max(fun[u], dfs(min_v));
}

void populate_max_value(const int u) {
  connected[u] = true;

  if (parents[u].empty()) return;

  ll min_value = INT_MAX;

  for (const int v : parents[u]) {
    populate_max_value(v);

    min_value = min(min_value, max_value[v]);
  }

  max_value[u] = max(max_value[u], min_value);
}

void solve() {
  cin >> N;

  parents.assign(N + 1, vector<int>());
  memset(max_value, 0, sizeof max_value);
  memset(connected, 0, sizeof connected);

  for (int i = 0; i < N; i++) {
    cin >> fun[i];
    max_value[i] = fun[i];
  }

  for (int i = 0; i < N; i++) {
    int child;
    cin >> child;
    child--;

    parents[~child ? child : N].push_back(i);
  }

  populate_max_value(N);

  ll ans = 0;

  for (int i = 0; i < N; i++) {
    ans += dfs(i);
  }

  cout << ans << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;

  for (int i = 1; i <= T; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
}
