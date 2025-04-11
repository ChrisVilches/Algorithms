#include <bits/stdc++.h>
using namespace std;

class Solution {
  const string chars = "ACGT";

  int to_bin(const char c) const {
    return find(chars.begin(), chars.end(), c) - chars.begin();
  }

 public:
  vector<string> findRepeatedDnaSequences(const string s) {
    unordered_map<int, int> freq;

    int curr = 0;

    for (size_t i = 0; i < min(s.size(), static_cast<size_t>(10)); i++) {
      curr += to_bin(s[i]) << (2 * i);
    }

    freq[curr]++;

    for (size_t i = 10; i < s.size(); i++) {
      curr /= 4;
      curr += to_bin(s[i]) << (2 * 9);
      freq[curr]++;
    }

    vector<string> ans;

    for (const auto& [str, f] : freq) {
      if (f == 1) continue;

      ans.emplace_back();

      for (int i = 0, val = str; i < 10; i++, val /= 4) {
        ans.back() += chars[val & 3];
      }
    }

    return ans;
  }
};
