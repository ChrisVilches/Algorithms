#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;

ull combinations(int idx, vector<ull> &counts_list){
  if(counts_list.size() == 0) return 0;

  ull category_count = counts_list[idx];
  if(idx == counts_list.size() - 1) return category_count;
  ull other_combinations = combinations(idx+1, counts_list);
  return (category_count + other_combinations) + (category_count * other_combinations);
}

map<string, ull> read_category_count_map(){
  int n;
  cin >> n;
  map<string, ull> counts;
  for(int i=0; i<n; i++){
    string category;
    cin >> category >> category; // Omit first word
    if(counts.find(category) != counts.end()){
      counts[category]++;
    } else {
      counts[category] = 1;
    }
  }
  return counts;
}

void solve(){
  map<string, ull> counts = read_category_count_map();
  vector<ull> counts_list;

  for(auto it = counts.begin(); it != counts.end(); it++){
    counts_list.push_back(it->second);
  }

  cout << combinations(0, counts_list) << endl;
}

int main(){
  int n;
  cin >> n;
  while(n--) solve();
}
