#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// TODO: Try to remove the "idx".
// TODO: Find code smells, refactor, etc.
struct Set {
  int idx;
  int elements;
  ll sum;
  Set* parent = nullptr;
  Set(int i, int n, ll s) : idx(i), elements(n), sum(s) {}
  Set() {}
  void insert(const ll p) {
    elements++;
    sum += p;
  }
  void remove(const ll p) {
    elements--;
    sum -= p;
  }
  void merge(const Set& s) {
    elements += s.elements;
    sum += s.sum;
  }
  pair<int, ll> query_set_data() const { return {elements, sum}; }
};

int parent[100007];
Set sets[100007];

Set* find(const int p) {
  Set* s = &sets[parent[p]];
  while (s->parent) s = s->parent;
  parent[p] = s->idx;
  return s;
}

void union_sets(const int p, const int q) {
  if (find(p)->idx == find(q)->idx) return;

  find(q)->merge(*find(p));
  find(p)->parent = find(q);
}

void move_to_set(const int p, const int q) {
  find(p)->remove(p);
  parent[p] = find(q)->idx;
  find(p)->insert(p);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;

  while (cin >> N >> M) {
    iota(parent, parent + N + 1, 0);
    for (int i = 0; i <= N; i++) sets[i] = Set(i, 1, i);

    while (M--) {
      int type, p, q;

      cin >> type;
      switch (type) {
        case 1:
          cin >> p >> q;
          union_sets(p, q);
          break;
        case 2:
          cin >> p >> q;
          move_to_set(p, q);
          break;
        case 3:
          cin >> p;
          const auto [n, sum] = find(p)->query_set_data();
          cout << n << " " << sum << '\n';
          break;
      }
    }
  }
}
