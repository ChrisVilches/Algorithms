#include <bits/stdc++.h>
using namespace std;

#define MAX 100007

struct BIT {
  BIT(int n) : bit_n(n + 1) { A.assign(bit_n, 0); }

  void range_update(int i, int j, int v) {
    update(i, v);
    update(j + 1, -v);
  }

  int query(int i) {
    i++;
    int sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

 private:
  int bit_n;
  vector<int> A;
  void update(int i, int v) {
    i++;
    for (; i < bit_n; i += i & -i) A[i] += v;
  }
};

int N, nums[MAX], L[MAX], R[MAX];

void update_worth_visiting(const int i, BIT& bit) {
  int l_max_idx = L[i];
  int r_max_idx = R[i];

  int from = ~l_max_idx ? i - (abs(l_max_idx - i) - 1) / 2 : 0;
  int to = ~r_max_idx ? i + (abs(r_max_idx - i) - 1) / 2 : N - 1;

  bit.range_update(from, i - 1, 1);
  bit.range_update(i + 1, to, 1);
}

int main() {
  cin >> N;
  BIT bit(N);

  for (int i = 0; i < N; i++) {
    cin >> nums[i];
  }

  L[0] = 0;
  for (int i = 1; i < N; i++) {
    L[i] = i - 1;
    while (nums[L[i]] <= nums[i] && L[i] > 0) L[i] = L[L[i]];
  }

  R[N - 1] = N - 1;
  for (int i = N - 2; i >= 0; i--) {
    R[i] = i + 1;
    while (nums[R[i]] <= nums[i] && R[i] < N - 1) R[i] = R[R[i]];
  }

  for (int i = 0; i < N; i++) {
    if (nums[i] > nums[R[i]]) R[i] = -1;
    if (nums[i] > nums[L[i]]) L[i] = -1;
  }

  for (int i = 0; i < N; i++) {
    update_worth_visiting(i, bit);
  }

  for (int i = 0; i < N; i++) cout << bit.query(i) << " ";

  cout << endl;
}
