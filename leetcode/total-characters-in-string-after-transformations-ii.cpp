#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;

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

  vector<vector<int>> square_matrix(const vector<vector<int>>& A) {
    const int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
      for (int k = 0; k < n; k++) {
        for (int j = 0; j < n; j++) {
          C[i][j] = (C[i][j] + 1LL * A[i][k] * A[k][j]) % mod;
        }
      }
    }

    return C;
  }

 public:
  int lengthAfterTransformations(const string s, const int t, const vector<int>& nums) {
    vector<vector<int>> T(26, vector<int>(26, 0));

    for (int i = 0; i < 26; i++) {
      for (int j = i + 1; j <= i + nums[i]; j++) {
        T[j % 26][i]++;
      }
    }

    vector<int> result(26, 0);

    for (const char c : s) result[c - 'a']++;

    for (int exp = t; exp > 0; exp >>= 1) {
      if (exp & 1) {
        result = multiply_matrix_vector(T, result);
      }

      T = square_matrix(T);
    }

    return accumulate(result.begin(), result.end(), 0LL) % mod;
  }
};
