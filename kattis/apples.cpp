#include <bits/stdc++.h>
using namespace std;

int main() {
  int R, C;
  while (cin >> R >> C) {
    vector<string> grid(R);
    for (auto& row : grid) cin >> row;

    vector<string> result(R, string(C, ' '));

    for (int r = 0; r < R; r++) {
      for (int c = 0; c < C; c++) {
        const char cell = grid[r][c];
        result[r][c] = cell == '#' ? '#' : '.';
      }
    }

    for (int c = 0; c < C; c++) {
      deque<int> empty_pos;

      for (int r = R - 1; r >= 0; r--) {
        const char cell = grid[r][c];

        if (cell == '.') empty_pos.push_back(r);
        if (cell == '#') empty_pos.clear();
        if (cell != 'a') continue;

        if (empty_pos.empty()) {
          result[r][c] = 'a';
        } else {
          result[empty_pos.front()][c] = 'a';
          empty_pos.pop_front();
          empty_pos.push_back(r);
        }
      }
    }

    for (const auto& row : result) {
      cout << row << endl;
    }
  }
}
