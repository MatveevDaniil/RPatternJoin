#ifndef DUPLICATES_SEARCH_HPP
#define DUPLICATES_SEARCH_HPP

#include "file_io.hpp"
#include "hash_containers.hpp"

// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>

void duplicates_search(
  const std::vector<std::string>& strings,
  arma::sp_umat& adj_matrix
) {
  int n = strings.size();

  str2ints str2idxs;
  str2idxs.reserve(n);
  for (int i = 0; i < n; i++) {
    if (i % 10000 == 0)
      Rcpp::checkUserInterrupt();
    str2idxs[strings[i]].push_back(i);
  }
  
  for (const auto& entry : str2idxs) {
    Rcpp::checkUserInterrupt();
    for (auto i: entry.second)
      for (auto j: entry.second)
        adj_matrix(i, j) = 1;
  }
}

#endif // DUPLICATES_SEARCH_HPP