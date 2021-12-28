#include <bits/stdc++.h>

#include <ext/rope>
using namespace std;
using namespace __gnu_cxx;

vector<crope> strings;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    strings.push_back(crope(s.c_str()));
  }

  for (int i = 0; i < N - 1; i++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;

    strings[a] = strings[a] + strings[b];
    strings[b] = crope();
  }

  for (crope& c : strings) {
    if (c.empty()) continue;

    cout << c << endl;
    break;
  }
}
