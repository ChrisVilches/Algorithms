#include <bits/stdc++.h>

using namespace std;

struct BIT {
  BIT(int n) : bit_n(n + 1) { A.assign(bit_n, 0); }

  int query(int i) {
    i++;
    int sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

  void update(int i, int v) {
    i++;
    for (; i < bit_n; i += i & -i) A[i] += v;
  }

 private:
  int bit_n;
  vector<int> A;
};

int main() {
  int N;
  scanf("%d", &N);

  BIT bit(N);

  for (int i = 0; i < N; i++) bit.update(i, 1);

  for (int i = 0; i < N; i++) {
    int x;
    scanf("%d", &x);
    x--;

    int index = bit.query(x);

    if (i > 0) putchar_unlocked(' ');
    printf("%d", index);

    bit.update(x, -1);
  }

  putchar_unlocked('\n');
}
