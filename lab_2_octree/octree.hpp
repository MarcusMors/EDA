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
#include <limits>
#include <memory>
#include <stdexcept>
#include <vector>
#include <iostream
#include <optional>


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

  const int threshold = 8;
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
    Point child_bounds[8][2];// Store {bnl, tfr} for each child

    int mid_x_plus_1 = mid.x + 1;
    int mid_y_plus_1 = mid.y + 1;
    int mid_z_plus_1 = mid.z + 1;

    // Octant 0 (nnn): x<=mid.x, y<=mid.y, z<=mid.z
    child_bounds[nnn_0][0] = bottom_near_left_corner;
    child_bounds[nnn_0][1] = mid;

    // Octant 1 (pnn): x>mid.x, y<=mid.y, z<=mid.z
    child_bounds[pnn_1][0] = { mid_x_plus_1, bottom_near_left_corner.y, bottom_near_left_corner.z };
    child_bounds[pnn_1][1] = { top_far_right_corner.x, mid.y, mid.z };

    // Octant 2 (npn): x<=mid.x, y>mid.y, z<=mid.z
    child_bounds[npn_2][0] = { bottom_near_left_corner.x, mid_y_plus_1, bottom_near_left_corner.z };
    child_bounds[npn_2][1] = { mid.x, top_far_right_corner.y, mid.z };

    // Octant 3 (ppn): x>mid.x, y>mid.y, z<=mid.z
    child_bounds[ppn_3][0] = { mid_x_plus_1, mid_y_plus_1, bottom_near_left_corner.z };
    child_bounds[ppn_3][1] = { top_far_right_corner.x, top_far_right_corner.y, mid.z };

    // Octant 4 (nnp): x<=mid.x, y<=mid.y, z>mid.z
    child_bounds[nnp_4][0] = { bottom_near_left_corner.x, bottom_near_left_corner.y, mid_z_plus_1 };
    child_bounds[nnp_4][1] = { mid.x, mid.y, top_far_right_corner.z };

    // Octant 5 (pnp): x>mid.x, y<=mid.y, z>mid.z
    child_bounds[pnp_5][0] = { mid_x_plus_1, bottom_near_left_corner.y, mid_z_plus_1 };
    child_bounds[pnp_5][1] = { top_far_right_corner.x, mid.y, top_far_right_corner.z };

    // Octant 6 (npp): x<=mid.x, y>mid.y, z>mid.z
    child_bounds[npp_6][0] = { bottom_near_left_corner.x, mid_y_plus_1, mid_z_plus_1 };
    child_bounds[npp_6][1] = { mid.x, top_far_right_corner.y, top_far_right_corner.z };

    // Octant 7 (ppp): x>mid.x, y>mid.y, z>mid.z
    child_bounds[ppp_7][0] = { mid_x_plus_1, mid_y_plus_1, mid_z_plus_1 };
    child_bounds[ppp_7][1] = top_far_right_corner;


    // Create the actual child nodes
    for (int i = 0; i < 8; ++i) {
      // Ensure the child bounds are valid before creating
      if (child_bounds[i][0].x <= child_bounds[i][1].x && child_bounds[i][0].y <= child_bounds[i][1].y
          && child_bounds[i][0].z <= child_bounds[i][1].z) {
        children[i] = std::make_unique<Octree>(child_bounds[i][0], child_bounds[i][1], threshold);// Pass threshold down
      } else {
        // Handle degenerate case (e.g., log a warning, or maybe avoid subdivision if dimensions collapse)
        // For now, we'll leave the child as nullptr if bounds are invalid,
        // though ideally the subdivision logic should prevent this unless the initial box is tiny.
        std::cerr << "Warning: Degenerate child bounds for octant " << i << ". Child not created." << std::endl;
      }
    }

    // Redistribute points from the current node to the new children
    std::vector<Point> points_to_move = std::move(points);// Move ownership
    points.clear();// Clear points in the current (now internal) node

    for (const auto &pt : points_to_move) {
      z_order octant = pt.z_order_in_relation_to_mid(mid);
      if (children[octant]) {// Check if child was created successfully
        children[octant]->insert(pt);// Re-insert into the appropriate child
      } else {
        // This shouldn't happen if bounds are handled correctly,
        // but as a fallback, maybe add back to current node or log error.
        std::cerr << "Error: Could not redistribute point " << pt << " to non-existent child octant " << octant
                  << std::endl;
        // Optionally: points.push_back(pt); // Add back if needed, but violates clean subdivision
      }
    }
  }


public:
  Octree(Point t_bottom_near_left_corner, Point t_top_far_right_corner, int min, int max, std::vector<Point> t_ps);
  bool exist(const Point &);
  void insert(const Point &);
  Point find_closest(const Point &, int radius);
};


}// namespace eda


#endif
