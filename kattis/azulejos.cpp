#include <bits/stdc++.h>

using namespace std;

struct Tile {
  int price, height, id;
  bool operator ==(const Tile& t) const{
    throw runtime_error("SHOULDNT HAPPEN Lol");
    cout << "EXECUTING ==" << endl;
    return id == t.id;
  }
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

void print_price_set(set<Tile> s){
  fprintf(stderr, "Elements: %ld,", s.size());
  for(auto it=s.begin(); it != s.end(); ++it){
    Tile t = *it;
    fprintf(stderr, " (id: %d, price: %d, height: %d)", t.id, t.price, t.height);
  }
  cerr << endl;
}

void print_map(map<int, set<Tile>> m){
  fprintf(stderr, "MAP: ");
  for(auto it=m.begin(); it != m.end(); ++it){
    fprintf(stderr, "(Price: %d, Elements: %ld) ", it->first, it->second.size());
  }
  cerr << endl;
}

void assertx(bool v){
  if(v) return;
  throw runtime_error("xxxx");
}

void assertx(bool v, string msg){
  if(v) return;
  throw runtime_error(msg);
}

int main(){
  cin >> n;
  map<int, set<Tile>> back, front;

  read_tiles(back);
  read_tiles(front);
/*
  set<int> s;
  s.insert(2);
  s.insert(5);
  s.insert(7);
  s.insert(8);
  assertx(*s.lower_bound(6) == 7, "1");
  assertx(*s.lower_bound(5) == 5, "2");
  assertx(*s.lower_bound(4) == 5, "3");
  assertx(*s.upper_bound(5) == 7, "4");
  assertx(*s.upper_bound(7) == 8, "4");
  assertx(s.upper_bound(8) == s.end(), "5");
*/
  set<Tile> ss;
  Tile t1;
  t1.id = 555;
  t1.price = 123;
  t1.height = 1000;
  Tile t2;
  t2.id = 666;
  t2.price = 123445;
  t2.height = 2000;
  Tile t3;
  t3.id = 777;
  t3.price = 6564645;
  t3.height = 3000;
  Tile t4;
  t4.id = 444;
  t4.price = 234;
  t4.height = 500;

  ss.insert(t1);
  ss.insert(t2);
 // cout << (*ss.lower_bound(t2)).id << endl;
  assertx((*ss.find(t1)).id == 555, "4");
  assertx((*ss.lower_bound(t2)).id == 666, "1");
  assertx((ss.upper_bound(t2)) == ss.end(), "2");
  assertx((ss.lower_bound(t3)) == ss.end(), "3");
  assertx((ss.lower_bound(t4)) == ss.find(t1), "4");
  assertx((ss.upper_bound(t4)) == ss.find(t1), "4");

  vector<Tile> back_result, front_result;

  for(int i=0; i<n; i++){
    set<Tile>& back_set = back.begin()->second;
    set<Tile>& front_set = front.begin()->second;
    set<Tile>::iterator add_to_back, add_to_front;

    if(back_set.size() >= front_set.size()){
      add_to_front = front_set.begin();
      add_to_back = back_set.upper_bound(*add_to_front);

      while(1){
        if(add_to_back != back_set.end()){
          if((*add_to_back).height > (*add_to_front).height) break;
        }
        if(add_to_back == back_set.end()) break;
        ++add_to_back;
      }

      if(add_to_back != back_set.end()){
        if((*add_to_back).height > (*add_to_front).height){
          // OK
        } else {
          ++add_to_back;
        }
      }
    } else {
      add_to_back = back_set.begin();
      add_to_front = front_set.lower_bound(*add_to_back);

      while(1){
        if(add_to_front != front_set.end()){
          if((*add_to_back).height > (*add_to_front).height) break;
        }
        if(add_to_front == front_set.begin()) break;
        --add_to_front;
      }
    }

    if((add_to_back == back_set.end()) || (add_to_front == front_set.end())){
      cout << "impossible" << endl;
      return 0;
    }

    if((*add_to_back).height > (*add_to_front).height){

    } else {
      cout << "impossible" << endl;
      return 0;
    }

    back_result.push_back(*add_to_back);
    front_result.push_back(*add_to_front);

    //int b1 = back_set.size();
    //int f1 = front_set.size();
    back_set.erase(add_to_back);
    front_set.erase(add_to_front);
    //int b2 = back_set.size();
    //int f2 = front_set.size();

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
