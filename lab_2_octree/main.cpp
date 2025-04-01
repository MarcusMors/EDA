// Copyright (C) 2025 José Enrique Vilca Campana
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "interface.hpp"
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

// #include "interface.hpp"

using namespace std;
using namespace eda;

using ui = unsigned;
using sstream = std::stringstream;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vii = std::vector<ii>;
using vvii = std::vector<vii>;
using vvi = std::vector<vi>;


int main()
{
  int n{};// points1.csv has 1136 points
  char g{};
  cin >> n;
  vi xs(n);
  vi ys(n);
  vi zs(n);
  vector<Point> ps(n);

  for (size_t i = 0; i < n; i++) {
    Point p;
    cin >> p;
    xs[i] = p.x;
    ys[i] = p.y;
    zs[i] = p.z;
    ps[i] = Point{ plab };
  }

  // eda::Octree octree;

  auto exists = [&](const Point &t_p) -> bool {
    //
  };
  auto insert = [&](const Point &t_p) -> void {
    //
  };
  auto find_closest = [&](const Point &t_p, int radius) -> Point {
    //
  };

  cin >> n;
  while (--n) {
    char option{};
    cin >> option;
    Point p{};
    cin >> p;

    switch (static_cast<interface>(option)) {
    case eda::interface::exists: cout << exists(p) << "\n"; break;
    case eda::interface::insert: insert(p); break;
    case eda::interface::find_closest:
      int r{};
      cin >> r;
      find_closest(p, r);
      break;

    default: cout << "UNEXPECTED:" << option << "\n"; break;
    }
  }


  return 0;
}
