#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N;
ll M, nums[1'000'001];

bool possible(ll height) {
  ll total = 0;

  for (int i = 0; i < N; i++) {
    if (height < nums[i]) total += nums[i] - height;
    if (total >= M) return true;
  }

  return false;
}

int main() {
  cin >> N >> M;

  for (int i = 0; i < N; i++) scanf("%lld", &nums[i]);

  ll left = 0;
  ll right = 1'000'000'001;

  while (left < right) {
    ll mid = (left + right) / 2;

    if (possible(mid))
      left = mid + 1;
    else
      right = mid;
  }

  cout << left - 1 << endl;
}
