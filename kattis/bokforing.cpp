#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1'000'001

int nums[MAX_N], last_update[MAX_N];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  memset(last_update, -1, sizeof last_update);

  int N, Q;
  cin >> N >> Q;

  int curr_restart_value = -1;
  int last_restart = -1;

  string op;

  for (int q = 0; q < Q; q++) {
    int a, b;
    cin >> op;

    switch (op[0]) {
      case 'S':  // SET
        cin >> a >> b;
        last_update[a] = q;
        nums[a] = b;
        break;
      case 'P':  // PRINT
        cin >> a;
        cout << (last_update[a] < last_restart ? curr_restart_value : nums[a]) << '\n';
        break;
      case 'R':  // RESTART
        cin >> a;
        curr_restart_value = a;
        last_restart = q;
        break;
    }
  }
}
