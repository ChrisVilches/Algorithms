#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

vector<int> find_occurrences(string s, string sub) {
  vector<int> ret;

  int pos = s.find(sub, 0);

  while (pos != string::npos) {
    ret.push_back(pos);
    pos = s.find(sub, pos + 1);
  }

  return ret;
}

int main() {
  string s;
  cin >> s;

  ll ans = 0;

  vector<int> heavy = find_occurrences(s, "heavy");
  vector<int> metal = find_occurrences(s, "metal");

  for (int i = 0, j = 0; i < (int)heavy.size(); i++) {
    for (; j < (int)metal.size(); j++) {
      if (heavy[i] < metal[j]) {
        ans += metal.size() - j;
        break;
      }
    }
  }

  cout << ans << endl;
}
