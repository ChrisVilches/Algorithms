#include <bits/stdc++.h>
using namespace std;

class Solution {
  const long long mod = 1e9 + 7;

  vector<int> kmp(const string& s, const string& pattern) const {
    vector<int> lps(pattern.size());
    lps.front() = 0;
    for (size_t i = 1, j = 0; i < pattern.size(); i++) {
      while (j != 0 && pattern[i] != pattern[j]) j = lps[j - 1];
      if (pattern[i] == pattern[j]) j++;
      lps[i] = j;
    }
    vector<int> matches;
    for (size_t i = 0, j = 0; i < s.size(); i++) {
      while (j != 0 && s[i] != pattern[j]) j = lps[j - 1];
      if (s[i] == pattern[j]) j++;
      if (j == pattern.size()) {
        matches.emplace_back(i - j + 1);
        j = lps[j - 1];
      }
    }
    return matches;
  }

  array<int, 4> square_matrix(const array<int, 4>& A) const {
    return {int((1LL * A[0] * A[0] + 1LL * A[1] * A[2]) % mod),
            int((1LL * A[0] * A[1] + 1LL * A[1] * A[3]) % mod),
            int((1LL * A[2] * A[0] + 1LL * A[3] * A[2]) % mod),
            int((1LL * A[2] * A[1] + 1LL * A[3] * A[3]) % mod)};
  }

 public:
  int numberOfWays(const string s, const string t, const long long k) {
    const vector<int> matches = kmp(s + s, t);

    if (matches.empty()) return 0;

    const int match_count =
        ranges::count_if(matches, [&s](const size_t x) { return x < s.size(); });

    const int n = s.size();

    array<int, 4> T{
        n - match_count - 1,
        match_count,
        n - match_count,
        match_count - 1,
    };

    array<long long, 2> result{0, 1};

    for (long long exp = k; exp > 0; exp >>= 1) {
      if (exp & 1) {
        result = {T[0] * result.front() + T[1] * result.back(),
                  T[2] * result.front() + T[3] * result.back()};
        result[0] %= mod;
        result[1] %= mod;
      }

      T = square_matrix(T);
    }

    return result[matches.front() == 0];
  }
};
