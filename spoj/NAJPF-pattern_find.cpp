#include <bits/stdc++.h>
using namespace std;

void compute_lps(string pat, int M, vector<int>& lps) {
  int len = 0, i = 1;
  lps[0] = 0;

  while (i < M) {
    if (pat[i] == pat[len]) {
      len++;
      lps[i] = len;
      i++;
    } else {
      if (len != 0)
        len = lps[len - 1];
      else {
        lps[i] = 0;
        i++;
      }
    }
  }
}

vector<int> kmp(string txt, string pat) {
  int M = pat.size();
  int N = txt.size();
  int i = 0, j = 0;
  vector<int> matches;
  vector<int> lps(N);

  compute_lps(pat, M, lps);

  while (i < N) {
    if (pat[j] == txt[i]) {
      j++;
      i++;
    }

    if (j == M) {
      matches.push_back(i - j);
      j = lps[j - 1];
    } else if (i < N && pat[j] != txt[i]) {
      if (j != 0)
        j = lps[j - 1];
      else
        i = i + 1;
    }
  }

  return matches;
}

void solve() {
  string str, pattern;
  cin >> str >> pattern;

  vector<int> matches = kmp(str, pattern);

  if (matches.empty()) {
    cout << "Not Found" << endl << endl;
    return;
  } else {
    cout << matches.size() << endl;
  }

  for (int m : matches) {
    cout << m + 1 << ' ';
  }
  cout << endl << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
