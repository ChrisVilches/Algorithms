#include <bits/stdc++.h>
using namespace std;

class Solution {
  string ans;
  map<char, int> desired_freq;

  bool satisfies(const map<char, int>& freq) {
    for (const auto& [k, v] : desired_freq) {
      if (!freq.count(k) || freq.at(k) < desired_freq[k]) {
        return false;
      }
    }
    return true;
  }

  bool window(const string& s, const int n) {
    map<char, int> freq;
    for (int i = 0; i < n - 1; i++) {
      freq[s[i]]++;
    }
    for (size_t i = 0; i + n - 1 < s.size(); i++) {
      freq[s[i + n - 1]]++;
      if (satisfies(freq)) {
        ans = s.substr(i, n);
        return true;
      }
      freq[s[i]]--;
    }
    return false;
  }

 public:
  string minWindow(string s, string t) {
    int lo = 1;
    int hi = s.size();
    for (const char c : t) desired_freq[c]++;

    while (lo <= hi) {
      const int mid = (lo + hi) / 2;
      if (window(s, mid)) {
        hi = mid - 1;
      } else {
        lo = mid + 1;
      }
    }
    return ans;
  }
};
