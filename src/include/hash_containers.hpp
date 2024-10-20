#ifndef HASHMAP_CONTAINERS_HPP
#define HASHMAP_CONTAINERS_HPP

#include "unordered_dense.h"
#include "small_vector.hpp"

using str2int = ankerl::unordered_dense::map<std::string, int>;
using ints = gch::small_vector<int>;
using str2ints = ankerl::unordered_dense::map<std::string, ints>;
using int_pair_set = ankerl::unordered_dense::set<std::pair<int, int>>;
using str_pair_set = ankerl::unordered_dense::set<std::pair<std::string, std::string>>;

#endif // HASHMAP_CONTAINERS_HPP
