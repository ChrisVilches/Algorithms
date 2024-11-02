#include <bits/stdc++.h>
using namespace std;

class Solution {
  short rows[9][10];
  short cols[9][10];
  short subbox[3][3][10];

 public:
  bool isValidSudoku(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j] == '.') continue;

        const int d = board[i][j] - '0';

        if (rows[i][d]++) return false;
        if (cols[j][d]++) return false;
        if (subbox[i / 3][j / 3][d]++) return false;
      }
    }

    return true;
  }
};
