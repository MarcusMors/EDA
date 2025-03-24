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

template<class T> std::ostream &operator<<(ostream &os, vector<double> v)
{
  for (auto &&e : v) { os << std::fixed << std::setprecision(15) << e << " "; }
  return os;
}

template<class T> std::ostream &operator<<(ostream &os, vector<float> v)
{
  for (auto &&e : v) { os << std::fixed << std::setprecision(6) << e << " "; }
  return os;
}


double distance(const vector<double> &point_a, const vector<double> &point_b)
{
  double dist = 0;
  for (int i = 0; i < point_a.size(); i++) {
    // cout << "pre: " << std::fixed << std::setprecision(15) << point_a[i] << "  -  " << point_b[i] << "\n";
    // cout << "results: " << std::fixed << std::setprecision(15) << abs(point_a[i] - point_b[i]) << "\n";

    // dist += (abs(point_a[i] - point_b[i]) * abs(point_a[i] - point_b[i]));
    dist += (point_a[i] - point_b[i]) * (point_a[i] - point_b[i]);
    // cout << "dist: " << dist << endl;
  }

  return sqrt(dist);
}


template<class OutStreamType = std::ostream> void print_random_data(OutStreamType &out_stream, int dimensions)
{
  using intType = int;
  const intType n_max = 1'000'000;
  utils::RNG<> rng_base(0, n_max);
  auto rng_between_0_and_1 = [&]() { return double(double(rng_base()) / double(n_max)); };

  using std::endl;
  for (intType i = 0; i < dimensions; i++) { out_stream << rng_between_0_and_1() << ' '; }
  out_stream << endl;
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
  // vector<int> dims{ 10, 50 };
  // vector<int> dims{ 2 };
  int n_points = 100;
  // int n_points = 10;

  for (auto &&dim : dims) {
    // string str;
    // cin >> str;

    vector<vector<double>> points(n_points, vector<double>(dim));// points between 0 and 1
    vector<vector<double>> dist_matrix(n_points, vector<double>(n_points));// points between 0 and 1

    for (int i = 0; i < n_points; i++) { std::generate(all(points[i]), rng_between_0_and_1); }

    // cout << "points: " << endl;
    // cin >> str;
    // for (int i = 0; i < n_points; i++) {
    //   cout << "i: " << i << endl;
    //   for (auto &&p : points) { cout << p << " "; }
    //   cout << endl;
    // }

    // cout << points << endl;

    // calcular distancias en una matriz
    for (int x = 0; x < n_points; x++) {
      for (int y = x + 1; y < n_points; y++) { dist_matrix[x][y] = distance(points[x], points[y]); }
    }

    for (int x = 0; x < n_points; x++) {
      for (int y = x + 1; y < n_points; y++) { cout << std::fixed << std::setprecision(8) << dist_matrix[x][y] << " "; }
    }
    cout << "\n";

    // for (auto v : dist_matrix) {
    //   for (auto e : v) { cout << std::fixed << std::setprecision(8) << e << " "; }
    //   cout << "\n";
    // }
  }

  // print_random_data(cout);

  // std::ofstream out{ "" };
  // print_random_data(out);
  // 4951
  return 0;
}
