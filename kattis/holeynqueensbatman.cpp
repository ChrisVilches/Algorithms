#include <bits/stdc++.h>
using namespace std;

int N, M;
int total;
bool holes[13][13];
int queen_position[13];

bool threaten(const int row, const int cell) {
  int counter = 1;
  for (int j = row - 1; j >= 0; j--) {
    if (queen_position[j] == cell || queen_position[j] == cell + counter ||
        queen_position[j] == cell - counter)
      return true;

    counter++;
  }
  return false;
}

void count(const int row) {
  if (row == N) {
    total++;
    return;
  }
  for (int i = 0; i < N; i++) {
    if (holes[row][i]) continue;
    if (threaten(row, i)) continue;
    queen_position[row] = i;
    count(row + 1);
  }
}

void solve() {
  memset(holes, 0, sizeof holes);
  total = 0;

  for (int i = 0; i < M; i++) {
    int r, c;
    cin >> r >> c;
    holes[r][c] = true;
  }

  for (int i = 0; i < N; i++) {
    if (holes[0][i]) continue;
    queen_position[0] = i;
    count(1);
  }

  cout << total << endl;
}

int main() {
  while (scanf("%d %d", &N, &M) == 2) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
