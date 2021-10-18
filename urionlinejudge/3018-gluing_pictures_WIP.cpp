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

void suffix_array_build(const string &s){
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

int longest_prefix_match(int sa_pos, const string& city, const string& name, int name_offset){
  int pos_in_string = sa[sa_pos];
  int total = 0;
  for(int i=0; ; i++){
    int pos_city = i + pos_in_string;
    int pos_s = i + name_offset;
    if(pos_s == (int)name.size() || pos_in_string == (int)city.size()) break;

    char c1 = city[pos_city];
    char c2 = name[pos_s];
    if(c1 != c2) break;
    total++;
  }

  return total;
}

int find_suffix_array_position(const string &name, int offset){
  int longest_match = 0;
  int match_pos = 0;
  int mid;
  int left = 0;
  int right = city.size() +0; // TODO: If I recall correctly, it worked after deleting the -1

  while(left < right){
    mid = (right + left)/2;
    int match = longest_prefix_match(mid, city, name, offset);
    if(match > longest_match){
      longest_match = match;
      match_pos = mid;
    }

    bool greater = name.compare(offset, name.size() - offset, city, sa[mid], city.size() - sa[mid]) > 0;

    if(greater){
      left = mid + 1;
    } else {
      right = mid;
    }
  }

  return match_pos;
}

int necessary_for_name(const string& name){
  hash<string> hasher;
  unordered_set<int> pictures;
  int name_curr_pos = 0;

  unordered_set<char> chars;

  while(name_curr_pos < (int)name.size()){

    // Corner case, (but it doesn't work lol... it returns Wrong Answer)
    if(chars.find(name[name_curr_pos]) != chars.end()){
      name_curr_pos++;
      continue;
    }
    // Find best match in suffix array.
    int sa_pos = find_suffix_array_position(name, name_curr_pos);

    if(sa_pos == -1) return -1;

    int pos_in_city = sa[sa_pos];
    string longest;

    // From the best match, get the longest string.
    for(int i=pos_in_city; i<(int)city.size() && name_curr_pos < (int)name.size(); i++){
      if(city[i] == name[name_curr_pos]){
        longest += city[i];
        name_curr_pos++;
      } else {
        break;
      }
    }

    // If no characters were fetched from that string, it means the name cannot be completed.
    if(longest.size() == 0)
      return -1;

    //cout << "inserting: " << longest << endl;
    if(longest.size() == 1){
      chars.insert(longest[0]);
    }
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
