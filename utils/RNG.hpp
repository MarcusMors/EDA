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

#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <sstream>
#include <string>

using ull = unsigned long long;
using ul = unsigned long;
using ui = unsigned;
using ill = long long;

namespace utils {


using namespace std;

template<class T_Seed = std::random_device,
  class T_Engine = std::default_random_engine,
  class T_intType = short int,
  class T_Distribution = std::uniform_int_distribution<T_intType>>
struct RNG_Config
{
  using Seed = T_Seed;
  using Engine = T_Engine;
  // supported int Types // check https://en.cppreference.com/w/cpp/header/random
  // short, int, long, long long,
  // ui short, ui int, ui long, or ull
  using intType = T_intType;
  using Distribution = T_Distribution;
};

template<class Config = RNG_Config<>> class RNG
{
private:
  using Seed = typename Config::Seed;
  using Engine = typename Config::Engine;
  using intType = typename Config::intType;
  using Distribution = typename Config::Distribution;

  Seed seed;
  Engine engine{ seed() };
  const intType m_max{ std::numeric_limits<intType>::max() };
  const intType m_min{ std::numeric_limits<intType>::min() };
  Distribution distribution = Distribution(m_min, m_max);

public:
  intType max() const { return m_max; }
  intType min() const { return m_min; }

  RNG(intType t_min, intType t_max) : m_min{ t_min }, m_max{ t_max }, distribution{ Distribution(m_min, m_max) } {}
  RNG() {}

  intType operator()() { return distribution(engine); }
};


using li_config =
  utils::RNG_Config<std::random_device, std::default_random_engine, long int, std::uniform_int_distribution<long int>>;
using i_config =
  utils::RNG_Config<std::random_device, std::default_random_engine, int, std::uniform_int_distribution<int>>;
using si_config = utils::
  RNG_Config<std::random_device, std::default_random_engine, short int, std::uniform_int_distribution<short int>>;

}// namespace utils
