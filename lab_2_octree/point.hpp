#ifndef __POINT_H__
#define __POINT_H__

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
  double x{};
  double y{};
  double z{};

  // Equality operator
  bool operator==(const Point &other) const { return x == other.x && y == other.y && z == other.z; }

  // Inequality operator
  bool operator!=(const Point &other) const { return !(*this == other); }
  double distance_sq(const Point &other) const
  {
    double diffx = static_cast<double>(x) - other.x;
    double diffy = static_cast<double>(y) - other.y;
    double diffz = static_cast<double>(z) - other.z;
    return diffx * diffx + diffy * diffy + diffz * diffz;
  }

  // Calculate Euclidean distance
  double distance(const Point &other) const { return std::sqrt(distance_sq(other)); }

  z_order z_order_in_relation_to_mid(const Point mid) const
  {
    int x_sign = (x <= mid.x) ? 0 : 1;
    int y_sign = (y <= mid.y) ? 0 : 1;
    int z_sign = (z <= mid.z) ? 0 : 1;
    return static_cast<z_order>((z_sign << 2) | (y_sign << 1) | x_sign);
  }
};

std::ostream &operator<<(std::ostream &os, const eda::Point p) { return os << p.x << "," << p.y << "," << p.z; }

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
#endif// __POINT_H__