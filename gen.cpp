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

#define fastio()                         \
  std::ios_base::sync_with_stdio(false); \
  std::cin.tie(NULL);                    \
  std::cout.tie(NULL)

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


template<class OutStreamType = std::ostream> void print_random_data(OutStreamType &out_stream, int dimensions)
{
  using Seed = std::random_device;
  using Engine = std::default_random_engine;
  // supported int Types // check https://en.cppreference.com/w/cpp/header/random
  // short, int, long, long long,
  // unsigned short, unsigned int, unsigned long, or unsigned long long
  using intType = int;
  using Distribution = std::uniform_int_distribution<intType>;

  Seed seed;
  Engine engine{ seed() };

  const intType n_max = 1'000'000;
  const intType n_min = 0;
  Distribution n_distribution(n_min, n_max);
  auto generate_n = [&]() { return n_distribution(engine); };

  using std::endl;
  for (intType i = 0; i < dimensions; i++) { out_stream << double(double(generate_n()) / double(n_max)) << ' '; }
  out_stream << endl;
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

int main()
{
  using std::cout;
  using std::stringstream;
  using std::vector;
  vector<int> dims{ 10, 50, 100, 500, 1000, 2000, 5000 };
  int n_points = 100;

  for (auto &&dim : dims) {
    // string str;
    // cin >> str;

    vector<vector<double>> points(100, vector<double>(dim));// points between 0 and 1
    vector<vector<double>> dist_matrix(100, vector<double>(100));// points between 0 and 1

    for (int i = 0; i < n_points; i++) {
      stringstream point;
      print_random_data(point, dim);
      cout << point.str() << endl;

      vector<double> vals_of_point{};
      for (int d = 0; d < dim; d++) {
        double val;
        point >> val;
        vals_of_point.push_back(val);
      }
      points[i] = (vector<double>(all(vals_of_point)));
    }

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
      for (int y = x + 1; y < n_points; y++) {
        cout << std::fixed << std::setprecision(1) << dist_matrix[x][y] << " ";
        // dist_matrix[x][y] = distance(points[x], points[y]);
      }
      cout << "\n";
    }

    // for (auto v : dist_matrix) {
    //   for (auto e : v) { cout << std::fixed << std::setprecision(8) << e << " "; }
    //   cout << "\n";
    // }
  }

  // print_random_data(cout);

  // std::ofstream out{ "" };
  // print_random_data(out);

  return 0;
}
