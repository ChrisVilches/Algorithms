#include <bits/stdc++.h>

using namespace std;

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
    if (p == -1)
      st[cur].link = 0;
    else {
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

int pictures(SuffixAutomaton& sa, string& name) {
  int ans = 0;
  int i = 0;

  while (i < (int)name.size()) {
    char c = name[i];

    if (!sa.st[0].next.count(c)) return -1;

    ans++;
    int curr = 0;

    while (sa.st[curr].next.count(c) && i < (int)name.size()) {
      curr = sa.st[curr].next[c];
      c = name[++i];
    }
  }

  return ans;
}

int main() {
  int N;
  string city;
  cin >> city >> N;

  SuffixAutomaton sa(city);

  while (N--) {
    string name;
    cin >> name;
    cout << pictures(sa, name) << endl;
  }
}
