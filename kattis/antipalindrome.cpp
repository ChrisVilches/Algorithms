#include <bits/stdc++.h>
using namespace std;

bool is_palindrome(const string s) {
  const int n = s.size();

  for (int i = 0; i < n / 2; i++) {
    if (s[i] != s[n - 1 - i]) return false;
  }

  return true;
}

bool has_palindromes(const string s) {
  const int n = s.size();
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (is_palindrome(s.substr(i, j - i + 1))) return true;
    }
  }
  return false;
}

int main() {
  string s;
  getline(cin, s);

  int k = 0;

  for (const char c : s) {
    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) s[k++] = tolower(c);
  }

  s.resize(k);

  cout << (has_palindromes(s) ? "Palindrome" : "Anti-palindrome") << endl;
}
