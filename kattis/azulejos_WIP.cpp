#include <bits/stdc++.h>

using namespace std;

struct Tile {
  int price, height, id;
};

int n;

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
  int j = 0;
  char increasing = 'i';
  for(int i=0; i<n; i++){

    if(i == n - 1 || back[i+1].price != bp){
      bp = back[i+1].price;
      increasing = 'j';
    } else {
      continue;
    }

    printf("i stopped at %d\n", i);
    
    
    for(; j<n; j++){
      if(front[j].price != fp){
        fp = front[j].price; 
        //if(j < n-1) j++;
        printf("j stopped at %d\n", j-1);
        break;
      }
    }

    increasing = i <= j ? 'i' : 'j';

    // TODO: This two pointers shit is fucked. it should be a lot simpler
    

  printf("sorting from %d to %d\n", sorted_idx, min(i, j-1));
  printf("after sorting %c needs to catch up\n", increasing);
    sort_tiles_by_height(back, sorted_idx, min(i, j-1));
    sort_tiles_by_height(front, sorted_idx, min(i, j-1));
    sorted_idx = min(i, j-1) + 1;
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
