#include <bits/stdc++.h>
using namespace std;

int nums[1001];

int main() {
  int N;
  cin >> N;

  for (int i = 0; i < N; i++) cin >> nums[i];

  sort(nums, nums + N);

  int first = nums[0];
  int curr = nums[0];

  vector<pair<int, int>> pairs;

  for (int i = 1; i <= N; i++) {
    if (i == N || nums[i] != curr + 1) {
      pairs.push_back({first, curr});

      if (i < N) first = curr = nums[i];
      continue;
    }

    if (nums[i] == curr + 1) curr = nums[i];
  }

  for (pair<int, int> p : pairs)
    if (p.second - p.first == 1)
      printf("%d %d ", p.first, p.second);
    else if (p.first == p.second)
      printf("%d ", p.first);
    else
      printf("%d-%d ", p.first, p.second);

  putchar('\n');
}
