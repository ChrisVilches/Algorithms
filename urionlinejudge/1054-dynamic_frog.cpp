#include <bits/stdc++.h>

using namespace std;
int N, D;

pair<int, char> read_stone() {
  char type;
  int pos;
  while (scanf("%c", &type) && !(type == 'B' || type == 'S'))
    ;
  scanf("%*c%d", &pos);

  return make_pair(pos, type);
}

void solve() {
  cin >> N >> D;

  vector<pair<int, char>> stones{make_pair(0, 'B')};

  for (int i = 0; i < N; i++) stones.push_back(read_stone());

  stones.push_back(make_pair(D, 'B'));

  int ans = 0;
  for (int i = 0; i < (int)stones.size() - 2; i++) {
    auto a = stones[i];
    auto b = stones[i + 1];
    auto c = stones[i + 2];

    if (b.second == 'S') {
      int dist = c.first - a.first;
      ans = max(ans, dist);
    } else {
      int dist1 = c.first - b.first;
      int dist2 = b.first - a.first;
      ans = max({ans, dist1, dist2});
    }
  }
  if (ans == 0) {
    ans = D;
  }

  cout << ans;
}

int main() {
  int T;
  cin >> T;

  for (int i = 0; i < T; i++) {
    printf("Case %d: ", i + 1);
    solve();
    printf("\n");
  }
}
