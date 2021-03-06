#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct State {
  int len, link;
  map<char, int> next;
};

struct SuffixAutomaton {
  vector<State> st;
  int sz = 1, last = 0;

  SuffixAutomaton(string& s) {
    st.assign(s.size() * 2, State());
    st[0].len = 0;
    st[0].link = -1;
    for (char c : s) extend(c);
  }

  void extend(char c) {
    int cur = sz++, p = last;
    st[cur].len = st[last].len + 1;
    while (p != -1 && !st[p].next.count(c)) st[p].next[c] = cur, p = st[p].link;
    if (p == -1) {
      st[cur].link = 0;
    } else {
      int q = st[p].next[c];
      if (st[p].len + 1 == st[q].len)
        st[cur].link = q;
      else {
        int clone = sz++;
        st[clone].len = st[p].len + 1;
        st[clone].next = st[q].next;
        st[clone].link = st[q].link;
        while (p != -1 && st[p].next[c] == q)
          st[p].next[c] = clone, p = st[p].link;

        st[q].link = st[cur].link = clone;
      }
    }
    last = cur;
  }
};

ll dfs(SuffixAutomaton& sa, int i) {
  if (sa.st[i].next.empty()) return 1;

  ll count = 1;

  for (auto it = sa.st[i].next.begin(); it != sa.st[i].next.end(); it++)
    count += dfs(sa, it->second);

  return count;
}

ll distinct_substrs(string& s) {
  SuffixAutomaton sa(s);
  return dfs(sa, 0) - 1;
}

int main() {
  int T;
  cin >> T;

  while (T--) {
    string s;
    cin >> s;
    cout << distinct_substrs(s) << endl;
  }
}
