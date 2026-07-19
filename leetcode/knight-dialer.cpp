#include <bits/stdc++.h>
using namespace std;

class Solution {
  static constexpr long long mod = 1e9 + 7;
  const array<int, 8> di{-2, -2, 2, 2, -1, -1, 1, 1};
  const array<int, 8> dj{-1, 1, -1, 1, -2, 2, -2, 2};

  vector<vector<int>> square_symmetric_matrix(const vector<vector<int>>& A) {
    const size_t n = A.size();
    vector<vector<int>> res(n, vector<int>(n, 0));

    for (size_t i = 0; i < n; i++) {
      for (size_t j = i; j < n; j++) {
        long long sum = 0;
        for (size_t k = 0; k < n; k++) {
          sum = (sum + 1LL * A[i][k] * A[k][j]) % mod;
        }
        res[i][j] = res[j][i] = sum;
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
  int knightDialer(const int n) {
    vector<vector<int>> T(12, vector<int>(12, 0));

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 3; j++) {
        if (i == 3 && (j == 0 || j == 2)) continue;

        for (int d = 0; d < 8; d++) {
          const int i2 = i + di[d];
          const int j2 = j + dj[d];
          if (i2 < 0 || j2 < 0 || i2 >= 4 || j2 >= 3) continue;
          if (i2 == 3 && (j2 == 0 || j2 == 2)) continue;
          T[i2 * 3 + j2][i * 3 + j] = 1;
        }
      }
    }

    vector<int> result(12, 1);
    result[11] = 0;
    result[9] = 0;

    for (int exp = n - 1; exp > 0; exp >>= 1) {
      if (exp & 1) {
        result = multiply_matrix_vector(T, result);
      }

      T = square_symmetric_matrix(T);
    }

    return accumulate(result.begin(), result.end(), 0LL) % mod;
  }
};
