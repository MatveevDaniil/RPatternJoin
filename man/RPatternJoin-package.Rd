\name{RPatternJoin-package}
\alias{RPatternJoin-package}
\alias{RPatternJoin}
\docType{package}
\title{
  String Similarity Joins for Hamming and Levenshtein Distances
}
\description{
  This project is a tool for words edit similarity joins under small (< 3) edit distance constraints. 
  It works for Levenshtein distance and Hamming (with allowed insertions/deletions to the end) distance. 
  The software is specifically optimized for edit similarity joins of amino-acid sequences from TCR/BCR profiles, 
  where the number of words is relatively large (10^5-10^6) and the average length of words is relatively small (~20).
}
\details{
  This R package serves as a wrapper for a C++ package. 
  More information about the original C++ package can be found on GitHub at \href{https://github.com/MatveevDaniil/PatternJoin}{PatternJoin}. 
  The package offers several similarity join algorithms, all of which can be accessed through the \code{\link[=buildAdjacencyMatrix]{buildAdjacencyMatrix}} function.}
\author{
Daniil Matveev <dmatveev@sfsu.edu>
}
\references{
  paper is in progress...
}
\keyword{ package }
