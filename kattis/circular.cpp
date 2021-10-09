#include <bits/stdc++.h>

using namespace std;
#define MAX_N 1000007
enum {
  S = 69,
  E = 71
};
int n;

int gen_status[MAX_N];
int marker[MAX_N];
int gen_type[MAX_N];
int locs[MAX_N];
int found[MAX_N];
int prev_pos[MAX_N];
int first[MAX_N];
int closed_values[MAX_N];

int scores[MAX_N * 2];

int main(){
  set<int> visited; // unordered_set for making it faster.
  memset(gen_status, 0, sizeof gen_status);
  memset(locs, 0, sizeof locs);
  memset(found, 0, sizeof found);
  memset(prev_pos, 0, sizeof prev_pos);

  cin >> n;

  char c;
  int num;
  for(int i=0; i<n; i++){
    scanf(" %c%d ", &c, &num);
    if(c == 's'){
      marker[i] = S;
    } else if(c == 'e'){
      marker[i] = E;
    } else {
      printf("MARKER TYPE WRONG: %d\n", c);
      throw runtime_error("bad input marker type");
    }

    gen_type[i] = num;

    //printf("char %c , num %d\n", c, num);
  }

  int closed = 0;
  

  for(int pos=0; pos<n; pos++){
    int i = gen_type[pos];
    int m = marker[pos];

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
    } else {
      throw runtime_error("bad marker");
    }
  }

  //printf("after first pass\n");
  for(int pos=0; pos<n; pos++){
    int i = gen_type[pos];
    if(visited.find(i) != visited.end())
      continue;
    visited.insert(i);
   // printf("status of i=%d : %d\n", i, gen_status[i]);

  }
  //printf("\n");

  for(int pos=n; pos<(n*2); pos++){
    int i = gen_type[pos-n];
    int m = marker[pos-n];

    //printf("closed at pos %d --> %d\n",pos, closed);
    closed_values[pos] = closed;

    if(m == S){
      if(gen_status[i] == 0){
        closed--;
      }
      gen_status[i]++;
      
    } else if(m == E) {
      gen_status[i]--;
      if(gen_status[i] == 0){
        closed++;
      }
      
    } else {
      throw runtime_error("bad marker");
    }

    // e1 e1 s1 e2 s1 s2 e42 e1 s1
    // e1 e1 s1 e2 s1 s2 e42 e1 s1 e1 e1 s1 e2 s1 s2 e42 e1 s1
    //       |-------------------------|    
    //                 |---------------------|

    
  }

  int highest = INT_MIN;
  int highest_pos = 0;

  for(int pos=n; pos<(n*2); pos++){
    if(closed_values[pos] > highest){
      highest = closed_values[pos];
      highest_pos = pos - n;
    }
  }


  printf("%d %d\n", highest_pos+1, highest);
}
