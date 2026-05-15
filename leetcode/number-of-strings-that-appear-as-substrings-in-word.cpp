#include <bits/stdc++.h>
using namespace std;

class SuffixAutomaton {
  struct State {
    int len, link;
    map<char, int> next;
  };

  int sz = 1, last = 0;

  void extend(const char c) {
    const int cur = sz++;
    int p = last;
    st[cur].len = st[last].len + 1;
    while (p != -1 && !st[p].next.count(c)) st[p].next[c] = cur, p = st[p].link;
    if (p == -1) {
      st[cur].link = 0;
    } else {
      const int q = st[p].next[c];
      if (st[p].len + 1 == st[q].len)
        st[cur].link = q;
      else {
        const int clone = sz++;
        st[clone].len = st[p].len + 1;
        st[clone].next = st[q].next;
        st[clone].link = st[q].link;
        while (p != -1 && st[p].next[c] == q) st[p].next[c] = clone, p = st[p].link;

        st[q].link = st[cur].link = clone;
      }
    }
    last = cur;
  }

 public:
  vector<State> st;

  SuffixAutomaton(const string& s) {
    st.assign(s.size() * 2, State());
    st[0].len = 0;
    st[0].link = -1;
    for (const char c : s) extend(c);
  }
};

class Solution {
  bool has_pattern(const SuffixAutomaton& sa, const string& pattern) const {
    int cur = 0;
    for (const char c : pattern) {
      if (!sa.st[cur].next.count(c)) return false;
      cur = sa.st[cur].next.at(c);
    }

    return true;
  }

 public:
  int numOfStrings(const vector<string>& patterns, const string word) {
    SuffixAutomaton sa(word);
    int ans = 0;

    for (const string& p : patterns) {
      ans += has_pattern(sa, p);
    }

    return ans;
  }
};
