#include <bits/stdc++.h>

using namespace std;

#define MAX_STRING_LENGTH (2 * 100003)

string city;
int N;

int sa[MAX_STRING_LENGTH];
int ranks[MAX_STRING_LENGTH], lcp[MAX_STRING_LENGTH], gap, S;
bool cmp(int x, int y) {
  if(ranks[x] != ranks[y])
    return ranks[x] < ranks[y];
  x += gap, y += gap;
  return (x < S && y < S)? ranks[x] < ranks[y]: x > y;
}

void suffix_array_build(const string &s) {
  S = s.size();
  vector<int> tmp;
  for(int i=0; i<S; i++){
    tmp.push_back(0);
  }
  for(int i = 0;i < S;++i)
    ranks[i] = s[i],
    sa[i] = i;
  for(gap = 1; ;gap <<= 1) {
    sort(sa, sa + S, cmp);
    for(int i = 1;i < S;++i)
      tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
    for(int i = 0;i < S;++i)
      ranks[sa[i]] = tmp[i];
    if(tmp[S - 1] == S - 1)
      break;
  }
}

int compare(int sa_pos, const string& city, const string& name, int name_offset){
  int pos_in_string = sa[sa_pos];
  int total = 0;
  for(int i=0; ; i++){
    int pos_city = i + pos_in_string;
    int pos_s = i + name_offset;
    if(pos_s == name.size() || pos_in_string == city.size()) break;

    char c1 = city[pos_city];
    char c2 = name[pos_s];
    if(c1 != c2) break;
    total++;
  }

  return total;
}

int compare(string& s1, string& s2){
  int total = 0;
  for(int i=0; i<s1.size() && i<s2.size(); i++){
    if(s1[i] == s2[i]){
      total++;
    } else {
      break;
    }
  }
  return total;
}

string suffix_at(int i){
  return city.substr(sa[i]);
}

int find_suffix_array_position(const string &name_substr){
  int longest_match = 0;
  int match_pos = 0;

  int mid;
  int left = 0;
  int right = city.size() - 1; // TODO: If I recall correctly, it worked after deleting the -1

  //cout << "using name_substr = " << name_substr << endl;

  for(int i=0; i<name_substr.size(); i++){
    left = 0;
    right = city.size();
    string name_substr_substr = name_substr.substr(0, i+1); // (?)
    //cout << "(i=" << i << ") name substr substr = " << name_substr_substr << " , longest_match = " << longest_match << endl;
    while(left < right){
      mid = (right + left)/2;

      
      //cout << "left " << left << " , " << "right " << right << endl;
      //cout << "testing suffix " << suffix << endl;

      //int m = compare(suffix, name_substr_substr);
      int m = compare(mid, city, name_substr_substr, 0);
      if(m > longest_match){
        longest_match = m;
        match_pos = mid;
      }

      //if(m == name_substr_substr.size()) return mid;
      // string suffix = suffix_at(mid);
      // bool greater = suffix < name_substr_substr;

      bool greater = name_substr_substr.compare(0, name_substr_substr.size(), city, sa[mid], city.size()-sa[mid]) > 0;

      if(greater){
        left = mid + 1;
      } else {
        right = mid;
      }
    }
  }

  return match_pos;
/*
  while(left < right){
    int mid = (right + left)/2;
    //printf("string size is %d and mid pos is %d\n", city.size(), sa[mid]);
    if(city[sa[mid]] < name_substr[0]){
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  for(int i=left; i<city.size(); i++){
    int m = compare(i, city, name_substr, 0);
    if(m == 0) break;
    if(m > longest_match){
      longest_match = m;
      match_pos = i;
    }
  }
  return match_pos;
  */
}

int necessary_for_name(const string& name){
  hash<string> hasher;
  unordered_set<int> pictures;
  
  int name_curr_pos = 0;

  while(name_curr_pos < name.size()){
    // Find best match in suffix array.
    int sa_pos = find_suffix_array_position(name.substr(name_curr_pos));

    if(sa_pos == -1) return -1;

    int pos_in_city = sa[sa_pos];
    string longest;

    // From the best match, get the longest string.
    for(int i=pos_in_city; i<city.size() && name_curr_pos < name.size(); i++){
      if(city[i] == name[name_curr_pos]){
        longest += city[i];
        name_curr_pos++;
      } else {
        break;
      }
    }
   // cerr << "longest: " << longest << endl;
    // If no characters were fetched from that string, it means the name cannot be completed.
    if(longest.size() == 0)
      return -1;

    pictures.insert(hasher(longest));
  }

  return pictures.size();
}

int main(){
  cin >> city >> N;

  suffix_array_build(city);

  for(int i=0; i<N; i++){
    string name;
    cin >> name;
    cout << necessary_for_name(name) << endl;
  }
}
