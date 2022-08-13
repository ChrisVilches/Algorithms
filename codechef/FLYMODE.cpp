#include <bits/stdc++.h>
using namespace std;

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

int main() {
  int N;
  cin >> N;
  vector<int> H(N);

  for (auto& h : H) cin >> h;

  vector<pair<int, int>> compress;
  for (int i = 0; i < N; i++) compress.emplace_back(H[i], i);
  sort(compress.begin(), compress.end());

  int curr = compress.front().first;
  int compressed_h = 0;

  for (const auto& [h, idx] : compress) {
    if (curr != h) compressed_h += 2;
    curr = h;
    H[idx] = compressed_h;
  }

  const int bit_size = compressed_h + 1;

  BIT bit(bit_size);

  for (int i = 0; i < N - 1; i++) {
    const auto [from, to] = minmax(H[i], H[i + 1]);
    bit.range_update(from, to, 1);

    if (i != 0) bit.range_update(H[i], H[i], -1);
  }

  int ans = 0;

  for (int i = 0; i < bit_size; i++) {
    ans = max(ans, bit.query(i));
  }

  cout << ans << endl;
}
