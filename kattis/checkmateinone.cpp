#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

const int di[8]{-1, -1, -1, 0, 0, 1, 1, 1};
const int dj[8]{-1, 0, 1, -1, 1, -1, 0, 1};

set<pii> move_piece(const pii pos, const set<pii> blocked, const bool is_rook) {
  set<pii> possible_moves;

  for (int d = 0; d < 8; d++) {
    if (is_rook && di[d] * dj[d] != 0) continue;

    for (int steps = 1; is_rook || steps == 1; steps++) {
      const int i2 = pos.first + steps * di[d];
      const int j2 = pos.second + steps * dj[d];
      if (i2 < 0 || j2 < 0 || i2 >= 8 || j2 >= 8 || blocked.count({i2, j2})) break;
      possible_moves.emplace(i2, j2);
    }
  }

  return possible_moves;
}

bool can_attack(const pii src, const pii other, const pii dest, const bool is_rook) {
  return move_piece(src, {other}, is_rook).count(dest);
}

bool can_escape(const pii K, const pii R, const pii k) {
  for (const pii& escape_move : move_piece(k, {}, false)) {
    if (!can_attack(K, R, escape_move, false) && !can_attack(R, K, escape_move, true))
      return true;
  }

  return false;
}

int main() {
  vector<string> grid(8);
  for (string& row : grid) cin >> row;

  pii k, K, R;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (grid[i][j] == 'k') k = {i, j};
      if (grid[i][j] == 'K') K = {i, j};
      if (grid[i][j] == 'R') R = {i, j};
    }
  }

  bool ans = false;

  for (const pii& R : move_piece(R, {K, k}, true)) {
    if (!can_attack(R, K, k, true)) continue;
    if (!can_escape(K, R, k)) ans = true;
  }

  for (const pii& K : move_piece(K, {R, k}, false)) {
    if (!can_attack(K, R, k, false)) continue;
    if (!can_escape(K, R, k)) ans = true;
  }

  cout << (ans ? "Yes" : "No") << endl;
}
