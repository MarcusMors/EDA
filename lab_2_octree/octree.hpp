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

#ifndef OCTREE_HPP
#define OCTREE_HPP

#include "point.hpp"
#include <algorithm>
#include <cmath>
#include <ios>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>


namespace eda {

class Octree
{
private:
  std::unique_ptr<Octree> children[8]{ nullptr };
  std::vector<Point> points;

  // bottomLeft y h definen el espacio(cubo más grande)
  Point bottom_near_left_corner{};
  Point top_far_right_corner{};
  Point mid{};
  // std:: string str;

  const int threshold = 4;
  int nPoints{};

  bool is_leaf() const
  {
    return children[0] == nullptr;// If one child is null, all should be null.
  }
  bool is_within_bounds(const Point &p) const
  {
    return p.x >= bottom_near_left_corner.x and p.x <= top_far_right_corner.x and//
           p.y >= bottom_near_left_corner.y and p.y <= top_far_right_corner.y and//
           p.z >= bottom_near_left_corner.z and p.z <= top_far_right_corner.z;
  }

  void subdivide()
  {
    // Calculate dimensions for children based on mid point
    // Note: mid point itself belongs to the lower range due to <= in z_order calc
    Point child_bounds[8][2]{};

    double mid_x_plus_1 = mid.x;
    double mid_y_plus_1 = mid.y;
    double mid_z_plus_1 = mid.z;

    child_bounds[nnn_0][0] = bottom_near_left_corner;
    child_bounds[nnn_0][1] = mid;

    child_bounds[pnn_1][0] = { mid_x_plus_1, bottom_near_left_corner.y, bottom_near_left_corner.z };
    child_bounds[pnn_1][1] = { top_far_right_corner.x, mid.y, mid.z };

    child_bounds[npn_2][0] = { bottom_near_left_corner.x, mid_y_plus_1, bottom_near_left_corner.z };
    child_bounds[npn_2][1] = { mid.x, top_far_right_corner.y, mid.z };

    child_bounds[ppn_3][0] = { mid_x_plus_1, mid_y_plus_1, bottom_near_left_corner.z };
    child_bounds[ppn_3][1] = { top_far_right_corner.x, top_far_right_corner.y, mid.z };

    child_bounds[nnp_4][0] = { bottom_near_left_corner.x, bottom_near_left_corner.y, mid_z_plus_1 };
    child_bounds[nnp_4][1] = { mid.x, mid.y, top_far_right_corner.z };

    child_bounds[pnp_5][0] = { mid_x_plus_1, bottom_near_left_corner.y, mid_z_plus_1 };
    child_bounds[pnp_5][1] = { top_far_right_corner.x, mid.y, top_far_right_corner.z };

    child_bounds[npp_6][0] = { bottom_near_left_corner.x, mid_y_plus_1, mid_z_plus_1 };
    child_bounds[npp_6][1] = { mid.x, top_far_right_corner.y, top_far_right_corner.z };

    child_bounds[ppp_7][0] = { mid_x_plus_1, mid_y_plus_1, mid_z_plus_1 };
    child_bounds[ppp_7][1] = top_far_right_corner;


    // Create the child nodes
    for (int i = 0; i < 8; ++i) {
      // Ensure within bounds
      if (child_bounds[i][0].x <= child_bounds[i][1].x && child_bounds[i][0].y <= child_bounds[i][1].y
          && child_bounds[i][0].z <= child_bounds[i][1].z) {
        children[i] = std::make_unique<Octree>(child_bounds[i][0], child_bounds[i][1], threshold);
      } else {
        std::cerr << "Warning: invalid bounds for children " << i << ". Child not created." << std::endl;
      }
    }

    std::vector<Point> points_to_move = points;
    points.clear();

    for (const auto &pt : points_to_move) {
      z_order octant = pt.z_order_in_relation_to_mid(mid);
      if (children[octant]) {// Check successful child creation
        children[octant]->insert(pt);// Re-insert into appropriate child
      }
    }
  }
  void range_query(const Point &center, double radius_sq, std::vector<Point> &points_in_range) const
  {
    // 1. Pruning: Check if the search sphere intersects the node's bounding box
    // A simple (though not perfectly tight) check: find the squared distance
    // from the center to the closest point on the bounding box.
    double dist_sq_to_box = 0.0;
    for (int i = 0; i < 3; ++i) {
      double v;
      int c, bnl, tfr;
      if (i == 0) {
        c = center.x;
        bnl = bottom_near_left_corner.x;
        tfr = top_far_right_corner.x;
      } else if (i == 1) {
        c = center.y;
        bnl = bottom_near_left_corner.y;
        tfr = top_far_right_corner.y;
      } else {
        c = center.z;
        bnl = bottom_near_left_corner.z;
        tfr = top_far_right_corner.z;
      }

      if (c < bnl) {
        v = static_cast<double>(bnl) - c;
      } else if (c > tfr) {
        v = static_cast<double>(c) - tfr;
      } else {// Center coordinate to box's range on this axis
        v = 0.0;
      }
      dist_sq_to_box += v * v;
    }

    // The entire box is outside the search radius, prune this.
    if (dist_sq_to_box > radius_sq) { return; }

    if (is_leaf()) {
      for (const auto &pt : points) {
        if (pt.distance_sq(center) <= radius_sq) { points_in_range.push_back(pt); }
      }
    } else {
      for (int i = 0; i < 8; ++i) {
        if (children[i]) {// Check if child exists
          children[i]->range_query(center, radius_sq, points_in_range);
        }
      }
    }
  }


public:
  double h() const { return top_far_right_corner.z - bottom_near_left_corner.z; }
  eda::Point bottom_left() const { return bottom_near_left_corner; }
  void print()
  {
    if (not is_leaf()) {
      cout << "octree:" << "(" << bottom_left() << ")" << " " << h() << endl;
      for (int i = 0; i < 8; i++) { children[i]->print_r(1); }
    } else {
      // cout << "leaf:" << " ";
      // for (auto p : points) { cout << "(" << p << ") "; }
      // cout << endl;
    }
  }
  void tab(int deep)
  {
    cout << deep << " ";
    for (int i = 0; i < deep; i++) { cout << "-"; }
  }

  void print_r(int deep = 0)
  {
    std::string str;
    cin >> str;
    if (not is_leaf()) {
      tab(deep);
      cout << "octree:" << "(" << bottom_left() << ")" << " " << h() << endl;
      for (int i = 0; i < 8; i++) { children[i]->print_r(deep + 1); }
    } else {
      tab(deep);
      // cout << "leaf:" << " ";
      // for (auto p : points) { cout << "(" << p << ") "; }
      // cout << endl;
    }
  }

  Octree(Point t_bottom_near_left_corner,
    Point t_top_far_right_corner,
    int node_threshold = 8,
    const std::vector<Point> &initial_points = {})
    : bottom_near_left_corner(t_bottom_near_left_corner), top_far_right_corner(t_top_far_right_corner),
      threshold(node_threshold), nPoints(0)
  {
    if (t_bottom_near_left_corner.x > t_top_far_right_corner.x || t_bottom_near_left_corner.y > t_top_far_right_corner.y
        || t_bottom_near_left_corner.z > t_top_far_right_corner.z) {
      throw std::invalid_argument("Octree bounds are invalid (min > max)");
    }

    mid.x = bottom_near_left_corner.x + (top_far_right_corner.x - bottom_near_left_corner.x) / 2;
    mid.y = bottom_near_left_corner.y + (top_far_right_corner.y - bottom_near_left_corner.y) / 2;
    mid.z = bottom_near_left_corner.z + (top_far_right_corner.z - bottom_near_left_corner.z) / 2;

    for (const auto &p : initial_points) { insert(p); }
  }
  bool insert(const Point &p)
  {
    if (not is_within_bounds(p) or exist(p)) { return false; }

    if (is_leaf()) {
      bool cannot_subdivide =
        (bottom_near_left_corner.x == top_far_right_corner.x && bottom_near_left_corner.y == top_far_right_corner.y
          && bottom_near_left_corner.z == top_far_right_corner.z);

      if (points.size() < threshold or cannot_subdivide) {
        // Avoid inserting duplicates if necessary (optional, depends on requirements)
        points.push_back(p);
        nPoints++;
        return true;
      } else {
        subdivide();
      }
    }

    z_order octant = p.z_order_in_relation_to_mid(mid);

    if (children[octant]) {
      bool inserted = children[octant]->insert(p);
      if (inserted) { nPoints++; }
      return inserted;
    } else {
      return false;
    }
  }
  bool exist(const Point &p) const
  {
    if (not is_within_bounds(p)) { return false; }

    if (is_leaf()) {
      return std::find(points.begin(), points.end(), p) != points.end();
    } else {
      z_order octant = p.z_order_in_relation_to_mid(mid);
      if (children[octant]) {
        cout << "(" << bottom_left() << ")" << endl;
        cout << "h: " << h() << endl;
        return children[octant]->exist(p);
      } else {
        return false;
      }
    }
  }
  std::optional<Point> find_closest(const Point &p, double radius) const
  {
    if (radius < 0) { return std::nullopt; }

    std::vector<Point> points_in_range;
    double radius_sq = radius * radius;

    range_query(p, radius_sq, points_in_range);

    if (points_in_range.empty()) { return std::nullopt; }

    auto closest_it = std::min_element(points_in_range.begin(),
      points_in_range.end(),
      [&p](const Point &a, const Point &b) { return a.distance_sq(p) < b.distance_sq(p); });

    return *closest_it;
  }

  int get_nPoints() const { return nPoints; }

  std::pair<Point, Point> get_bounds() const { return { bottom_near_left_corner, top_far_right_corner }; }
};


}// namespace eda


#endif
