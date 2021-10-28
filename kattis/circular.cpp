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
int closed[MAX_N] = {0}; // Count how many genes are closed at each position (i.e. the Si -> Ei are balanced)

int main(){
  cin >> n;
  // Skip genes that are not balanced (i.e. "S" count is different from "E" count in the sequence)
  unordered_set<int> balanced_genes;
  unordered_set<int> open_genes;

  for(int i=0; i<n; i++){
    scanf(" %c%d ", &c, &num);
    marker[i] = c == 's' ? S : E;
    gen_type[i] = num;
  }

  // Check which gene types are actually balanced.
  for(int pos=0; pos<n; pos++){
    int i = gen_type[pos];
    int m = marker[pos];
    gen_status[i] += m == S ? 1 : -1;
    if(gen_status[i] == 0)
      balanced_genes.insert(i);
    else
      balanced_genes.erase(i);
  }

  int iter = 2;

  while(iter--){
    for(int pos=0; pos<n; pos++){
      int i = gen_type[pos];
      int m = marker[pos];
      closed[pos] = balanced_genes.size() - open_genes.size();
      if(balanced_genes.find(i) == balanced_genes.end()) continue;

      if(m == S){
        open_genes.insert(i);
        gen_status[i]++;
      } else {
        // In the first pass, some "end" values might not be associated with any "start".
        // Therefore check first.
        if(gen_status[i] > 0){
          gen_status[i]--;
          if(gen_status[i] == 0)
            open_genes.erase(i);
        }
      }
    }
  }

  int highest = 0, highest_pos = 0;

  for(int pos=0; pos<n; pos++){
    if(closed[pos] > highest){
      highest = closed[pos];
      highest_pos = pos;
    }
  }

  printf("%d %d\n", highest_pos+1, highest);
}
