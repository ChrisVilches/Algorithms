#include <bits/stdc++.h>

using namespace std;

int main() {
  int N;
  while (scanf("%d", &N) == 1) {
    unordered_map<int, int> sequences;
    int ans = 1;

    for (int i = 0; i < N; i++) {
      int num;
      cin >> num;

      if (sequences.count(num - 1)) {
        int count = sequences[num - 1];
        sequences[num] = count + 1;
      } else if (!sequences.count(num)) {
        sequences[num] = 1;
      }
      ans = max(ans, sequences[num]);
    }

    cout << ans << endl;
  }
}
