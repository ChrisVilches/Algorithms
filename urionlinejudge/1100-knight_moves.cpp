#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

int di[] = {-2, -2, 2, 2, 1, -1, 1, -1};
int dj[] = {1, -1, 1, -1, -2, -2, 2, 2};

int bfs_distance(pii from, pii to) {
  queue<tiii> q;

  bool visited[8][8];
  memset(visited, 0, sizeof visited);

  q.push(make_tuple(from.first, from.second, 0));

  while (!q.empty()) {
    auto [i, j, dist] = q.front();
    q.pop();

    visited[i][j] = true;

    if (i == to.first && j == to.second) return dist;

    for (int d = 0; d < 8; d++) {
      int i2 = i + di[d];
      int j2 = j + dj[d];

      if (i2 >= 0 && j2 >= 0 && i2 < 8 && j2 < 8 && !visited[i2][j2])
        q.push(make_tuple(i2, j2, dist + 1));
    }
  }
  return -1;
}

int main() {
  string line;
  while (getline(cin, line)) {
    pii from = make_pair(line[0] - 'a', line[1] - '1');
    pii to = make_pair(line[3] - 'a', line[4] - '1');

    cout << "To get from " << line.substr(0, 2) << " to" << line.substr(2, 3)
         << " takes " << bfs_distance(from, to) << " knight moves." << endl;
  }
}
