#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

char read_char() {
  char c;
  while (scanf("%c", &c) && !(c == '.' || c == 'H' || c == 'S'))
    ;
  return c;
}

int main() {
  int N;
  cin >> N;
  vector<pii> house, spy;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      char c = read_char();
      if (c == 'S') {
        spy.push_back(make_pair(i, j));
      } else if (c == 'H') {
        house.push_back(make_pair(i, j));
      }
    }
  }

  int ans = 0;

  for (pii s : spy) {
    int min_dist = INT_MAX;
    for (pii h : house) {
      int dist = abs(s.first - h.first) + abs(s.second - h.second);
      min_dist = min(min_dist, dist);
    }
    ans = max(ans, min_dist);
  }

  cout << ans << endl;
}
