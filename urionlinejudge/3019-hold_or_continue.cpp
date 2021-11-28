#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

const int N = 75;
ld a[N + 3];
ld dp[N + 3][N + 3];
int ans[N + 3][N + 3][N + 3];

ld solve(int A, int B) {
  ld p = 0.5L;

  for (int t = 0; t < 100; t++) {
    swap(A, B);

    for (int i = 0; i <= N; i++) {
      if (i == 0 || A + i > N) {
        a[i] = 1 - p;
      } else if (A + i == N) {
        a[i] = 1;
      } else {
        a[i] = 1 - dp[B][A + i];
      }
    }

    for (int i = N - A - 1; i >= 0; i--) {
      ld curr = 1 - p;
      for (int j = 2; j <= 6; j++) {
        if (i + j <= N) {
          curr += a[i + j];
        } else {
          curr += 1 - p;
        }
      }
      a[i] = max(a[i], curr / 6);
    }
    p = a[0];
  }

  return p;
}

void calculate_answer(int A, int B) {
  for (int i = 0; i <= N; i++) {
    if (A + i > N) {
      a[i] = 1 - dp[B][A];
    } else if (A + i == N) {
      a[i] = 1;
    } else {
      a[i] = 1 - dp[B][A + i];
    }
  }
  for (int i = N - A; i >= 0; i--) {
    ld curr = 1 - dp[B][A];
    for (int j = 2; j <= 6; j++) {
      if (i + j <= N) {
        curr += a[i + j];
      } else {
        curr += 1 - dp[B][A];
      }
    }

    if (curr / 6L > a[i]) {
      a[i] = curr / 6;
      ans[A][B][i] = 0;
    } else {
      ans[A][B][i] = 1;
    }
  }
}

int main() {
  for (int i = 0; i < N; i++) {
    dp[N][i] = 1;
  }

  for (int sum = 2 * N; sum >= 0; sum--) {
    for (int A = 0; A < N; A++) {
      int B = sum - A;
      if (B < 0 || B >= N) continue;
      if (A == N - 1) {
        dp[A][B] = 0;
        continue;
      }
      if (B == N - 1) {
        dp[A][B] = 1;
        continue;
      }
      dp[A][B] = solve(A, B);
    }

    for (int A = 0; A < N - 1; A++) {
      int B = sum - A;
      if (B < 0 || B >= N - 1) continue;
      calculate_answer(A, B);
    }
  }
  /*
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        fprintf(stderr, "dp[%d][%d] = %.5f\n", i, j, (double)dp[i][j]);
      }
    }
  */
  int q;
  while (scanf("%d", &q) == 1)
    while (q--) {
      int A, B, X;
      cin >> A >> B >> X;
      if (ans[A][B][X]) {
        cout << 'H' << endl;
      } else {
        cout << 'C' << endl;
      }
    }
}
