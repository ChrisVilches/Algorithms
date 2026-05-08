#include <bits/stdc++.h>
using namespace std;

struct BIT {
  BIT(const int n) : bit_n(n + 1), A(bit_n, 0) {}

  int sum(int i) const {
    i++;
    int sum = 0;
    for (; i > 0; i -= i & -i) sum += A[i];
    return sum;
  }

  void update(int i, const int v) {
    i++;
    for (; i < bit_n; i += i & -i) A[i] += v;
  }

 private:
  const int bit_n;
  vector<int> A;
};

class LUPrefix {
  const int n;
  BIT bit;

 public:
  LUPrefix(const int size) : n(size), bit(n) {}

  void upload(const int video) { bit.update(video - 1, 1); }

  int longest() {
    int lo = 0;
    int hi = n - 1;
    while (lo <= hi) {
      const int mid = (lo + hi) / 2;
      if (bit.sum(mid) == mid + 1) {
        lo = mid + 1;
      } else {
        hi = mid - 1;
      }
    }

    return lo;
  }
};
