#include "../utils/RNG.hpp"
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>


#define all(x) (x).begin(), (x).end()

using namespace std;

long double distance(const vector<long double> &point_a, const vector<long double> &point_b)
{
  long double dist = 0;
  for (int i = 0; i < point_a.size(); i++) { dist += (point_a[i] - point_b[i]) * (point_a[i] - point_b[i]); }

  return sqrt(dist);
}


int main()
{
  using namespace utils;

  using intType = long int;
  const intType n_max = 1'000'000;

  utils::RNG<li_config> rng_base(0, n_max);
  auto rng_between_0_and_1 = [&]() { return static_cast<long double>(rng_base()) / static_cast<long double>(n_max); };

  vector<int> dims{ 10, 50, 100, 500, 1000, 2000, 5000 };
  int n_points = 100;

  for (auto &&dim : dims) {

    vector<vector<long double>> points(n_points, vector<long double>(dim));// points between 0 and 1
    vector<vector<long double>> dist_matrix(n_points, vector<long double>(n_points));// points between 0 and 1
    for (int i = 0; i < n_points; i++) {
      int counter = 0;

      std::generate(all(points[i]), [&]() {
        const intType center = 500'000;
        const long double d_center = 0.5;
        const intType r = 500'000;
        const long double d_r = 0.5;

        const intType r2 = 250'000;
        long double d_r2 = 0.25;

        if (counter == 0) {
          counter++;
          auto result = rng_between_0_and_1();
          return result;
          // return static_cast<long double>(0.95);
        }

        for (int o = 0; o < counter; o++) {
          const long double p{ points[i][o] };
          const long double diff{ p - d_center };
          const long double diff2{ diff * diff };

          d_r2 -= diff2;
        }

        d_r2 = sqrtl(d_r2);// 0.2 at d=2

        long int min = center - static_cast<long int>(d_r2 * n_max);// at d=2 and 0.4975
        long int max = center + static_cast<long int>(d_r2 * n_max);// at d=2 and 0.5025
        utils::RNG<li_config> rng_base2(min, max);
        auto rng2 = [&]() { return static_cast<long double>(rng_base2()) / static_cast<long double>(n_max); };

        counter++;
        auto result = rng2();
        return result;
      });
      // 0.0025
    }

    // cout << "points: " << endl;
    // for (int i = 0; i < n_points; i++) {
    //   cout << "d: " << dim << "\ti: " << i << endl;
    //   cout << std::fixed << std::setprecision(2) << points[i] << endl;

    //   long double s = 0;
    //   for (int j = 0; j < points[i].size(); j++) { s += (0.5 - points[i][j]) * (0.5 - points[i][j]); }
    //   cout << "s: " << sqrtl(s) << endl;
    // }

    // calcular distancias en una matriz
    for (int x = 0; x < n_points; x++) {
      for (int y = x + 1; y < n_points; y++) { dist_matrix[x][y] = distance(points[x], points[y]); }
    }

    for (int x = 0; x < n_points; x++) {
      for (int y = x + 1; y < n_points; y++) { cout << std::fixed << std::setprecision(9) << dist_matrix[x][y] << " "; }
    }
    cout << "\n";
  }
}
