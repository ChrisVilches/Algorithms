#include <bits/stdc++.h>

using namespace std;

bool possible[1 << 21];
int N, M;

int main() {
  while (scanf("%d %d", &N, &M) == 2) {
    memset(possible, true, sizeof possible);

    for (int i = 0; i < M; i++) {
      int a, b;
      scanf("%d %d", &a, &b);
      a--;
      b--;

      for (int i = 0; i < (1 << N); i++) {
        bool has_first = i & (1 << a);
        bool has_second = i & (1 << b);
        possible[i] &= !has_first || !has_second;
      }
    }

    int total = 0;

    for (int i = 0; i < (1 << N); i++) total += possible[i];

    printf("%d\n", total);
  }
}
