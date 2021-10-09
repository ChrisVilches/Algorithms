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
  unordered_set<int> genes;

  for(int i=0; i<n; i++){
    scanf(" %c%d ", &c, &num);
    marker[i] = c == 's' ? S : E;
    gen_type[i] = num;
  }

  for(int pos=0; pos<n; pos++){
    int i = gen_type[pos];
    int m = marker[pos];
    if(m == S){
      gen_status[i]++;
    } else if(m == E) {
      gen_status[i]--;
    }
  }
  for(int pos=0; pos<n; pos++){
    int i = gen_type[pos];
    if(gen_status[i] == 0)
      genes.insert(i);
  }
  memset(gen_status, 0, sizeof gen_status);

  //int open = 0;
  unordered_set<int> open_genes;
  for(int pos=0; pos<n; pos++){
    int i = gen_type[pos];
    int m = marker[pos];
    if(genes.find(i) == genes.end()) continue;

    if(m == S){
      open_genes.insert(i);
      if(gen_status[i] == 0){
        open_genes.insert(i);
      }
      gen_status[i]++;
    } else if(m == E) {
      if(gen_status[i] > 0){
        gen_status[i]--;
        if(gen_status[i] == 0){
          open_genes.erase(i);
          if(genes.find(i) == genes.end()) throw runtime_error("woooo");
        }
      }
    }
  }

  for(int pos=0; pos<n; pos++){
    int i = gen_type[pos];
    int m = marker[pos];

    closed_values[pos] = genes.size() - open_genes.size();
    //if(gen_status[i] < 0) throw runtime_error("asd");
    if(genes.find(i) == genes.end()) continue;

    if(m == S){
      open_genes.insert(i);
      gen_status[i]++;
      
    } else if(m == E) {
      if(gen_status[i] > 0){
        gen_status[i]--;
        if(gen_status[i] == 0){
          open_genes.erase(i);
          if(genes.find(i) == genes.end()) throw runtime_error("woooo");
        }
      }
    }

    //if(gen_status[i] < 0) throw runtime_error("asd");
  }

  int highest = 0;
  int highest_pos = 0;

  for(int pos=0; pos<n; pos++){
    if(closed_values[pos] > highest){
      highest = closed_values[pos];
      highest_pos = pos;
    }
  }

  // e1 s2 e2 s1 
  // e1 s2 e2 s1 e1 s2 e2 s1 
  //    |---|
  //          |---|

  printf("%d %d\n", highest_pos+1, highest);
}
