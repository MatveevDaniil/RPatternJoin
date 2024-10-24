// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// similarityJoin
Rcpp::List similarityJoin(const std::vector<std::string>& strings, int cutoff, char metric, std::string method, bool drop_deg_one, std::string output_format);
RcppExport SEXP _RPatternJoin_similarityJoin(SEXP stringsSEXP, SEXP cutoffSEXP, SEXP metricSEXP, SEXP methodSEXP, SEXP drop_deg_oneSEXP, SEXP output_formatSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<std::string>& >::type strings(stringsSEXP);
    Rcpp::traits::input_parameter< int >::type cutoff(cutoffSEXP);
    Rcpp::traits::input_parameter< char >::type metric(metricSEXP);
    Rcpp::traits::input_parameter< std::string >::type method(methodSEXP);
    Rcpp::traits::input_parameter< bool >::type drop_deg_one(drop_deg_oneSEXP);
    Rcpp::traits::input_parameter< std::string >::type output_format(output_formatSEXP);
    rcpp_result_gen = Rcpp::wrap(similarityJoin(strings, cutoff, metric, method, drop_deg_one, output_format));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_RPatternJoin_similarityJoin", (DL_FUNC) &_RPatternJoin_similarityJoin, 6},
    {NULL, NULL, 0}
};

RcppExport void R_init_RPatternJoin(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
