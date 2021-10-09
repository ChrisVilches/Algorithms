#include <bits/stdc++.h>

using namespace std;

struct Tile {
  int price, height, id;
  bool operator <(const Tile& t) const{
    if(height != t.height){
      return height < t.height;
    }

    return id != t.id;
  }
};

int n;

void read_tiles(map<int, set<Tile>> &row){
  vector<Tile> tiles;
  for(int i=0; i<n; i++){
    Tile t;
    t.id = i + 1;
    cin >> t.price;
    tiles.push_back(t);
  }
  for(int i=0; i<n; i++){
    cin >> tiles[i].height;
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
  t2.id = 777;
  t2.price = 6564645;
  t2.height = 3000;

  ss.insert(t1);
  ss.insert(t2);
  /*assertx((*ss.begin()).id == 555, "1");
  assertx((*ss.lower_bound(t1)).id == 555, "2");
  assertx((*ss.upper_bound(t1)).id == 666, "3"); // THIS ONE SHOULD BE THE NEXT ITEM OF t1!!!!!!!! WTF
  assertx((*ss.lower_bound(t2)).id == 666, "4");
  assertx(ss.upper_bound(t2) == ss.end(), "upper bound");
  assertx(ss.lower_bound(t3) == ss.end(), string("lower bound no funciona como pensaba!?!?!?!?"));
*/
  //assertx(back[1].size() == 1, string("price 1 wrong set size"));
  //assertx(back[2].size() == 2, string("price 2 wrong set size"));
  //assertx(back[3].size() == 1, string("price 3 wrong set size"));

  vector<Tile> back_result, front_result;

  for(int i=0; i<n; i++){
    set<Tile>& back_set = back.begin()->second;
    set<Tile>& front_set = front.begin()->second;
    assertx(front_set.size() > 0);
    assertx(back_set.size() > 0);
    cerr << "-------------------- i = " << i << endl;
    print_map(back);
    print_map(front);
    cerr << "Elements in back: ";
    print_price_set(back_set);
    cerr << "Elements in front: ";
    print_price_set(front_set);
    cerr << "--------------------" << endl;

    //fprintf(stderr, "Prices back: %d, front: %d\n", back.begin()->first, front.begin()->first);

    set<Tile>::iterator add_to_back, add_to_front;

    if(back_set.size() >= front_set.size()){
      // Add smallest item in back that's taller than the one in front
      add_to_front = front_set.begin();
      assertx(add_to_front != front_set.end());
      add_to_back = back_set.upper_bound(*add_to_front);

      if(add_to_back != back_set.end()){

        if((*add_to_back).height > (*add_to_front).height){
          // OK
        } else {
          add_to_back++;
        }

      }
    } else {
      // Add item closest to the one in back (i.e. tallest item possible that's smaller than the one in back)
      add_to_back = back_set.begin();
      assertx(add_to_back != back_set.end());
      add_to_front = --front_set.lower_bound(*add_to_back);

      if(add_to_front != front_set.end() && add_to_front != front_set.begin()){
        if((*add_to_back).height > (*add_to_front).height){
          // OK
        } else {
          add_to_front--;
        }
      }

      
    }

    if(add_to_back == back_set.end() || add_to_front == front_set.end()){
      if(add_to_back == back_set.end()){
        cerr << "add to back is end()" << endl;
      } else {
        cerr << "add to front is end()" << endl;
      }

      cout << "impossible" << endl;
      return 0;
    }

    if((*add_to_back).height > (*add_to_front).height){

    } else {
      cout << "impossible" << endl;
      return 0;
    }

    assertx((*add_to_back).height > (*add_to_front).height);

    back_result.push_back(*add_to_back);
    front_result.push_back(*add_to_front);

    int b1 = back_set.size();
    int f1 = front_set.size();
    back_set.erase(add_to_back);
    front_set.erase(add_to_front);
    int b2 = back_set.size();
    int f2 = front_set.size();
    assertx(b1-1 == b2);
    assertx(f1-1 == f2);

    if(back_set.size() == 0) back.erase(back.begin());
    if(front_set.size() == 0) front.erase(front.begin());
  }

  assertx(back.size() == 0);
  assertx(front.size() == 0);
  assertx(back_result.size() == n);
  assertx(front_result.size() == n);
  
  fprintf(stderr, "size of initial maps %ld %ld\n", back.size(), front.size());
  fprintf(stderr, "size of back and front result vectors %ld %ld\n", back_result.size(), front_result.size());

  for(int i=0; i<n; i++){
    cout << back_result[i].id << " ";
  }

  cout << endl;

  for(int i=0; i<n; i++){
    cout << front_result[i].id << " ";
  }

  cout << endl;
}
