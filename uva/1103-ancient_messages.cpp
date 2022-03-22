#include <bits/stdc++.h>
using namespace std;

int H, W, curr_id, amount_letters;
short grid[207][207];

const int di[] = {0, 0, -1, 1};
const int dj[] = {-1, 1, 0, 0};
const char letter_map[] = {'W', 'A', 'K', 'J', 'S', 'D'};

void read_grid() {
  memset(grid, 0, sizeof grid);

  for (int i = 1; i <= H; i++) {
    string line;
    cin >> line;

    int row = 1;

    for (char c : line) {
      const short hex = (c >= '0' && c <= '9') ? c - '0' : 10 + c - 'a';

      int bit = 8;
      do {
        grid[i][row++] = (hex & bit) > 0;
      } while (bit /= 2);
    }
  }

  H += 2;
  W = (4 * W) + 2;
}

void fill(const int i, const int j, const int from, const int to) {
  if (grid[i][j] != from) return;
  grid[i][j] = to;

  for (int d = 0; d < 4; d++) {
    const int i2 = i + di[d];
    const int j2 = j + dj[d];

    if (i2 < 0 || j2 < 0 || i2 >= H || j2 >= W) continue;
    fill(i2, j2, from, to);
  }
}

void fill_background() { fill(0, 0, 0, -1); }

void assign_id_each_letter() {
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (grid[i][j] == 1) {
        fill(i, j, 1, curr_id++);
        amount_letters++;
      }
    }
  }
}

void fill_holes() {
  for (int i = 0; i < H; i++)
    for (int j = 0; j < W; j++)
      if (grid[i][j] == 0) fill(i, j, 0, curr_id++);
}

map<int, int> count_holes() {
  auto id_is_hole = [](const int id) -> bool { return id - 2 >= amount_letters; };

  map<int, set<int>> hole_set;

  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W - 1; j++) {
      const int hole_id = grid[i][j];
      const int letter_id = grid[i][j + 1];

      if (id_is_hole(hole_id) && !id_is_hole(letter_id))
        hole_set[letter_id].insert(hole_id);
    }
  }

  map<int, int> res;
  for (const auto& [k, v] : hole_set) res[k] = v.size();

  return res;
}

multiset<char> get_solution() {
  map<int, int> counts = count_holes();
  multiset<char> letters;

  for (int i = 0; i < amount_letters; i++) {
    const int letter_id = 2 + i;
    const int hole_count = counts[letter_id];
    const char c = letter_map[hole_count];
    letters.insert(c);
  }
  return letters;
}

void solve() {
  curr_id = 2;
  amount_letters = 0;

  read_grid();
  fill_background();
  assign_id_each_letter();
  fill_holes();

  for (const auto c : get_solution()) cout << c;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int test_n = 1;
  while (cin >> H >> W && H && W) {
    cout << "Case " << test_n++ << ": ";
    solve();
    cout << endl;
  }
}
