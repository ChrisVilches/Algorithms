#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define MAX_N 1000007

char sequence[MAX_N];
ll psum[MAX_N];

ll sum_range(int l, int r) { return psum[r + 1] - psum[l]; }

int main() {
  int test = 1;

  while (scanf("%s", sequence) == 1) {
    int N = strlen(sequence);
    if (N == 0) break;

    psum[0] = 0;
    for (int i = 0; i < N; i++) {
      int value = sequence[i] - '0';
      psum[i + 1] = psum[i] + value;
    }

    int Q;
    scanf("%d", &Q);

    printf("Case %d:\n", test++);

    while (Q--) {
      int i, j;
      scanf("%d %d", &i, &j);
      if (i > j) swap(i, j);

      int ones_amount = j - i + 1;
      bool all_same = sum_range(i, j) == ones_amount || sum_range(i, j) == 0;

      printf("%s\n", all_same ? "Yes" : "No");
    }
  }
}
