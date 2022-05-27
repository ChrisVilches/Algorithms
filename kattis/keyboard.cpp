#include <bits/stdc++.h>
using namespace std;

int R, C;
char keyboard[51][51];
bool visited[51][51][10'001];

int di[]{-1, 1, 0, 0};
int dj[]{0, 0, -1, 1};

char text[10'005];
int text_size;

int bfs() {
  queue<tuple<int, int, int, int>> q;

  q.push({0, 0, 0, 0});
  visited[0][0][0] = true;

  while (!q.empty()) {
    const auto [r, c, key_idx, dist] = q.front();
    q.pop();

    if (key_idx == text_size) return dist;

    if (keyboard[r][c] == text[key_idx]) {
      visited[r][c][key_idx] = true;
      q.push({r, c, key_idx + 1, dist + 1});
      continue;
    }

    for (int d = 0; d < 4; d++) {
      int r2 = r;
      int c2 = c;

      while (keyboard[r][c] == keyboard[r2][c2]) {
        r2 += di[d];
        c2 += dj[d];
        if (r2 < 0 || c2 < 0) break;
        if (r2 >= R || c2 >= C) break;
      }

      if (r2 < 0 || c2 < 0) continue;
      if (r2 >= R || c2 >= C) continue;
      if (visited[r2][c2][key_idx]) continue;

      visited[r2][c2][key_idx] = true;

      q.push({r2, c2, key_idx, dist + 1});
    }
  }

  assert(false);
}

int main() {
  scanf("%d%d", &R, &C);
  for (int i = 0; i < R; i++) scanf("%s", keyboard[i]);

  scanf("%s", text);
  text_size = strlen(text);
  text[text_size++] = '*';

  cout << bfs() << endl;
}
