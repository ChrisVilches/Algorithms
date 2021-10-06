#include <bits/stdc++.h>

using namespace std;

int nums[100000];

int n, q;
int main(){
  scanf("%d %d", &n, &q);
  for(int i=0; i<n; i++) scanf("%d", &nums[i]);

  while(q--){
    int x;
    scanf("%d", &x);
    int left = 0;
    int right = n;
    int idx = -1;
    while(left < right){
      int mid = (left + right)/2;
      if(nums[mid] >= x){
        right = mid;
        if(nums[mid] == x) idx = mid;
      } else {
        left = mid + 1;
      }
    }
    printf("%d\n", idx);
  }
}
