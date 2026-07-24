#include <bits/stdc++.h>
using namespace std;

class Solution {
  static constexpr long long mod = 1e9 + 7;

  vector<vector<int>> square_symmetric_matrix(const vector<vector<int>>& A) {
    const size_t n = A.size();
    vector<vector<int>> res(n, vector<int>(n, 0));

    for (size_t i = 0; i < n; i++) {
      for (size_t j = i; j < n; j++) {
        long long sum = 0;

        for (size_t k = 0; k < n; k++) {
          sum += 1LL * A[i][k] * A[k][j];
          sum %= mod;
        }

        res[i][j] = sum;
        res[j][i] = sum;
      }
    }

    return res;
  }

  vector<int> multiply_matrix_vector(const vector<vector<int>>& A, const vector<int>& x) {
    const size_t n = x.size();
    vector<int> res(n, 0);

    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        res[i] = (res[i] + 1LL * A[i][j] * x[j]) % mod;
      }
    }

    return res;
  }

 public:
  int zigZagArrays(const int n, const int l, const int r) {
    const int m = r - l + 1;

    vector<vector<int>> T(2 * m, vector<int>(2 * m, 0));

    for (int i = 0; i < 2 * m; i++) {
      const bool first = i < m;
      const int x = first ? i : i - m;
      for (int j = 0; j < m; j++) {
        T[i][first ? j + m : j] = first ? x > j : x < j;
      }
    }

    vector<int> result(2 * m, 1);

    for (int exp = n - 1; exp > 0; exp >>= 1) {
      if (exp & 1) {
        result = multiply_matrix_vector(T, result);
      }

      T = square_symmetric_matrix(T);
    }

    return accumulate(result.begin(), result.end(), 0LL) % mod;
  }
};
