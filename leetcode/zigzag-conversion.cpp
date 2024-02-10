#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string convert(string s, int numRows) {
    bool down = true;
    int row = 0;
    int col = 0;
    vector<string> result(numRows, string(s.size(), ' '));

    for (const auto c : s) {
      if (row == 0) down = true;
      result[row][col] = c;

      if (down) {
        row++;
        if (row == numRows) {
          row = max(0, row - 2);
          col++;
          down = false;
        }
      } else {
        row--;
        col++;
      }
    }

    string ret;

    for (const auto& row : result) {
      for (const auto c : row) {
        if (c != ' ') ret += c;
      }
    }

    return ret;
  }
};
