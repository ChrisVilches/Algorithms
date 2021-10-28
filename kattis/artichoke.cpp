#include <bits/stdc++.h>

using namespace std;

#define MAX 1000010

int p, a, b, c, d, n;
double nums[MAX];
int larger[MAX];

double price(int k) {
  double first = sin(a * k + b);
  double second = cos(c * k + d);
  return p * (first + second + 2);
}

int main() {
  cin >> p >> a >> b >> c >> n;

  for (int i = 0; i < n; i++) nums[i] = price(i + 1);

  larger[0] = 0;

  for (int i = 1; i < n; i++) {
    larger[i] = i - 1;
    while (nums[larger[i]] < nums[larger[larger[i]]] && i > 0)
      larger[i] = larger[larger[i]];

    if (nums[i] > nums[larger[i]]) larger[i] = -1;
  }

  double diff = 0;
  for (int i = 0; i < n; i++)
    if (larger[i] != -1) diff = max(diff, nums[larger[i]] - nums[i]);

  printf("%.9f\n", diff);
}
