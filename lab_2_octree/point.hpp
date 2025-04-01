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

#include <cmath>
#include <ios>// Defines std::ios_base
#include <iostream>

namespace eda {

enum z_order : int {
  // xyz (negative = n, positive = p)
  nnn_0 = 0,// (-X, -Y, -Z)
  pnn_1 = 1,// (+X, -Y, -Z)
  npn_2 = 2,// (-X, +Y, -Z)
  ppn_3 = 3,// (+X, +Y, -Z)
  nnp_4 = 4,// (-X, -Y, +Z)
  pnp_5 = 5,// (+X, -Y, +Z)
  npp_6 = 6,// (-X, +Y, +Z)
  ppp_7 = 7// (+X, +Y, +Z)
};


struct Point
{
  int x{};
  int y{};
  int z{};

  // Equality operator
  bool operator==(const Point &other) const { return x == other.x && y == other.y && z == other.z; }

  // Inequality operator
  bool operator!=(const Point &other) const { return !(*this == other); }
  double distance(const Point &other)
  {
    double diffx2 = (x - other.x) * (x - other.x);
    double diffy2 = (y - other.y) * (y - other.y);
    double diffz2 = (z - other.z) * (z - other.z);
    return sqrt(diffx2 + diffy2 + diffz2);
  }
  z_order z_order_in_relation_to_mid(const Point mid)
  {
    int x_sign = (x <= mid.x) ? 0 : 1;
    int y_sign = (y <= mid.y) ? 0 : 1;
    int z_sign = (z <= mid.z) ? 0 : 1;
    return static_cast<z_order>((z_sign << 2) | (y_sign << 1) | x_sign);
  }
};

std::ostream &operator<<(std::ostream &os, eda::Point p) { return os << p.x << "," << p.y << "," << p.z; }

std::istream &operator>>(std::istream &is, eda::Point &p)
{
  char g;
  int x, y, z;
  if ((is >> x) and (is >> g and g == ',') and (is >> y) and (is >> g and g == ',') and (is >> z)) {
    p = eda::Point{ x, y, z };
    return is;
  }
  is.setstate(std::ios_base::failbit);// register the failure in the stream
  return is;
}


}// namespace eda

/*

i want to name an method of a point class.
Point mid;
Point p1;
mid.method_name(p1);
this method returns a z_order type:
enum z_order : int {
  // xyz (negative = n, positive = p)
  seventh_nnn_0 = 0,// (-X, -Y, -Z)
  fifth_pnn_1 = 1,// (+X, -Y, -Z)
  sixth_npn_2 = 2,// (-X, +Y, -Z)
  third_ppn_3 = 3,// (+X, +Y, -Z)
  eighth_nnp_4 = 4,// (-X, -Y, +Z)
  first_pnp_5 = 5,// (+X, -Y, +Z)
  second_npp_6 = 6,// (-X, +Y, +Z)
  fourth_ppp_7 = 7// (+X, +Y, +Z)
};

depending on where the point is located in relation to mid point.


*/