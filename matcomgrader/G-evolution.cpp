#include <bits/stdc++.h>
using namespace std;

int nums[1007][2];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  cin >> N >> M;

  for (int n = 1; n <= N; n++) {
    cin >> nums[n][0];
  }

  int iter = 0;

  while (M--) {
    for (int n = 1; n <= N; n++) {
      int prev = nums[n - 1][iter];
      int next = nums[n + 1][iter];

      nums[n][!iter] = prev != next;
    }

    iter = !iter;
  }

  for (int i = 1; i <= N; i++) {
    cout << nums[i][iter] << " ";
  }
  cout << endl;
}
