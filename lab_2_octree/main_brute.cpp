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
  int n{};
  char g{};
  cin >> n;
  vector<Point> ps(n);

  for (size_t i = 0; i < n; i++) {
    Point p;
    cin >> p;
    ps[i] = Point{ p };
  }

  auto exists = [&](const Point &t_p) -> bool {
    for (auto p : ps) {
      if (t_p == p) { return true; }
    }
    return false;
  };
  auto insert = [&](const Point &t_p) -> void {
    for (auto p : ps) {
      if (t_p == p) { return; }
    }
    ps.push_back(t_p);
  };
  auto find_closest = [&](const Point &t_p, int radius) -> Point {
    vector<pair<double, Point>> ds{};
    Point p_ptr{ P_NINF };
    for (auto p : ps) {
      if (p == t_p) { continue; }
      const double d = distance(t_p, p);
      ds.push_back({ d, p });
    }

    double minimum = 1000000;
    for (auto [d, p] : ds) {
      if (d < minimum) {
        minimum = d;
        p_ptr = p;
      }
    }

    if (minimum < static_cast<double>(radius) and p_ptr != P_NINF) { return p_ptr; }
    return P_NINF;
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