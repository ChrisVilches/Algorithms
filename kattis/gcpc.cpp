#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tuple<int, int, int> tiii;

int problems[100'001];
int penalty[100'001];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  cin >> N >> M;

  tree<tiii, null_type, less<tiii>, rb_tree_tag, tree_order_statistics_node_update> teams;

  for (int i = 0; i < N; i++) teams.insert({0, 0, -i});

  while (M--) {
    int t, p;
    cin >> t >> p;
    t--;

    teams.erase({problems[t], -penalty[t], -t});

    problems[t]++;
    penalty[t] += p;
    teams.insert({problems[t], -penalty[t], -t});

    const tiii favorite_team = {problems[0], -penalty[0], 0};

    printf("%d\n", N - (int)teams.order_of_key(favorite_team));
  }
}
