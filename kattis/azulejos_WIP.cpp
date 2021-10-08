#include <bits/stdc++.h>

using namespace std;

struct Tile {
  int price, height, id;
};

int n;

// NOTE: Partial sort -> The objects in the range [first,last) are modified.

void sort_tiles_by_prices(vector<Tile> &v){
  sort(v.begin(), v.end(), [](Tile &a, Tile &b){
    return a.price <= b.price;
  });
}

void sort_tiles_by_height(vector<Tile> &v, int a, int b){
  std::partial_sort(v.begin(), v.begin() + a, v.begin() + b, [](Tile &a, Tile &b){
    return a.height > b.height;
  });
}

void read_tiles(vector<Tile> &v){
  for(int i=0; i<n; i++){
    Tile t;
    t.id = i + 1;
    cin >> t.price;
    v.push_back(t);
  }
  for(int i=0; i<n; i++){
    cin >> v[i].height;
  }
}

int main(){
  cin >> n;

  vector<Tile> back, front;
  read_tiles(back);
  read_tiles(front);
  sort_tiles_by_prices(back);
  sort_tiles_by_prices(front);

  int sorted_idx = 0;
  int bp = back[0].price;
  int fp = front[0].price;
  int pre_b = 0;
  int pre_f = 0;

  int j = 0;

  for(int i=0; i<=n; i++){

    if(i == n){
      printf(".i stopped at %d ... range [%d, %d)\n", n, pre_b, n);
    } else {
      if(back[i].price == bp) continue;
      printf("i stopped at %d ... range [%d, %d)\n", i, pre_b, i);
      bp = back[i].price;
    }
    pre_b = i;

    /*
         0 1 2 3 4 5
Back
prices:  1 1 1 2 3
heights: 5 5 5 5 5

Front
prices:  1 2 2 2 2
heights: 5 5 5 5 5

0, 0
1, 2
3, 3
4, 4

i [0, 3)
j [0, 1)
j [1, 5)
i [3, 4)
i [4, 5) maybe
    */

    if(i == n || j == n){
      printf(".-------- Fixing heights in range [%d, %d] -------------\n", sorted_idx, n-1);
      break;
    }

    printf("Starting a new J loop. i=%d j=%d\n", i, j);
    for(; j<=n; j++){
      if(j == i){
        printf("*-------- Fixing heights in range [%d, %d] ----------------\n", sorted_idx, min(i, j)-1);
        sorted_idx = min(i, j);
        //printf("i == j ... %d == %d\n",i ,j);
        break;
      }

      if(front[j].price != fp){
        
        fp = front[j].price;
        printf("j stopped at %d ... range [%d, %d]\n", j, pre_f, j-1);
        pre_f = j;

        printf("-------- Fixing heights in range [%d, %d] ----------------\n", sorted_idx, min(i, j)-1);
        sorted_idx = min(i, j);
        // should sort here
        /*if(i < j){
          printf("*Fixing heights in range [%d, %d] ----------------\n", sorted_idx, min(i, j)-1);
          sorted_idx = min(i, j);
          break;
        }*/
      }
    }
    //printf("ended loop\n");

    //printf("sorting from %d to %d\n", sorted_idx, min(i, j-1));
    //printf("after sorting %c needs to catch up\n", increasing);
    //sort_tiles_by_height(back, sorted_idx, min(i, j-1));
    //sort_tiles_by_height(front, sorted_idx, min(i, j-1));
    //sorted_idx = min(i, j-1) + 1;
  }

  for(int i=0; i<n; i++){
    if(back[i].height <= front[i].height){
      cout << "impossible" << endl;
      return 0;
    }
  }

  for(int i=0; i<n; i++){
    cout << back[i].id << " ";
  }
  cout << endl;

  for(int i=0; i<n; i++){
    cout << front[i].id << " ";
  }
  cout << endl;
}
