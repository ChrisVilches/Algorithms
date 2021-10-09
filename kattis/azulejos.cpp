#include <bits/stdc++.h>

using namespace std;

struct Tile {
  int price, height, id;
  bool operator <(const Tile& t) const{
    if(height == t.height){
      return id < t.id;
    }
    return height < t.height;
  }
};

int n;

void read_tiles(map<int, set<Tile>> &row){
  vector<Tile> tiles;
  for(int i=0; i<n; i++){
    Tile t;
    t.id = i + 1;
    scanf("%d", &t.price);
    tiles.push_back(t);
  }
  for(int i=0; i<n; i++){
    scanf("%d", &tiles[i].height);
    row[tiles[i].price].insert(tiles[i]);
  }
}

int main(){
  cin >> n;
  map<int, set<Tile>> back, front;

  read_tiles(back);
  read_tiles(front);

  vector<Tile> back_result, front_result;

  for(int i=0; i<n; i++){
    set<Tile>& back_set = back.begin()->second;
    set<Tile>& front_set = front.begin()->second;
    set<Tile>::iterator add_to_back, add_to_front;

    if(back_set.size() >= front_set.size()){
      add_to_front = front_set.begin();

      // TODO: This has to be done because of some issues with the comparator (can be improved/simplified).
      Tile t = *add_to_front;
      t.id = INT_MAX;
      add_to_back = back_set.upper_bound(t);
    } else {
      add_to_back = back_set.begin();
      Tile t = *add_to_back;
      t.id = -1;
      add_to_front = front_set.lower_bound(t);

      if(add_to_front == front_set.begin()){
        cout << "impossible" << endl;
      }

      --add_to_front;
    }

    if((add_to_back == back_set.end()) || (add_to_front == front_set.end())){
      cout << "impossible" << endl;
      return 0;
    }

    back_result.push_back(*add_to_back);
    front_result.push_back(*add_to_front);

    back_set.erase(add_to_back);
    front_set.erase(add_to_front);

    if(back_set.size() == 0) back.erase(back.begin());
    if(front_set.size() == 0) front.erase(front.begin());
  }

  for(int i=0; i<n; i++){
    printf("%d ", back_result[i].id);
  }

  printf("\n");

  for(int i=0; i<n; i++){
    printf("%d ", front_result[i].id);
  }

  printf("\n");
}
