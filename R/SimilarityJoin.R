.buildAdjacencyMatrixCheckArgs <- function(
  strings,
  cutoff,
  metric,
  method,
  drop_deg_one
) {
  if (!is.character(strings) || length(strings) == 0)
    stop("Error: `strings` must be a non-empty character vector.")
  if (!is.numeric(cutoff) || !any(cutoff == c(0, 1, 2)))
    stop("Error: `cutoff` must be a numeric from (0, 1, 2).")
  if (!is.character(metric) || !any(metric == c("Hamming", "Levenshtein")))
    stop("Error: `metric` must be a string from (\"Hamming\", \"Levenshtein\").")
  if (!is.character(method) || !any(method == c("pattern", "semi_pattern", "partition_pattern")))
    stop("Error: `method` must be a string from (\"pattern\", \"semi_pattern\", \"partition_pattern\").")
  if (!is.logical(drop_deg_one))
    stop("Error: `drop_deg_one` must be a logical.")
}

#' Build Adjacency Matrix
#'
#' @param strings Input vector of strings.
#' @param cutoff Cutoff: 0,1,2.
#' @param metric Edit distance type: "Hamming", "Levenshtein".
#' @param method Method: "partition_pattern", "pattern", "semi_pattern".
#' @param drop_deg_one Drop isolated strings: TRUE, FALSE.
#'
#' @return A sparse adjacency matrix.
#' @export
#'
#' @examples
#' library(RPatternJoin)
#' library(Matrix)
#' strings <- c("banana", "ananas", "banuna", "ant", "cart")
#' cutoff <- 2
#' metric <- "Levenshtein"
#' method <- "partition_pattern"
#' drop_deg_one <- TRUE
#' adj_matrix <- buildAdjacencyMatrix(strings, cutoff, metric, method, drop_deg_one)
buildAdjacencyMatrix <- function(
  strings,
  cutoff,
  metric,
  method,
  drop_deg_one
) {
  .buildAdjacencyMatrixCheckArgs(strings, cutoff, metric, method, drop_deg_one)
  metric <- substr(metric, 1, 1)
  result <- .buildAdjacencyMatrix(strings, cutoff, metric, method, drop_deg_one)
  adj_matrix <- result$adj_matrix
  non_triv_ids <- result$non_triv_ids
  dimnames(adj_matrix)[[1]] <- non_triv_ids
  dimnames(adj_matrix)[[2]] <- strings[non_triv_ids]
  return(adj_matrix)
}
