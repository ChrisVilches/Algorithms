#include <bits/stdc++.h>

using namespace std;

string line;
stringstream ss;
int N, D;

void solve() {
  getline(cin, line);
  ss = stringstream(line);
  ss >> N >> D;
  getline(cin, line);
  ss = stringstream(line);

  vector<pair<int, char>> stones;
  stones.push_back(make_pair(0, 'B'));

  for (int i = 0; i < N; i++) {
    char type, skip;
    int pos;
    ss >> type >> skip >> pos;
    stones.push_back(make_pair(pos, type));
  }
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
  cout << ans;
}

int main() {
  getline(cin, line);
  ss = stringstream(line);
  int T;
  ss >> T;

  for (int i = 0; i < T; i++) {
    printf("Case %d: ", i + 1);
    solve();
    printf("\n");
  }
}
