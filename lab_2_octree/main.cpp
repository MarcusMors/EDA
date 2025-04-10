#ifndef __MAIN_H__
#define __MAIN_H__

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
#include "octree.hpp"
#include <cstddef>
#include <fstream>
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


double min_x = I_INF;
double min_y = I_INF;
double min_z = I_INF;
double max_x = -I_INF;
double max_y = -I_INF;
double max_z = -I_INF;
eda::Point min_p{};
eda::Point max_p{};

vector<eda::Point> input_file()
{
  int i = 0;
  fstream file("points1.csv");

  vector<eda::Point> ps{};
  for (eda::Point p; file >> p; i++) {
    min_x = min(min_x, p.x);
    min_y = min(min_y, p.y);
    min_z = min(min_z, p.z);
    max_x = max(max_x, p.x);
    max_y = max(max_y, p.y);
    max_z = max(max_z, p.z);
    ps.push_back(p);
  }
  min_p = eda::Point{ .x = min_x, .y = min_y, .z = min_z };
  max_p = eda::Point{ .x = max_x, .y = max_y, .z = max_z };

  file.close();
  return ps;
}
vector<eda::Point> input_console()
{
  vector<eda::Point> ps;
  int n{};
  cin >> n;
  for (size_t i = 0; i < n; i++) {
    eda::Point p;
    cin >> p;
    min_x = min(min_x, p.x);
    min_y = min(min_y, p.y);
    min_z = min(min_z, p.z);
    max_x = max(max_x, p.x);
    max_y = max(max_y, p.y);
    max_z = max(max_z, p.z);
    ps[i] = p;
  }

  min_p = eda::Point{ .x = min_x, .y = min_y, .z = min_z };
  max_p = eda::Point{ .x = max_x, .y = max_y, .z = max_z };


  return ps;
}

int main()
{
  // points1.csv has 1136 points

  vector<eda::Point> ps = input_file();
  // vector<eda::Point> ps = input_console();


  int threshold = 4;

  eda::Octree octree(min_p, max_p, threshold, ps);

  auto exists = [&](const eda::Point &t_p) -> bool { return octree.exist(t_p); };
  auto insert = [&](const eda::Point &t_p) -> void {
    if (octree.insert(t_p)) {
      return;
    } else {
      return;
    }
  };
  auto find_closest = [&](const eda::Point &t_p, int radius) -> eda::Point {
    auto closest = octree.find_closest(t_p, radius);
    if (closest) {
      return *closest;
    } else {
      return P_NINF;
    }
  };

  int n;
  cin >> n;
  while (n--) {
    // cout << "n:" << n;
    char option{};
    cin >> option;
    if (option == eda::interface::print) {
      octree.print();
      continue;
    }
    eda::Point p{};
    cin >> p;

    switch (option) {
    case eda::interface::exists: cout << exists(p) << "\n"; break;
    case eda::interface::insert: insert(p); break;
    case eda::interface::find_closest:
      int r{};
      cin >> r;
      cout << find_closest(p, r) << endl;
      break;

      // default: cout << "UNEXPECTED:" << option << "\n"; break;
    }
  }


  return 0;
}

#endif// __MAIN_H__