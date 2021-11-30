#include <bits/stdc++.h>

using namespace std;

int nums[1000001];

int main() {
  int N;
  scanf("%d", &N);

  for (int i = 0; i < N; i++) {
    scanf("%d", &nums[i]);
  }

  sort(nums, nums + N);

  for (int i = 0; i < N; i++) {
    printf("%d\n", nums[i]);
  }
}
