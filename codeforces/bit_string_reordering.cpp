#include <bits/stdc++.h>
using namespace std;

int N, M;

int calculate(const int first_bit, vector<int> seq, vector<int> run) {
  int total_swaps = 0;
  int curr_bit = first_bit;
  auto remaining = run.begin();

  for (auto it = seq.begin(); it != seq.end(); it++) {
    if (*it != curr_bit) {
      auto swap_bit = find(it, seq.end(), curr_bit);

      if (swap_bit == seq.end()) return INT_MAX;

      total_swaps += distance(it, swap_bit);
      iter_swap(it, swap_bit);
    }

    if (--(*remaining) == 0) {
      remaining++;
      curr_bit = !curr_bit;
    }
  }

  return total_swaps;
}

void solve() {
  vector<int> seq(N), run(M);

  for (int i = 0; i < N; i++) cin >> seq[i];
  for (int i = 0; i < M; i++) cin >> run[i];

  int ans = min(calculate(0, seq, run), calculate(1, seq, run));

  cout << ans << endl;
}

int main() {
  while (scanf("%d %d", &N, &M) == 2) solve();
}
