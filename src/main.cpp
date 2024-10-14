#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include "getopt.h"
#include "duplicates_search.hpp"
#include "sim_search_patterns.hpp"
#include "sim_search_semi_patterns.hpp"
#include "sim_search_part_patterns.hpp"

// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
#include <Rcpp.h>


void check_validity(int cutoff, char metric, const std::string& method) {
  std::set<int> valid_cutoffs = {0, 1, 2};
  std::set<char> valid_metrics = {'L', 'H'};
  std::set<std::string> valid_methods = {"pattern", "semi_pattern", "partition_pattern"};

  if (valid_cutoffs.count(cutoff) == 0)
    throw std::invalid_argument("Invalid cutoff value");

  if (valid_metrics.count(metric) == 0)
    throw std::invalid_argument("Invalid metric value");

  if (valid_methods.count(method) == 0)
    throw std::invalid_argument("Invalid method value");
}


void dropDegreeOne(
  arma::sp_umat& adj_matrix,
  std::vector<int>& non_triv_ids
) {
  arma::sp_umat col_sums = arma::sum(adj_matrix, 0);
  arma::uvec _non_triv_ids = arma::find(col_sums > 1);

  adj_matrix = adj_matrix.cols(_non_triv_ids).t();
  adj_matrix = adj_matrix.cols(_non_triv_ids).t();
  
  for (int i = 0; i < _non_triv_ids.n_elem; i++)
    non_triv_ids[i] = _non_triv_ids[i] + 1;
  non_triv_ids.resize(_non_triv_ids.n_elem);
}


// [[Rcpp::export(".buildAdjacencyMatrix")]]
Rcpp::List buildAdjacencyMatrix(
  const std::vector<std::string>& strings,
  int cutoff,
  char metric,
  std::string method,
  bool drop_deg_one
) {
  int n = strings.size();

  arma::sp_umat adj_matrix(n, n);

  if (cutoff == 0)
    duplicates_search(strings, adj_matrix);
  else {
    if (method == "pattern")
      sim_search_patterns(strings, cutoff, metric, adj_matrix);
    else if (method == "semi_pattern")
      sim_search_semi_patterns(strings, cutoff, metric, adj_matrix);
    else if (method == "partition_pattern")
      sim_search_part_patterns(strings, cutoff, metric, adj_matrix);
  }

  std::vector<int> non_triv_ids(n);
  
  if (drop_deg_one)
    dropDegreeOne(adj_matrix, non_triv_ids);
  else 
    for (int i = 0; i < n; i++)
      non_triv_ids[i] = i + 1;

  return Rcpp::List::create(
    Rcpp::Named("adj_matrix") = adj_matrix,
    Rcpp::Named("non_triv_ids") = non_triv_ids);
}