#include <bits/stdc++.h>
using namespace std;

int N;

void erase(string& s) {
  for (int i = 0; i < (int)s.size(); i++) {
    if (s[i] == '1')
      s[i] = '0';
    else
      s[i] = '1';
  }
}

int main() {
  cin >> N;
  string file, result;
  cin >> file >> result;

  while (N--) erase(file);

  if (file == result)
    cout << "Deletion succeeded" << endl;
  else
    cout << "Deletion failed" << endl;
}
