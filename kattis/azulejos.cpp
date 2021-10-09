#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

int n;

void read_tiles(map<int, set<pii>> &row){
  vector<pii> tiles; // ID, price
  for(int i=0; i<n; i++){
    pii t;
    t.first = i + 1;
    scanf("%d", &t.second);
    tiles.push_back(t);
  }
  for(int i=0; i<n; i++){
    int height;
    scanf("%d", &height);
    row[tiles[i].second].insert(make_pair(height, tiles[i].first));
  }
}

int main(){
  cin >> n;
  map<int, set<pii>> back, front;

  read_tiles(back);
  read_tiles(front);

  vector<pii> back_result, front_result;

  for(int i=0; i<n; i++){
    set<pii>& back_set = back.begin()->second;
    set<pii>& front_set = front.begin()->second;
    set<pii>::iterator add_to_back, add_to_front;

    if(back_set.size() >= front_set.size()){
      add_to_front = front_set.begin();
      add_to_back = back_set.upper_bound(make_pair(add_to_front->first, INT_MAX));
      if(add_to_back == back_set.end()){
        cout << "impossible" << endl;
        return 0;
      }
    } else {
      add_to_back = back_set.begin();
      add_to_front = front_set.lower_bound(make_pair(add_to_back->first, 0));

      if(add_to_front == front_set.begin()){
        cout << "impossible" << endl;
        return 0;
      }

      --add_to_front;
    }

    back_result.push_back(*add_to_back);
    front_result.push_back(*add_to_front);

    back_set.erase(add_to_back);
    front_set.erase(add_to_front);

    if(back_set.size() == 0) back.erase(back.begin());
    if(front_set.size() == 0) front.erase(front.begin());
  }

  for(int i=0; i<n; i++){
    printf("%d ", back_result[i].second);
  }

  printf("\n");

  for(int i=0; i<n; i++){
    printf("%d ", front_result[i].second);
  }

  printf("\n");
}
