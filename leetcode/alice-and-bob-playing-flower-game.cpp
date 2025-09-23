#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  long long flowerGame(const int n, const int m) {
    const long long n_even = n / 2;
    const long long n_odd = (n + 1) / 2;
    const long long m_even = m / 2;
    const long long m_odd = (m + 1) / 2;

    return (n_even * m_odd) + (n_odd * m_even);
  }
};
