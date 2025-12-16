#include <bits/stdc++.h>
using namespace std;

class Solution {
  bool have_common(const unordered_set<int>& a, const unordered_set<int>& b) const {
    for (const int x : a) {
      if (b.count(x)) return true;
    }

    return false;
  }

 public:
  int minimumTeachings(const int n, const vector<vector<int>>& languages_input,
                       const vector<vector<int>>& friendships) {
    int ans = INT_MAX;

    vector<unordered_set<int>> languages;

    for (size_t i = 0; i < languages_input.size(); i++) {
      const vector<int>& langs = languages_input[i];
      languages.emplace_back(langs.begin(), langs.end());
    }

    for (int lang = 1; lang <= n; lang++) {
      unordered_set<int> teach;

      for (const vector<int>& friendship : friendships) {
        const int u = friendship.front() - 1;
        const int v = friendship.back() - 1;

        if (have_common(languages[u], languages[v])) continue;

        for (const int p : {u, v}) {
          if (languages[p].count(lang) || teach.count(p)) continue;
          teach.emplace(p);
        }
      }

      ans = min(ans, static_cast<int>(teach.size()));
    }

    return ans;
  }
};
