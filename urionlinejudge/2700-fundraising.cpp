#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Segtree {
 private:
  vector<ll> tree;
  int n;
  inline int left(int p) { return p << 1; }
  inline int right(int p) { return (p << 1) + 1; }

  ll max_query(int p, int L, int R, int i, int j) {
    if (i > R || j < L) return INT_MIN;
    if (L >= i && R <= j) return tree[p];
    return max(max_query(left(p), L, (L + R) / 2, i, j),
               max_query(right(p), (L + R) / 2 + 1, R, i, j));
  }

  void update(int p, int L, int R, int pos, ll new_val) {
    if (L == R) {
      tree[p] = new_val;
    } else {
      int m = (L + R) / 2;
      if (pos <= m)
        update(left(p), L, m, pos, new_val);
      else
        update(right(p), m + 1, R, pos, new_val);
      tree[p] = max(tree[left(p)], tree[right(p)]);
    }
  }

 public:
  Segtree(int n) : n(n) { tree.assign(4 * n, 0); }
  ll max_query(int i, int j) { return max_query(1, 0, n - 1, i, j); }
  void update(int pos, ll val) { return update(1, 0, n - 1, pos, val); }
};

struct Guest {
  ll B, F, D;

  void from_stdin() { cin >> B >> F >> D; }

  bool operator<(const Guest& g) const {
    if (B == g.B) return F > g.F;
    return B < g.B;
  }
};

int compress_f(vector<Guest>& guests) {
  sort(guests.begin(), guests.end(),
       [](const Guest& g1, const Guest& g2) { return g1.F < g2.F; });

  ll val = 1;
  ll curr = guests.front().F;

  for (Guest& g : guests) {
    if (g.F != curr) val++;
    curr = g.F;
    g.F = val;
  }

  return (int)val;
}

vector<Guest> group_same_and_sort(vector<Guest>& guests) {
  sort(guests.begin(), guests.end());

  vector<Guest> res;

  pair<ll, ll> curr = {-1, -1};

  for (const Guest& g : guests) {
    if (curr != make_pair(g.B, g.F)) {
      curr = {g.B, g.F};
      res.push_back(Guest{g.B, g.F, 0});
    }

    res.back().D += g.D;
  }

  return res;
}

int main() {
  int N;

  while (cin >> N) {
    vector<Guest> guests(N);

    for (int i = 0; i < N; i++) guests[i].from_stdin();

    int tree_size = compress_f(guests) + 1;
    guests = group_same_and_sort(guests);

    Segtree st(tree_size);

    for (const auto [B, F, D] : guests) {
      ll max_val = st.max_query(0, F - 1);
      ll curr = st.max_query(F, F);

      if (curr < D + max_val) st.update(F, max_val + D);
    }

    cout << st.max_query(0, tree_size - 1) << endl;
  }
}
