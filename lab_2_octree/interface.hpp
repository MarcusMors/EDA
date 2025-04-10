#ifndef __INTERFACE_H__
#define __INTERFACE_H__

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


#include "point.hpp"
#include <bits/stdc++.h>

#define debugging

#ifdef debugging
#define DEBUG(x) cout << (x) << std::flush
#define DEBUGLN(x) cout << (x) << endl
#else
#define DEBUG(x)
#define DEBUGLN(x)
#endif

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
// #define token_to_replace token_replacing

using namespace std;
using ui = unsigned;
using sstream = std::stringstream;
using ii = std::pair<int, int>;
using vi = std::vector<int>;
using vii = std::vector<ii>;
using vvii = std::vector<vii>;
using vvi = std::vector<vi>;

const double I_INF = std::numeric_limits<double>::max() - 1000000;
const eda::Point P_INF = { .x = I_INF, .y = I_INF, .z = I_INF };
const eda::Point P_NINF = { .x = -I_INF, .y = -I_INF, .z = -I_INF };

template<class T, class U> std::ostream &operator<<(ostream &os, pair<T, U> v)
{
  return os << "(" << v.first << "," << v.second << ")";
}


template<class T> std::ostream &operator<<(ostream &os, vector<T> v)
{
  for (auto &&e : v) { os << e << " "; }
  return os;
}


namespace eda {

// -10,118,0
// 99,27,37
//
enum interface : char {
  exists = 'e',// P -> Bool
  insert = 'i',// P
  find_closest = 'c',// P,int -> *P -> if (nulltpr) {return - <int>::min();}  else { return *P; }
  print = 'p',// P,int -> *P -> if (nulltpr) {return - <int>::min();}  else { return *P; }
  other,// P,int -> *P -> if (nulltpr) {return - <int>::min();}  else { return *P; }
};

double distance(Point lhs, Point rhs)
{
  double diffx2 = (lhs.x - rhs.x) * (lhs.x - rhs.x);
  double diffy2 = (lhs.y - rhs.y) * (lhs.y - rhs.y);
  double diffz2 = (lhs.z - rhs.z) * (lhs.z - rhs.z);
  return sqrt(diffx2 + diffy2 + diffz2);
}

}// namespace eda

#endif// __INTERFACE_H__  7514