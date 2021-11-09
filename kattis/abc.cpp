#include <bits/stdc++.h>

using namespace std;

int main() {
  int nums[3];
  char c[3];
  scanf("%d %d %d ", &nums[0], &nums[1], &nums[2]);
  scanf("%c %c %c", &c[0], &c[1], &c[2]);

  sort(nums, nums + 3);

  for (int i = 0; i < 3; i++) cout << nums[c[i] - 'A'] << ' ';
}
