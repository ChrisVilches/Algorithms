#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int nums[100'000];
int psum[100'001];

ll sum_range(int l, int r) { return (ll)psum[r + 1] - (ll)psum[l]; }

int main() {
  int N, Q;
  cin >> N;

  psum[0] = 0;
  for (int i = 0; i < N; i++) {
    cin >> nums[i];
    psum[i + 1] = psum[i] + nums[i];
  }

  cin >> Q;

  for (int i = 0; i < Q; i++) {
    int a, b;
    cin >> a >> b;
    cout << sum_range(a, b) << endl;
  }
}
