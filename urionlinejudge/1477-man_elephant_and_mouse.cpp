#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tiii;

/*
Micro-optimized.
*/

int N, Q;
tiii tree[4 * 100004];
int lazy[4 * 100004];

void print(uint32_t n) {
  if (n / 10) print(n / 10);
  putchar_unlocked(n % 10 + '0');
}

uint32_t read_int() {
  char r;
  bool b, start = false;
  uint32_t ret = 0;
  while (true) {
    r = getchar_unlocked();
    b = (r < 47 || r > 58);
    if (!start && b) continue;
    if (start && b) break;
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

inline tiii shift_tuple(const tiii& t, int times) {
  switch (times % 3) {
    case 1:
      return {get<2>(t), get<0>(t), get<1>(t)};
    case 2:
      return {get<1>(t), get<2>(t), get<0>(t)};
    default:
      return t;
  }
}

inline int left(int p) { return p << 1; }
inline int right(int p) { return (p << 1) | 1; }

void initialize_tree(int p, int a, int b) {
  if (a == b)
    tree[p] = {1, 0, 0};
  else {
    initialize_tree(left(p), a, (a + b) >> 1);
    initialize_tree(right(p), 1 + ((a + b) >> 1), b);
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

  change_symbol(left(node), a, (a + b) >> 1, i, j);
  change_symbol(right(node), 1 + ((a + b) >> 1), b, i, j);
  tree[node] = add_tuple(tree[left(node)], tree[right(node)]);
}

tiii count_frequencies(int node, int a, int b, int i, int j) {
  if (a > j || b < i) return {0, 0, 0};
  propagate_one_level(node, a, b);
  if (i <= a && b <= j) return tree[node];

  return add_tuple(count_frequencies(left(node), a, (a + b) >> 1, i, j),
                   count_frequencies(right(node), 1 + ((a + b) >> 1), b, i, j));
}

int main() {
  char query_type;
  int i, j;
  tiii res;

  while (scanf("%d", &N) == 1) {
    Q = read_int();
    memset(lazy, 0, sizeof(int) * 4 * (N + 1));
    initialize_tree(1, 0, N);

    while (Q--) {
      query_type = '\0';
      while (!(query_type & 64)) query_type = getchar_unlocked();
      i = read_int();
      j = read_int();

      switch (query_type) {
        case 'M':
          change_symbol(1, 0, N, i, j);
          break;
        default:
          res = count_frequencies(1, 0, N, i, j);
          print(get<0>(res));
          putchar_unlocked(' ');
          print(get<1>(res));
          putchar_unlocked(' ');
          print(get<2>(res));
          putchar_unlocked('\n');
      }
    }

    putchar_unlocked('\n');
  }
}
