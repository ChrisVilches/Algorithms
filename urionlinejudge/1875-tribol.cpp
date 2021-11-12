#include <bits/stdc++.h>

using namespace std;

void solve() {
  int n;
  cin >> n;

  pair<int, string> goals[3] = {make_pair(0, string("red")),
                                make_pair(0, string("green")),
                                make_pair(0, string("blue"))};

  while (n--) {
    char a, b;
    cin >> a >> b;

    int score = 0;

    switch (a) {
      case 'R':
        goals[0].first += b == 'B' ? 1 : 2;
        break;
      case 'G':
        goals[1].first += b == 'R' ? 1 : 2;
        break;
      case 'B':
        goals[2].first += b == 'G' ? 1 : 2;
    }
  }

  sort(goals, goals + 3);

  if (goals[0].first == goals[1].first && goals[1].first == goals[2].first) {
    cout << "trempate" << endl;
  } else if (goals[0].first != goals[1].first &&
             goals[1].first == goals[2].first) {
    cout << "empate" << endl;
  } else {
    cout << goals[2].second << endl;
  }
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
