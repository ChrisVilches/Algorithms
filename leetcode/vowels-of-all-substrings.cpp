#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  long long countVowels(const string word) {
    const int n = word.size();

    long long ans = 0;

    for (int i = 0; i < n; i++) {
      const char c = word[i];
      const long long is_vowel = c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
      ans += is_vowel * (n - i) * (i + 1);
    }

    return ans;
  }
};
