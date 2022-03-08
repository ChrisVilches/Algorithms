#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> convert_start(const vector<ll>& nums) {
  vector<ll> res;
  const int N = nums.size();
  int start = -1;

  for (int i = 0; i < N; i++)
    if (start == -1 || nums[i] > start) start = i;

  for (int i = start, iter = N; iter--; i++) res.push_back(nums[i % N]);

  return res;
}

ll cost(vector<ll> nums, const ll target) {
  const int N = nums.size();
  ll cost = 0;
  ll surplus = 0;

  nums = convert_start(nums);

  while (true) {
    for (int i = 0; i < N; i++) {
      ll& curr = nums[i];

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

    bool ok = true;

    for (int i = 0; i < N; i++)
      if (nums[i] != target) ok = false;

    if (ok) break;
  }

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
