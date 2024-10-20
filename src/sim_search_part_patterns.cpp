#include "include/sim_search_part_patterns.hpp"
#include <chrono>
#include <iostream>

void sim_search_2parts(
  const std::vector<std::string> &strings,
  char metric,
  str2int& str2idx,
  int_pair_set& out,
  bool include_eye = true,
  int cutoff = 1
) {
  str2ints start2idxs, end2idxs;
  start2idxs.reserve(strings.size());
  end2idxs.reserve(strings.size());
  if (metric == 'L')
    for (int i = 0; i < strings.size(); i++) {
      if (i % 1000 == 0)
        Rcpp::checkUserInterrupt();
      std::string str = strings[i];
      int half_len = str.size() / 2;
      start2idxs[str.substr(0, half_len)].push_back(i);
      end2idxs[str.substr(half_len)].push_back(i);
      if (str.size() % 2 == 1) {
        start2idxs[str.substr(0, half_len + 1)].push_back(i);
        end2idxs[str.substr(half_len + 1)].push_back(i);
      }
    }
  else
    for (int i = 0; i < strings.size(); i++) {
      if (i % 1000 == 0)
        Rcpp::checkUserInterrupt();
      std::string str = strings[i];
      int half_len = str.size() / 2;
      if (str.size() % 2 == 0) {
        start2idxs[str.substr(0, half_len)].push_back(i);
        end2idxs[str.substr(half_len)].push_back(i);
      }
      else {
        start2idxs[str.substr(0, half_len)].push_back(i);
        start2idxs[str.substr(0, half_len + 1)].push_back(i);
        end2idxs[str.substr(half_len + 1)].push_back(i);
      }
    }
  
  check_part<TrimDirection::Start>(strings, cutoff, metric, str2idx, start2idxs, out);
  check_part<TrimDirection::End>(strings, cutoff, metric, str2idx, end2idxs, out);
  
  if (include_eye)
    for (int i = 0; i < strings.size(); i++)
      out.insert({i, i});
}

void sim_search_3parts(
  const std::vector<std::string> &strings,
  char metric,
  str2int& str2idx,
  int_pair_set& out,
  bool include_eye = true,
  int cutoff = 1
) {
  str2ints start2idxs, mid2idxs, end2idxs;
  start2idxs.reserve(strings.size());
  mid2idxs.reserve(strings.size());
  end2idxs.reserve(strings.size());
  if (metric == 'L')
    for (int i = 0; i < strings.size(); i++) {
      if (i % 1000 == 0)
        Rcpp::checkUserInterrupt();
      std::string str = strings[i];
      int part_len = str.size() / 3;
      int residue = str.size() % 3;
      if (residue == 0) {
        start2idxs[str.substr(0, part_len)].push_back(i);
        mid2idxs[str.substr(part_len, part_len)].push_back(i);
        mid2idxs[str.substr(part_len - 1, part_len)].push_back(i);
        end2idxs[str.substr(part_len * 2)].push_back(i);
      } else if (residue == 1) {
        start2idxs[str.substr(0, part_len)].push_back(i);
        start2idxs[str.substr(0, part_len + 1)].push_back(i);
        mid2idxs[str.substr(part_len, part_len)].push_back(i);
        mid2idxs[str.substr(part_len + 1, part_len)].push_back(i);
        mid2idxs[str.substr(part_len, part_len + 1)].push_back(i);
        end2idxs[str.substr(part_len * 2)].push_back(i);
        end2idxs[str.substr(part_len * 2 + 1)].push_back(i);
      } else if (residue == 2) {
        start2idxs[str.substr(0, part_len)].push_back(i);
        start2idxs[str.substr(0, part_len + 1)].push_back(i);
        mid2idxs[str.substr(part_len + 1, part_len)].push_back(i);
        mid2idxs[str.substr(part_len + 1, part_len + 1)].push_back(i);
        mid2idxs[str.substr(part_len, part_len + 1)].push_back(i);
        end2idxs[str.substr(part_len * 2 + 1)].push_back(i);
        end2idxs[str.substr(part_len * 2 + 2)].push_back(i);
      }
    }
  else
    for (int i = 0; i < strings.size(); i++) {
      if (i % 1000 == 0)
        Rcpp::checkUserInterrupt();
      std::string str = strings[i];
      int part_len = str.size() / 3;
      int residue = str.size() % 3;
      if (residue == 0) {
        start2idxs[str.substr(0, part_len)].push_back(i);
        mid2idxs[str.substr(part_len, part_len)].push_back(i);
        end2idxs[str.substr(part_len * 2)].push_back(i);
      } else if (residue == 1) {
        start2idxs[str.substr(0, part_len)].push_back(i);
        start2idxs[str.substr(0, part_len + 1)].push_back(i);
        mid2idxs[str.substr(part_len, part_len)].push_back(i);
        mid2idxs[str.substr(part_len + 1, part_len)].push_back(i);
        end2idxs[str.substr(part_len * 2 + 1)].push_back(i);
      } else if (residue == 2) {
        start2idxs[str.substr(0, part_len)].push_back(i);
        start2idxs[str.substr(0, part_len + 1)].push_back(i);
        mid2idxs[str.substr(part_len + 1, part_len)].push_back(i);
        mid2idxs[str.substr(part_len + 1, part_len + 1)].push_back(i);
        end2idxs[str.substr(part_len * 2 + 2)].push_back(i);
      }
    }

  check_part<TrimDirection::Start>(strings, cutoff, metric, str2idx, start2idxs, out);
  start2idxs.clear();
  check_part<TrimDirection::Mid>(strings, cutoff, metric, str2idx, mid2idxs, out);
  mid2idxs.clear();
  check_part<TrimDirection::End>(strings, cutoff, metric, str2idx, end2idxs, out);
  if (include_eye)
    for (int i = 0; i < strings.size(); i++)
      out.insert({i, i});
}

void sim_search_part_patterns(
  const std::vector<std::string>& strings,
  int cutoff,
  char metric,
  str2ints& str2idxs,
  int_pair_set& out
) {
  str2int str2idx;
  countStrings(strings, str2idx, str2idxs);

  if (cutoff == 1)
    sim_search_2parts(strings, metric, str2idx, out, true, cutoff);
  else if (cutoff == 2)
    sim_search_3parts(strings, metric, str2idx, out, true, cutoff);
}
