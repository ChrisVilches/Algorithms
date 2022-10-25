#include <bits/stdc++.h>
using namespace std;

const int di[] = {-1, 1, 0, 0};
const int dj[] = {0, 0, -1, 1};

class Solution {
  bool visited[10][10];
  vector<vector<char>> board;
  string word;
  int rows, cols;
  bool found = false;
  int curr_string_size = 0;

  void search(const int i, const int j) {
    if (board[i][j] != word[curr_string_size]) return;

    visited[i][j] = true;
    curr_string_size++;

    if (curr_string_size == (int)word.size()) {
      found = true;
      return;
    }

    for (int d = 0; d < 4; d++) {
      const int i2 = i + di[d];
      const int j2 = j + dj[d];

      if (i2 < 0 || j2 < 0) continue;
      if (i2 >= rows || j2 >= cols) continue;
      if (visited[i2][j2]) continue;
      search(i2, j2);
    }

    curr_string_size--;
    visited[i][j] = false;
  }

 public:
  bool exist(vector<vector<char>>& board, string word) {
    this->board = board;
    this->word = word;
    this->rows = board.size();
    this->cols = board.front().size();

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        search(i, j);
        if (found) return true;
      }
    }

    return false;
  }
};
