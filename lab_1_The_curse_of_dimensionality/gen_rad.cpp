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

// __gcd(value1, value2)
// append ll to get the long long version
// __builtin_ffs(x)// returns 1+ index of least significant bit else returns cero.
// __builtin_ffs(10) = 2 // because 10: "1010", 2 is 1 + the index of the least significant bit from right to left
// __builtin_clz(x) // returns number of leading 0-bits of x which starts from most significant bit position.
// __builtin_clz(16) = 27// int has 32 bits, because 16: "1 0000", has 5 bits, 32 - 5 = 27.
// __builtin_popcount(x) // returns number of 1-bits of x. x is unsigned int
// __builtin_popcount(14) = 3// because 14: "1110", has three 1-bits.

// #define int long long
#define rep(i, begin, end) \
  for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define pb push_back
#define all(x) (x).begin(), (x).end()
// #define type typename

using namespace std;
using ui = unsigned;
using cui = const unsigned;
using strs = std::stringstream;
using vii = std::vector<std::pair<int, int>>;
using vi = std::vector<int>;
using ii = std::pair<int, int>;

template<class T, class U> std::ostream &operator<<(ostream &os, pair<T, U> v)
{
  return os << "(" << v.first << "," << v.second << ")";
}

template<class T> std::ostream &operator<<(ostream &os, vector<T> v)
{
  for (auto &&e : v) { os << e << " "; }
  return os;
}

template<class T> std::ostream &operator<<(ostream &os, vector<long double> v)
{
  // for (auto &&e : v) { os << std::fixed << std::setprecision(15) << e << " "; }
  for (auto &&e : v) { os << std::fixed << std::setprecision(2) << e << " "; }
  return os;
}

template<class T> std::ostream &operator<<(ostream &os, vector<float> v)
{
  // for (auto &&e : v) { os << std::fixed << std::setprecision(6) << e << " "; }
  for (auto &&e : v) { os << std::fixed << std::setprecision(2) << e << " "; }
  return os;
}


long double distance(const vector<long double> &point_a, const vector<long double> &point_b)
{
  long double dist = 0;
  for (int i = 0; i < point_a.size(); i++) {
    // cout << "pre: " << std::fixed << std::setprecision(15) << point_a[i] << "  -  " << point_b[i] << "\n";
    // cout << "results: " << std::fixed << std::setprecision(15) << abs(point_a[i] - point_b[i]) << "\n";

    // dist += (abs(point_a[i] - point_b[i]) * abs(point_a[i] - point_b[i]));
    dist += (point_a[i] - point_b[i]) * (point_a[i] - point_b[i]);
    // cout << "dist: " << dist << endl;
  }

  return sqrt(dist);
}

using li_config =
  utils::RNG_Config<std::random_device, std::default_random_engine, long int, std::uniform_int_distribution<long int>>;
using i_config =
  utils::RNG_Config<std::random_device, std::default_random_engine, int, std::uniform_int_distribution<int>>;
using si_config = utils::
  RNG_Config<std::random_device, std::default_random_engine, short int, std::uniform_int_distribution<short int>>;


int main()
{

  using std::cout;
  using std::stringstream;
  using std::vector;

  using intType = long int;
  const intType n_max = 1'000'000;
  // 250000000000
  utils::RNG<li_config> rng_base(0, n_max);
  auto rng_between_0_and_1 = [&]() {
    auto enumerator = static_cast<long double>(rng_base());
    auto denominator = static_cast<long double>(n_max);
    auto result = enumerator / denominator;
    return result;
  };

  // vector<int> dims{ 10, 50, 100, 500, 1000, 2000, 5000 };
  vector<int> dims{ 2, 3, 4 };
  // vector<int> dims{ 10, 50 };
  // vector<int> dims{ 2 };
  // int n_points = 100;
  int n_points = 2;
  // int n_points = 10;

  for (int i = 0; i < 100; i++) {
    auto result = rng_between_0_and_1();
    if (result < -1 or result > 2) { cout << result << endl; }
  }
  cout << "-------------------" << endl;
  for (int i = 0; i < 100; i++) {
    auto result = rng_base();
    if (result < 0 or result > n_max) { cout << result << endl; }
  }

  return 0;
}

// int main()
// {

//   using std::cout;
//   using std::stringstream;
//   using std::vector;

//   using intType = long int;
//   const intType n_max = 1'000'000;
//   // 250000000000
//   utils::RNG<li_config> rng_base(0, n_max);
//   auto rng_between_0_and_1 = [&]() {
//     auto enumerator = static_cast<long double>(rng_base());
//     auto denominator = static_cast<long double>(n_max);
//     auto result = enumerator / denominator;
//     return result;
//   };

//   // vector<int> dims{ 10, 50, 100, 500, 1000, 2000, 5000 };
//   vector<int> dims{ 2, 3, 4 };
//   // vector<int> dims{ 10, 50 };
//   // vector<int> dims{ 2 };
//   // int n_points = 100;
//   int n_points = 2;
//   // int n_points = 10;

//   for (auto &&dim : dims) {
//     // string str;
//     // cin >> str;

//     vector<vector<long double>> points(n_points, vector<long double>(dim));// points between 0 and 1
//     vector<vector<long double>> dist_matrix(n_points, vector<long double>(n_points));// points between 0 and 1
//     for (int i = 0; i < n_points; i++) {
//       int counter = 0;

//       std::generate(all(points[i]), [&]() {
//         const intType center = 500'000;
//         const long double d_center = 0.5;
//         const intType r = 500'000;
//         const long double d_r = 0.5;

//         intType r2 = 250'000;
//         long double d_r2 = 0.25;

//         if (counter == 0) {
//           counter++;
//           auto result = rng_between_0_and_1();
//           return result;
//         }

//         // r2 -  all the others squared

//         for (int o = 0; o < counter; o++) {
//           // const long int p{ points[i][o] * n_max };
//           // const long int diff{ center - p };
//           const long double p{ points[i][o] };
//           const long double diff{ d_center - p };

//           // cout << "p:" << p << endl;
//           // cout << "diff:" << diff << endl;
//           // r2 -= ((diff) * (diff));
//           d_r2 -= ((diff) * (diff));
//         }

//         d_r2 = sqrt(d_r2);
//         // r2 = sqrt(r2);

//         // utils::RNG<li_config> rng_base2(center - r2, center + r2);
//         utils::RNG<li_config> rng_base2(center - (d_r2 * n_max), center + (d_r2 * n_max));
//         auto rng2 = [&]() { return static_cast<long double>(rng_base2()) / static_cast<long double>(n_max); };

//         counter++;
//         return rng2();
//       });
//       //
//     }

//     cout << "points: " << endl;
//     // std::string str = "";
//     // cin >> str;
//     for (int i = 0; i < n_points; i++) {
//       cout << "i: " << i << "\td: " << dim << endl;
//       for (auto &&p : points) { cout << std::fixed << std::setprecision(2) << p << " "; }
//       cout << endl;
//     }

//     // cout << points << endl;

//     // calcular distancias en una matriz
//     for (int x = 0; x < n_points; x++) {
//       for (int y = x + 1; y < n_points; y++) { dist_matrix[x][y] = distance(points[x], points[y]); }
//     }

//     for (int x = 0; x < n_points; x++) {
//       for (int y = x + 1; y < n_points; y++) { cout << std::fixed << std::setprecision(2) << dist_matrix[x][y] << "
//       "; }
//     }
//     cout << "\n";

//     // for (auto v : dist_matrix) {
//     //   for (auto e : v) { cout << std::fixed << std::setprecision(8) << e << " "; }
//     //   cout << "\n";
//     // }
//   }

//   // print_random_data(cout);

//   // std::ofstream out{ "" };
//   // print_random_data(out);
//   // 4951
//   return 0;
// }
