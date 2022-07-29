#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K;

  while (cin >> N >> K) {
    vector<pair<int, int>> deltas, slopes;

    for (int i = 0; i < K; i++) {
      char type;
      int x1, x2;
      cin >> type >> x1 >> x2;

      switch (type) {
        case 'R':
          deltas.emplace_back(x1, 1);
          deltas.emplace_back(x2 + 1, -1);
          break;
        case 'D':
          deltas.emplace_back(x1, -1);
          deltas.emplace_back(x2 + 1, 1);
          break;
        default:
          const int a = type == 'V' ? 1 : -1;
          const int m = (x1 + x2) / 2;

          slopes.emplace_back(x1, -a);
          slopes.emplace_back(1 + m, a);
          slopes.emplace_back(((x2 - x1) % 2) + 1 + m, a);
          slopes.emplace_back(x2 + 2, -a);
      }
    }

    sort(deltas.begin(), deltas.end());
    sort(slopes.begin(), slopes.end());

    long long curr = 0;
    long long add = 0;

    auto d = deltas.begin();
    auto s = slopes.begin();

    for (int x = 1; x <= N; x++) {
      while (d != deltas.end() && d->first == x) {
        curr += d->second;
        ++d;
      }
      while (s != slopes.end() && s->first == x) {
        add += s->second;
        ++s;
      }

      curr += add;
      cout << curr << '\n';
    }
  }
}
