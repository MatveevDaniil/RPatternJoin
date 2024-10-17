.checkStringList <- function(strings) {
  invalid_strings <- which(!nzchar(strings) | !grepl("^[A-Za-z]+$", strings))
  if (length(invalid_strings) > 0) {
    special_chars <- lapply(
      strings[invalid_strings],
      function(s) {
        unique(unlist(strsplit(s, ""))[!grepl("^[A-Za-z]$", unlist(strsplit(s, "")))])
      }
    )
    warning(
      "Warning: The `strings` vector contains lines with special characters: ",
      paste(special_chars, collapse = ", "),
      "\nTo disable this warning, change special_chars_warning to FALSE."
    )
  }
}

.buildAdjacencyMatrixCheckArgs <- function(
  strings,
  cutoff,
  metric,
  method,
  drop_deg_one,
  special_chars
) {
  if (!is.character(strings) || length(strings) == 0)
    stop("Error: `strings` must be a non-empty character vector.")
  if (special_chars)
    .checkStringList(strings)
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
#' @param strings Input vector of strings. To avoid hidden errors, function will give a warning if strings contain special characters. To disable this warning, change special_chars to FALSE.
#' @param cutoff Cutoff: 0,1,2. Algorithm will search all pairs of strings with edit distance less than or equal to the cutoff.
#' @param metric Edit distance type: "Hamming", "Levenshtein".
#' @param method Method: "partition_pattern", "semi_pattern", "pattern". By default we recommend using "partition_pattern".
#' @param drop_deg_one Drop isolated strings: TRUE, FALSE.
#' @param special_chars Enable check for special characters in strings: TRUE, FALSE.
#'
#' @return A sparse adjacency matrix.
#' @export
#'
#' @examples
#' library(RPatternJoin)
#' library(Matrix)
#'
#' ## Example 1
#' strings <- c("banana", "ananas", "banuna", "ant", "cart")
#' cutoff <- 2
#' metric <- "Levenshtein"
#' method <- "partition_pattern"
#' drop_deg_one <- TRUE
#' adj_matrix <- buildAdjacencyMatrix(strings, cutoff, metric, method, drop_deg_one)
#'
#' ## Example 2
#' strings <- c("AB", "ABC", "ACC", "AC")
#' cutoff <- 1
#' metric <- "Hamming"
#' method <- "semi_pattern"
#' drop_deg_one <- FALSE
#' adj_matrix <- buildAdjacencyMatrix(strings, cutoff, metric, method, drop_deg_one)
buildAdjacencyMatrix <- function(
  strings,
  cutoff,
  metric,
  method,
  drop_deg_one,
  special_chars = TRUE
) {
  .buildAdjacencyMatrixCheckArgs(strings, cutoff, metric, method, drop_deg_one, special_chars)
  metric <- substr(metric, 1, 1)
  result <- .buildAdjacencyMatrix(strings, cutoff, metric, method, drop_deg_one)
  adj_matrix <- result$adj_matrix
  non_triv_ids <- result$non_triv_ids
  dimnames(adj_matrix)[[1]] <- non_triv_ids
  dimnames(adj_matrix)[[2]] <- strings[non_triv_ids]
  return(adj_matrix)
}