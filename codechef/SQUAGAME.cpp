#include <bits/stdc++.h>
using namespace std;

// https://en.wikipedia.org/wiki/Sprague%E2%80%93Grundy_theorem

vector<int> find_winning_moves(const vector<vector<int>>& forest,
                               const vector<int>& roots) {
  vector<int> g(forest.size(), 0);

  const function<int(int)> calculate_grundy = [&](const int u) {
    for (const int v : forest[u]) {
      g[u] ^= calculate_grundy(v);
    }

    g[u]++;
    return g[u];
  };

  int forest_xor_sum = 0;
  for (const int r : roots) {
    forest_xor_sum ^= calculate_grundy(r);
  }

  vector<int> moves;

  const function<void(int, int)> find_moves = [&](const int u, const int target_val) {
    if (target_val == 0) {
      moves.push_back(u);
      return;
    }

    const int target_children_xor = target_val - 1;
    const int curr_children_xor = g[u] - 1;

    for (const int v : forest[u]) {
      find_moves(v, target_children_xor ^ curr_children_xor ^ g[v]);
    }
  };

  for (const int r : roots) {
    find_moves(r, forest_xor_sum ^ g[r]);
  }

  return moves;
}

struct BIT {
  BIT(const int size) : n(size + 1), A(n, 0) {}

  void range_update(const int i, const int j, const int v) {
    update(i, v);
    update(j + 1, -v);
  }

  int query(int i) const {
    i++;
    int sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

 private:
  const int n;
  vector<int> A;
  void update(int i, const int v) {
    i++;
    for (; i < n; i += i & -i) A[i] += v;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<pair<int, int>> events, squares(n), ys;

    for (int i = 0; i < n; i++) {
      int x, y, a;
      cin >> x >> y >> a;
      ys.emplace_back(y, ~i);
      ys.emplace_back(y + a, i);
      events.emplace_back(x, i);
      events.emplace_back(x + a, ~i);
    }

    sort(ys.begin(), ys.end());

    int comp_y = 0;

    for (const auto& [y, i] : ys) {
      if (i < 0) {
        squares[~i].first = comp_y;
      } else {
        squares[i].second = comp_y;
      }

      comp_y++;
    }

    sort(events.begin(), events.end());

    const int bit_size = comp_y + 1;
    BIT bit(bit_size);

    bit.range_update(0, bit_size - 1, -1);

    vector<vector<int>> forest(n);
    vector<int> roots;
    vector<int> delta(n);

    for (const auto& [_, i] : events) {
      const auto [lo, hi] = squares[i < 0 ? ~i : i];

      if (i < 0) {
        bit.range_update(lo, hi, -delta[~i]);
        continue;
      }

      const int curr_value = bit.query(lo);
      delta[i] = i - curr_value;

      bit.range_update(lo, hi, delta[i]);

      if (curr_value == -1) {
        roots.emplace_back(i);
      } else {
        forest[curr_value].emplace_back(i);
      }
    }

    const vector<int> moves = find_winning_moves(forest, roots);

    if (moves.empty()) {
      cout << "Fit" << endl;
    } else {
      const int ans = *min_element(moves.begin(), moves.end());
      cout << "Fat " << ans + 1 << endl;
    }
  }
}
