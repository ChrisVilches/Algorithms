#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tiii;

int N, Q;
tiii tree[4 * 100001];
int lazy[4 * 100001];

inline tiii add_tuple(const tiii& t1, const tiii& t2) {
  auto [a1, b1, c1] = t1;
  auto [a2, b2, c2] = t2;
  return {a1 + a2, b1 + b2, c1 + c2};
}

inline tiii shift_tuple(const tiii& t, const int times) {
  auto [a, b, c] = t;
  if (times % 3 == 1) return {c, a, b};
  if (times % 3 == 2) return {b, c, a};
  return t;
}

inline int left(int p) { return p << 1; }
inline int right(int p) { return (p << 1) + 1; }

void initialize_tree(int p, int a, int b) {
  if (a == b)
    tree[p] = {1, 0, 0};
  else {
    initialize_tree(left(p), a, (a + b) / 2);
    initialize_tree(right(p), (a + b) / 2 + 1, b);
    tree[p] = add_tuple(tree[left(p)], tree[right(p)]);
  }
}

void propagate_one_level(int node, int a, int b) {
  if (lazy[node] == 0) return;
  tree[node] = shift_tuple(tree[node], lazy[node]);

  if (a != b) {
    lazy[left(node)] += lazy[node];
    lazy[right(node)] += lazy[node];
  }

  lazy[node] = 0;
}

void change_symbol(int node, int a, int b, int i, int j) {
  propagate_one_level(node, a, b);
  if (a > j || b < i) return;

  if (i <= a && b <= j) {
    tree[node] = shift_tuple(tree[node], 1);

    if (a != b) {
      lazy[left(node)]++;
      lazy[right(node)]++;
    }
    return;
  }

  change_symbol(left(node), a, (a + b) / 2, i, j);
  change_symbol(right(node), (a + b) / 2 + 1, b, i, j);
  tree[node] = add_tuple(tree[left(node)], tree[right(node)]);
}

tiii count_frequencies(int node, int a, int b, int i, int j) {
  if (a > j || b < i) return {0, 0, 0};
  propagate_one_level(node, a, b);
  if (i <= a && b <= j) return tree[node];

  return add_tuple(count_frequencies(left(node), a, (a + b) / 2, i, j),
                   count_frequencies(right(node), 1 + (a + b) / 2, b, i, j));
}

int main() {
  while (scanf("%d %d", &N, &Q) == 2) {
    memset(lazy, 0, sizeof(int) * 4 * N);
    initialize_tree(1, 0, N - 1);

    while (Q--) {
      char query_type;
      int i, j;
      scanf(" %c %d %d", &query_type, &i, &j);
      i--;
      j--;

      switch (query_type) {
        case 'M':
          change_symbol(1, 0, N - 1, i, j);
          break;
        default:
          auto [a, b, c] = count_frequencies(1, 0, N - 1, i, j);
          printf("%d %d %d\n", a, b, c);
      }
    }

    putchar_unlocked('\n');
  }
}
