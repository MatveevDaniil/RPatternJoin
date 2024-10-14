#include "sim_search_semi_patterns.hpp"

void sim_search_semi_patterns(
  const std::vector<std::string>& strings,
  int cutoff,
  char metric,
  arma::sp_umat& adj_matrix
) {
  int n = strings.size();

  str2int str2idx;
  str2ints str2idxs;
  countStrings(strings, str2idx, str2idxs);

  int_pair_set idx_pairs;
  sim_search_semi_patterns_impl<TrimDirection::No>(strings, cutoff, metric, str2idx, idx_pairs, nullptr, true);
  pairSetToAdjMatrix(idx_pairs, adj_matrix, strings, str2idxs);
}