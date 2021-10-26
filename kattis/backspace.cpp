#include <bits/stdc++.h>

using namespace std;

int main() {
  string line;
  cin >> line;
  int erase = 0;
  string result;
  for (int i = line.size() - 1; i >= 0; i--) {
    if (line[i] == '<')
      erase++;
    else {
      if (erase > 0)
        erase--;
      else
        result += line[i];
    }
  }

  reverse(result.begin(), result.end());
  cout << result << endl;
}
