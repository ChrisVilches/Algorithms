#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tiii;

/*
Micro-optimized.
*/

int N, Q;
tiii tree[4 * 100001];
short lazy[4 * 100001];

void print(uint32_t n) {
  if (n / 10) print(n / 10);
  putchar_unlocked(n % 10 + '0');
}

uint32_t read_int() {
  char r;
  bool start = false;
  uint32_t ret = 0;
  start = false;
  ret = 0;
  while (true) {
    r = getchar_unlocked();
    if (!start && (r < 47 || r > 58)) continue;
    if (start && (r < 47 || r > 58)) break;
    if (start) ret *= 10;
    start = true;
    ret += r - '0';
  }
  return ret;
}

inline tiii add_tuple(const tiii& t1, const tiii& t2) {
  return {get<0>(t1) + get<0>(t2), get<1>(t1) + get<1>(t2),
          get<2>(t1) + get<2>(t2)};
}

inline tiii shift_tuple(const tiii& t, const int times) {
  auto [a, b, c] = t;
  switch (times) {
    case 1:
      return {c, a, b};
    case 2:
      return {b, c, a};
    default:
      return t;
  }
}

inline short add_mod3(short a, short b) {
  if (a + b < 3) return a + b;
  return a + b - 3;
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
    lazy[left(node)] = add_mod3(lazy[left(node)], lazy[node]);
    lazy[right(node)] = add_mod3(lazy[right(node)], lazy[node]);
  }

  lazy[node] = 0;
}

void change_symbol(int node, int a, int b, int i, int j) {
  propagate_one_level(node, a, b);
  if (a > j || b < i) return;

  if (i <= a && b <= j) {
    tree[node] = shift_tuple(tree[node], 1);

    if (a != b) {
      lazy[left(node)] = add_mod3(lazy[left(node)], 1);
      lazy[right(node)] = add_mod3(lazy[right(node)], 1);
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
    memset(lazy, 0, sizeof(short) * 4 * N);
    initialize_tree(1, 0, N - 1);

    while (Q--) {
      char query_type = '\0';
      int i, j;
      while (!(query_type & 64)) query_type = getchar_unlocked();
      i = read_int() - 1;
      j = read_int() - 1;

      switch (query_type) {
        case 'M':
          change_symbol(1, 0, N - 1, i, j);
          break;
        default:
          auto [a, b, c] = count_frequencies(1, 0, N - 1, i, j);
          print(a);
          putchar_unlocked(' ');
          print(b);
          putchar_unlocked(' ');
          print(c);
          putchar_unlocked('\n');
      }
    }

    putchar_unlocked('\n');
  }
}
