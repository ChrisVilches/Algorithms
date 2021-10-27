#include <bits/stdc++.h>

using namespace std;
#define MAX 803
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef tuple<int, int, int, int> tiiii;

char original_grid[MAX][MAX];
char grid[MAX][MAX];
int bee_times[MAX][MAX];
int N, S;
int di[] = {-1, 1, 0, 0};
int dj[] = {0, 0, -1, 1};

inline bool correct_char(char c) {
  return c == 'H' || c == 'G' || c == 'T' || c == 'M' || c == 'D';
}

char read_cell() {
  char c;
  while (scanf("%c", &c) && !correct_char(c))
    ;
  return c;
}

inline bool valid_grid(int i, int j) {
  return !(i < 0 || j < 0 || i >= N || j >= N);
}

void grid_cpy() {
  for (int i = 0; i < N; i++)
    memcpy(grid[i], original_grid[i], sizeof(char) * N);
}

void calculate_bee_times() {
  grid_cpy();
  memset(bee_times, 0, sizeof bee_times);
  queue<tiii> q;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      if (grid[i][j] == 'H') q.push(make_tuple(i, j, 0));

  while (!q.empty()) {
    auto [i, j, t] = q.front();
    q.pop();
    bee_times[i][j] = t;
    for (int d = 0; d < 4; d++) {
      int next_i = i + di[d];
      int next_j = j + dj[d];
      if (!valid_grid(next_i, next_j)) continue;
      if (grid[next_i][next_j] != 'G') continue;
      grid[next_i][next_j] = 'H';
      q.push(make_tuple(next_i, next_j, t + S));
    }
  }
}

bool possible(int minutes, pii from, pii to) {
  //cerr << "test using " << minutes << " minutes" << endl;
  grid_cpy();
  queue<tiiii> q;
  q.push(make_tuple(from.first, from.second, minutes, S));

  while (!q.empty()) {
    auto [i, j, t, s] = q.front();
    q.pop();
    if (to == make_pair(i, j)){
      //fprintf(stderr, "it's possible\n");
      return true;
    }

    grid[i][j] = 'T';

   // fprintf(stderr, "bee_times[%d][%d] <= t ---> %d <= %d\n", i, j,
    //        bee_times[i][j], t);
    if (bee_times[i][j] <= t) continue;

    for (int d = 0; d < 4; d++) {
      int next_i = i + di[d];
      int next_j = j + dj[d];
      if (!valid_grid(next_i, next_j)) continue;
      if (!(grid[next_i][next_j] == 'G' || grid[next_i][next_j] == 'D'))
        continue;

      grid[next_i][next_j] = 'T';

      q.push(make_tuple(next_i, next_j, t+1, s));
    }
  }
  return false;
}

void solve() {
  //cerr << endl
  //     << "======================================== CASE "
 //         "========================================"
 //      << endl
 //      << endl;
  cin >> N >> S;
  pii mecho, home;

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      original_grid[i][j] = read_cell();
      if (original_grid[i][j] == 'D')
        home = make_pair(i, j);
      else if (original_grid[i][j] == 'M') {
        mecho = make_pair(i, j);
        original_grid[i][j] = 'G';
      }
    }

  calculate_bee_times();

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
     // cerr << bee_times[i][j] << ' ';
    }
    //cerr << endl;
  }
  //cerr << endl;

  if (!possible(0, mecho, home)) {
    cout << -1 << endl;
    return;
  }

  int left = 0;
  int right = (N * N) + S;
  int possible_time;
  while (left < right) {
    int mid = (left + right) / 2;
    if (possible(mid, mecho, home)) {
      left = mid + 1;
      possible_time = mid;
    } else {
      right = mid;
    }
  }

  cout << possible_time/S << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
