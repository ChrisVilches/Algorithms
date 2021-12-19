#include <bits/stdc++.h>
using namespace std;

int H, W;
char grid[201][201];
string input_line;

const regex allowed_characters("[a-zA-Z0-9+,\\.!?\\s]");

struct Image {
  Image(int i, int j, int i2, int j2) : from_i(i), from_j(j), to_i(i2), to_j(j2) {
    nested_images = Image::scan_images(i + 1, j + 1, i2 - 1, j2 - 1);

    for (const Image& img : nested_images)
      for (int i = img.from_i; i < img.to_i; i++)
        for (int j = img.from_j; j < img.to_j; j++) nested_images_cells.insert({i, j});
  }

  void remove_ad_chars() const {
    for (const Image& img : nested_images) img.remove_ad_chars();

    if (!is_ad()) return;

    for (int i = from_i; i < to_i; i++)
      for (int j = from_j; j < to_j; j++) grid[i][j] = ' ';
  }

  static vector<Image> scan_images(int from_i, int from_j, int to_i, int to_j) {
    vector<Image> images;
    set<pair<int, int>> nested_images_cells;

    for (int i = from_i; i < to_i; i++) {
      for (int j = from_j; j < to_j; j++) {
        if (nested_images_cells.count({i, j})) continue;
        if (i == to_i - 1 || j == to_j - 1) continue;
        if (grid[i][j] == '+' && grid[i + 1][j] == '+' && grid[i][j + 1] == '+') {
          int i2 = i;
          int j2 = j;

          while (i2 < to_i && grid[i2][j] == '+') i2++;
          while (j2 < to_j && grid[i][j2] == '+') j2++;

          for (int y = i; y < i2; y++)
            for (int x = j; x < j2; x++) nested_images_cells.insert({y, x});

          images.push_back({i, j, i2, j2});
        }
      }
    }
    return images;
  }

 private:
  const int from_i, from_j, to_i, to_j;
  vector<Image> nested_images;
  set<pair<int, int>> nested_images_cells;

  bool is_ad() const {
    string c(1, ' ');

    for (int i = from_i; i < to_i; i++)
      for (int j = from_j; j < to_j; j++) {
        if (nested_images_cells.count({i, j})) continue;

        c[0] = grid[i][j];
        if (!regex_match(c, allowed_characters)) return true;
      }

    return false;
  }
};

int main() {
  while (getline(cin, input_line)) {
    stringstream ss(input_line);

    ss >> H >> W;

    for (int i = 0; i < H; i++) {
      getline(cin, input_line);
      for (int j = 0; j < W; j++) grid[i][j] = input_line[j];
    }

    vector<Image> images = Image::scan_images(0, 0, H, W);

    for (const Image& img : images) img.remove_ad_chars();

    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) cout << grid[i][j];
      cout << '\n';
    }
  }
}
