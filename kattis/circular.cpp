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

int main(){
  cin >> n;
  set<int> genes;

  for(int i=0; i<n; i++){
    scanf(" %c%d ", &c, &num);
    marker[i] = c == 's' ? S : E;
    gen_type[i] = num;
  }

  

  int open = 0;
  for(int pos=0; pos<n; pos++){
    int i = gen_type[pos];
    int m = marker[pos];

    if(open < 0) throw runtime_error("open < 0");

    if(m == S){
      if(gen_status[i] == 0){
        
        genes.insert(i);
        open++;
      }
      gen_status[i]++;
    } else if(m == E) {
      if(gen_status[i] > 0){
        gen_status[i]--;
        if(gen_status[i] == 0){
          open--;
        }
      }
    }

    if(open < 0) throw runtime_error("open < 0");
  }

  int total_genes = genes.size();

  for(int pos=0; pos<n; pos++){
    int i = gen_type[pos];
    int m = marker[pos];

    closed_values[pos] = total_genes - open;
    if(gen_status[i] < 0) throw runtime_error("asd");
    if(open < 0) throw runtime_error("open < 0");

    if(m == S){
      if(gen_status[i] == 0){
        open++;
      }
      gen_status[i]++;
      
    } else if(m == E) {
      if(gen_status[i] > 0){
        gen_status[i]--;
        if(gen_status[i] == 0){
          open--;
        }
      }
    }

    if(gen_status[i] < 0) throw runtime_error("asd");
    if(open < 0) throw runtime_error("open < 0");
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
