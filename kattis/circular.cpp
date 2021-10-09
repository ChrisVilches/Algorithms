#include <bits/stdc++.h>

using namespace std;
#define MAX_N 1000007
enum {
  S,
  E
};
int n, num;
char c;

int gen_status[MAX_N] = {0};
int marker[MAX_N] = {0};
int gen_type[MAX_N] = {0};
int closed_values[MAX_N] = {0};

// NOTE: Instead of "closed" maybe an "open" would be better? Then I just compute the difference.
//        This is prolly easier to implement

int main(){
  cin >> n;

  for(int i=0; i<n; i++){
    scanf(" %c%d ", &c, &num);
    marker[i] = c == 's' ? S : E;
    gen_type[i] = num;
  }

  int closed = 0;

  for(int pos=0; pos<n; pos++){
    int i = gen_type[pos];
    int m = marker[pos];

    if(closed < 0) throw runtime_error("closed < 0");

    if(m == S){
      if(gen_status[i] == 0){
        if(closed > 0){
          closed--;
        }
      }
      gen_status[i]++;
    } else if(m == E) {
      if(gen_status[i] > 0){
        gen_status[i]--;
        if(gen_status[i] == 0){
          closed++;
        }
      }
    }

    if(closed < 0) throw runtime_error("closed < 0");
  }

  for(int pos=0; pos<n; pos++){
    int i = gen_type[pos];
    int m = marker[pos];

    closed_values[pos] = closed;
    if(gen_status[i] < 0) throw runtime_error("asd");
    if(closed < 0) throw runtime_error("closed < 0");

    if(m == S){
      if(gen_status[i] == 0){
        if(closed > 0)
          closed--;
      }
      gen_status[i]++;
      
    } else if(m == E) {
      if(gen_status[i] > 0){
        gen_status[i]--;
        if(gen_status[i] == 0){
          closed++;
        }
      }
    }

    if(gen_status[i] < 0) throw runtime_error("asd");
    if(closed < 0) throw runtime_error("closed < 0");
  }

  int highest = 0;
  int highest_pos = 0;

  for(int pos=0; pos<n; pos++){
    if(closed_values[pos] > highest){
      highest = closed_values[pos];
      highest_pos = pos;
    }
  }

  printf("%d %d\n", highest_pos+1, highest);
}
