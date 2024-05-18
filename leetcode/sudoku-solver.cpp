#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<pair<int, int>> empty_cells;
  int solution[9][9];
  bool rows[9][10];
  bool cols[9][10];
  bool subbox[3][3][10];

  bool recur(const int cell_idx) {
    if (cell_idx == (int)empty_cells.size()) return true;

    const auto [i, j] = empty_cells[cell_idx];

    for (int d = 1; d <= 9; d++) {
      if (rows[i][d] || cols[j][d] || subbox[i / 3][j / 3][d]) continue;

      rows[i][d] = true;
      cols[j][d] = true;
      subbox[i / 3][j / 3][d] = true;

      solution[i][j] = d;
      if (recur(cell_idx + 1)) return true;

      rows[i][d] = false;
      cols[j][d] = false;
      subbox[i / 3][j / 3][d] = false;
    }

    return false;
  }

 public:
  void solveSudoku(vector<vector<char>>& board) {
    memset(rows, 0, sizeof rows);
    memset(cols, 0, sizeof cols);
    memset(subbox, 0, sizeof subbox);

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        const char c = board[i][j];
        if (c == '.') {
          empty_cells.emplace_back(i, j);
          solution[i][j] = 0;
        } else {
          const int d = c - '0';
          solution[i][j] = d;
          rows[i][d] = true;
          cols[j][d] = true;
          subbox[i / 3][j / 3][d] = true;
        }
      }
    }

    assert(recur(0));

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        board[i][j] = '0' + solution[i][j];
      }
    }
  }
};
