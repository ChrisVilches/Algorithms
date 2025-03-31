#include <bits/stdc++.h>
using namespace std;

class ProductOfNumbers {
  vector<int> prods, zeros{0};

  int div(const int k) {
    const int n = prods.size();
    const int idx = n - k - 1;
    return idx < 0 ? 1 : prods[idx];
  }

  bool has_zero(const int k) {
    const size_t n = prods.size();
    const size_t from = n - k;
    const size_t to = n - 1;
    return zeros[to + 1] - zeros[from] != 0;
  }

 public:
  void add(const int num) {
    if (num == 0) {
      prods.emplace_back(1);
      zeros.emplace_back(zeros.back() + 1);
    } else {
      const int prev = prods.empty() ? 1 : prods.back();
      prods.emplace_back(prev * num);
      zeros.emplace_back(zeros.back());
    }
  }

  int getProduct(const int k) {
    if (has_zero(k)) return 0;
    return prods.back() / div(k);
  }
};
