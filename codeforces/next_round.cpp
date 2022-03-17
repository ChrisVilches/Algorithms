#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K;

  cin >> N >> K;

  vector<int> scores(N);

  for (int i = 0; i < N; i++) {
    cin >> scores[i];
  }

  int ans = 0;

  for (int i = 0; i < N; i++) {
    ans += scores[i] > 0 && scores[K - 1] <= scores[i];
  }

  cout << ans << endl;
}
