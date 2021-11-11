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

pair<int, int> longest_common_substring(string s, string t) {
  SuffixAutomaton sa(s);
  int v = 0, l = 0, best = 0, bestpos = 0;
  for (int i = 0; i < (int)t.size(); i++) {
    while (v && !sa.st[v].next.count(t[i])) {
      v = sa.st[v].link;
      l = sa.st[v].len;
    }
    if (sa.st[v].next.count(t[i])) {
      v = sa.st[v].next[t[i]];
      l++;
    }
    if (l > best) {
      best = l;
      bestpos = i;
    }
  }
  return make_pair(bestpos - best + 1, best);
}

int main() {
  string s, t;
  cin >> s >> t;
  auto [start_pos, length] = longest_common_substring(s, t);

  string longest = t.substr(start_pos, length);

  cout << longest.size() << endl;
}
