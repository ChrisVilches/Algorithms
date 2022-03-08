#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cost(vector<ll> nums, const ll target) {
  ll cost = 0;
  ll surplus = 0;

solve:

  for (ll& curr : nums) {
    cost += surplus;

    if (curr < target) {
      const ll moved = min(surplus, target - curr);
      curr += moved;
      surplus -= moved;
    } else if (curr > target) {
      surplus += curr - target;
      curr = target;
    }
  }

  for (ll n : nums)
    if (n != target) goto solve;

  return cost;
}

int main() {
  int N;

  while (cin >> N) {
    vector<ll> nums(N);

    ll total = 0;

    for (int i = 0; i < N; i++) {
      cin >> nums[i];
      total += nums[i];
    }

    const ll target = total / N;

    ll cost1 = cost(nums, target);

    reverse(nums.begin(), nums.end());

    ll cost2 = cost(nums, target);

    cout << min(cost1, cost2) << endl;
  }
}
