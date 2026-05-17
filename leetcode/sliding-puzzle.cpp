#include <bits/stdc++.h>
using namespace std;

class Solution {
  const int di[4]{-1, 1, 0, 0};
  const int dj[4]{0, 0, -1, 1};

 public:
  int slidingPuzzle(const vector<vector<int>>& board) {
    set<vector<vector<int>>> visited;

    const vector<vector<int>> target{{1, 2, 3}, {4, 5, 0}};

    queue<pair<vector<vector<int>>, int>> q;
    q.emplace(board, 0);
    visited.emplace(board);

    while (!q.empty()) {
      const auto [state, moves] = q.front();
      q.pop();

      if (state == target) return moves;

      pair<int, int> zero;
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
          if (state[i][j] == 0) zero = {i, j};
        }
      }

      for (int d = 0; d < 4; d++) {
        const auto [i, j] = zero;
        const int i2 = i + di[d];
        const int j2 = j + dj[d];

        if (i2 < 0 || j2 < 0 || i2 >= 2 || j2 >= 3) continue;

        vector<vector<int>> new_state = state;
        swap(new_state[i][j], new_state[i2][j2]);

        if (visited.count(new_state)) continue;
        visited.emplace(new_state);

        q.emplace(new_state, moves + 1);
      }
    }

    return -1;
  }
};
