#include "../utils/RNG.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#define all(x) (x).begin(), (x).end()

using namespace std;

double distance(const vector<double> &point_a, const vector<double> &point_b)
{
  double dist = 0;
  for (int i = 0; i < point_a.size(); i++) { dist += (point_a[i] - point_b[i]) * (point_a[i] - point_b[i]); }
  return sqrt(dist);
}


int main()
{

  using std::cout;
  using std::stringstream;
  using std::vector;

  using intType = int;
  const intType n_max = 1'000'000;
  utils::RNG<> rng_base(0, n_max);
  auto rng_between_0_and_1 = [&]() { return double(double(rng_base()) / double(n_max)); };

  vector<int> dims{ 10, 50, 100, 500, 1000, 2000, 5000 };
  int n_points = 100;

  for (auto &&dim : dims) {

    vector<vector<double>> points(n_points, vector<double>(dim));// points between 0 and 1
    vector<vector<double>> dist_matrix(n_points, vector<double>(n_points));// points between 0 and 1

    for (int i = 0; i < n_points; i++) { std::generate(all(points[i]), rng_between_0_and_1); }

    for (int x = 0; x < n_points; x++) {
      for (int y = x + 1; y < n_points; y++) { dist_matrix[x][y] = distance(points[x], points[y]); }
    }

    for (int x = 0; x < n_points; x++) {
      for (int y = x + 1; y < n_points; y++) { cout << std::fixed << std::setprecision(8) << dist_matrix[x][y] << " "; }
    }
    cout << "\n";
  }
  return 0;
}
