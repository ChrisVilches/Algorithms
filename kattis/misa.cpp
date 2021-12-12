#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<pii, pii> handshake;

char grid[55][55];
int R, S;
int di[] = {1, -1, 0, 0, 1, -1, -1, 1};
int dj[] = {0, 0, 1, -1, 1, -1, 1, -1};

void add_handshake(set<handshake>& container, handshake handshake) {
  if (handshake.first > handshake.second)
    swap(handshake.first, handshake.second);

  container.insert(handshake);
}

set<handshake> initial_handshakes() {
  set<handshake> handshakes;

  for (int i = 0; i < R; i++)
    for (int j = 0; j < S; j++) {
      if (grid[i][j] != 'o') continue;
      for (int d = 0; d < 8; d++) {
        int i2 = i + di[d];
        int j2 = j + dj[d];

        if (i2 < 0 || j2 < 0 || i2 >= R || j2 >= S) continue;
        if (grid[i2][j2] == 'o') {
          add_handshake(handshakes, {{i, j}, {i2, j2}});
        }
      }
    }

  return handshakes;
}

int handshakes_with_mirko(int mirko_i, int mirko_j, set<handshake> handshakes) {
  for (int d = 0; d < 8; d++) {
    int i2 = mirko_i + di[d];
    int j2 = mirko_j + dj[d];

    if (i2 < 0 || j2 < 0 || i2 >= R || j2 >= S) continue;
    if (grid[i2][j2] == 'o')
      add_handshake(handshakes, {{mirko_i, mirko_j}, {i2, j2}});
  }

  return handshakes.size();
}

int main() {
  string line;
  getline(cin, line);
  stringstream ss(line);
  ss >> R >> S;

  for (int i = 0; i < R; i++) {
    getline(cin, line);
    for (int j = 0; j < S; j++) grid[i][j] = line[j];
  }

  set<handshake> handshakes = initial_handshakes();
  int ans = handshakes.size();

  for (int i = 0; i < R; i++)
    for (int j = 0; j < S; j++)
      if (grid[i][j] != 'o')
        ans = max(ans, handshakes_with_mirko(i, j, handshakes));

  cout << ans << endl;
}
