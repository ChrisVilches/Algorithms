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
  int N, K;
  cin >> N >> K;

  BIT bit(N);

  for (int i = 0; i < K; i++) {
    int a, b;
    cin >> a >> b;
    bit.range_update(a - 1, b - 1, 1);
  }

  vector<int> nums;

  for (int i = 0; i < N; i++) {
    nums.push_back(bit.query(i));
  }

  sort(nums.begin(), nums.end());

  cout << nums[nums.size() / 2] << endl;
}
