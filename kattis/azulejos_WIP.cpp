#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

struct Tile {
  int price, height, id;
  bool operator >(const Tile& t) const{
    cout << "IS THIS SHIT EVEN EXECUTING!? (>)" << endl;
    if(id == t.id) return false;
    return height > t.height;
  }

  bool operator ==(const Tile& t) const{
    return id == t.id;
  }

  bool operator <(const Tile& t) const{
    //cout << "IS THIS SHIT EVEN EXECUTING!? (<)" << endl;
    //if(id == t.id){
    //  cout << "IDS are the same lol" << endl;
    //}
    if(id == t.id) return false;
    return height <= t.height;
  }
};

int n;

void sort_tiles_by_prices(vector<Tile> &v){
  sort(v.begin(), v.end(), [](Tile &a, Tile &b){
    /*if(a.price == b.price){
      return a.height < b.height;
    }*/
    return a.price <= b.price;
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

int sorted_idx = 0;

int main(){
  cin >> n;

  vector<Tile> back, front;
  read_tiles(back);
  read_tiles(front);
  sort_tiles_by_prices(back);
  sort_tiles_by_prices(front);

  map<int, set<Tile>> back_price_tiles, front_price_tiles;

  vector<Tile> back_result;
  vector<Tile> front_result;

  for(int i=0; i<n; i++){
    back_price_tiles[back[i].price].insert(back[i]);
    front_price_tiles[front[i].price].insert(front[i]);
    //printf("When creating the set, before and after inserting %d, %d (inserted ID: %d)\n", bef, aft, back[i].id);
  }

  int left = 0;
  for(int i=0; i<n; i++){

    for(auto it = back_price_tiles.begin(); it != back_price_tiles.end(); it++){
      cout << "Price: " << it->first << " Set size: " << it->second.size() << endl;;

      //for(auto it2 = it->second.begin(); it2 != it->second.end(); it2++){
      //  cout << (*it2).
      //}
    }

    if((i == n-1) || back[i].price != back[i+1].price || front[i].price != front[i+1].price){
      if(i == n-1) printf("condition (i == n-1)\n");
      int sort_from = left;
      int sort_to = i + 1; // exclusive
      left = i + 1;

      printf("Sort from %d to %d\n", sort_from, sort_to);
      for(int j=sort_from; j<sort_to; j++){
        printf("lower_bound = front[%d].height + 1 (result: %d)\n", j, front[j].height + 1);
        int lower_bound = front[j].height + 1;
        front_result.push_back(front[j]);
        set<Tile> &tiles_same_price = back_price_tiles[back[j].price];
        std::set<Tile>::iterator it;

        printf("Size of set before getting the lower bound %ld\n", tiles_same_price.size());
        for(it = tiles_same_price.begin(); it != tiles_same_price.end(); ++it) {
          //printf("Iterating set value (from price set (%d)): %d (lower_bound: %d)\n", longer_list[i].price, (*it).height, lower_bound);
          printf("checking (*it).height >= lower_bound --> %d >= %d\n", (*it).height, lower_bound);
          if((*it).height >= lower_bound){
            break;
          }
        }

        if(it == tiles_same_price.end()){
          cout << "impossible on j=" << j << endl;
          return 0;
        } else {
          Tile val = *it;
          back_result.push_back(val);

          int bef = tiles_same_price.size();
          tiles_same_price.erase(it);
          int after = tiles_same_price.size();
          printf("set size bef and aft %d %d\n", bef, after);
        }
      }
    }
  }

  printf("n=%d and result lengths are %ld and %ld\n", n, back_result.size(), front_result.size());

  for(int i=0; i<n; i++){
    cout << back_result[i].id << " ";
  }

  cout << endl;

  for(int i=0; i<n; i++){
    cout << front_result[i].id << " ";
  }

  cout << endl;
}
