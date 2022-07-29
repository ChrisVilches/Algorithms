#include <bits/stdc++.h>
using namespace std;

struct Delta {
  int x, val, add;
  Delta(const int x, const int val, const int add) : x(x), val(val), add(add) {}
  bool operator<(const Delta& delta) const { return x < delta.x; }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, K;

  while (cin >> N >> K) {
    vector<Delta> deltas;

    for (int i = 0; i < K; i++) {
      char type;
      int x1, x2;
      cin >> type >> x1 >> x2;

      switch (type) {
        case 'R':
          deltas.emplace_back(x1, 1, 0);
          deltas.emplace_back(x2 + 1, -1, 0);
          break;
        case 'D':
          deltas.emplace_back(x1, -1, 0);
          deltas.emplace_back(x2 + 1, 1, 0);
          break;
        default:
          const int a = type == 'V' ? 1 : -1;
          const int m = (x1 + x2) / 2;

          deltas.emplace_back(x1, 0, -a);
          deltas.emplace_back(1 + m, 0, a);
          deltas.emplace_back(((x2 - x1) % 2) + 1 + m, 0, a);
          deltas.emplace_back(x2 + 2, 0, -a);
      }
    }

    sort(deltas.begin(), deltas.end());

    long long curr = 0;
    long long add = 0;

    auto d = deltas.begin();

    for (int x = 1; x <= N; x++) {
      while (d != deltas.end() && d->x == x) {
        curr += d->val;
        add += d->add;
        ++d;
      }
      curr += add;
      cout << curr << '\n';
    }
  }
}
