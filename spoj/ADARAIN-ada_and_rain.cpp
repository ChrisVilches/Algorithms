#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll nums[1'000'007];

int main() {
  int N, M, W;

  cin >> N >> M >> W;

  vector<pair<int, int>> deltas;

  for (int i = 0; i < N; i++) {
    int l, r;
    cin >> l >> r;
    deltas.emplace_back(l, 1);
    deltas.emplace_back(r + 1, -1);
  }

  sort(deltas.begin(), deltas.end());

  int d = 0;
  ll curr = 0;

  for (int i = 0; i < W; i++) {
    while (d < (int)deltas.size() && deltas[d].first == i) {
      curr += deltas[d++].second;
    }

    nums[i] = curr;
  }

  for (int i = 0; i < M; i++) {
    int q;
    cin >> q;

    cout << nums[q] << '\n';
  }
}
