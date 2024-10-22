# RPatternJoin 1.0.0

## Submission Summary

This is the third attempt to submit the `RPatternJoin-1.0.0` package to CRAN. I addressed the reviewer's concerns about the previous attempt (see 'Answers on attempt 2 review comments' section) and reran all previous checks (see 'Test Info' section).

## Answers on attempt 2 review comments:

Dear Konstanze Lauseker, 
Thank you for reviewing my previous attempt I fixed the issues you pointed me on.

### \dontrun block
comment: _Please unwrap the examples if they are executable in < 5 sec, or replace
dontrun{} with \donttest{}._

response: Changed on \donttest.

### fixed seed
comment: _Please do not set a seed to a specific number within a function. ->
R/SimilarityJoin.R_

response: Deleted it.

## Answers on attempt 1 review comments:

Dear Beni Altmann thank you for reviewing my previous submission, here are my answers to your comments:

### references issue
comment: _If there are references describing the methods in your package, please add these in the description field of your DESCRIPTION file in the form
authors (year) <doi:...>
authors (year, ISBN:...)
or if those are not available: <[https:...]https:...>
with no space after 'doi:', 'https:' and angle brackets for
auto-linking. (If you want to add a title as well please put it in
quotes: "Title")_

response: The paper has not been published yet, so I deleted the references section from the `Description` file.

### acronyms issue
comment: _Please always explain all acronyms in the description text. -> TCR, BCR._

response: I deleted the words TCR and BCR and substituted them with "Adaptive Immune Repertoire".

### copyright holders issue
comment: _Please always add all authors, contributors and copyright holders in the
Authors@R field with the appropriate roles.
 From CRAN policies you agreed to:
"The ownership of copyright and intellectual property rights of all
components of the package must be clear and unambiguous (including from
the authors specification in the DESCRIPTION file). Where code is copied
(or derived) from the work of others (including from R itself), care
must be taken that any copyright/license statements are preserved and
authorship is not misrepresented.
Preferably, an ‘Authors@R’ would be used with ‘ctb’ roles for the
authors of such code. Alternatively, the ‘Author’ field should list
these authors as contributors. Where copyrights are held by an entity
other than the package authors, this should preferably be indicated via
‘cph’ roles in the ‘Authors@R’ field, or using a ‘Copyright’ field (if
necessary referring to an inst/COPYRIGHTS file)."
e.g.: " Martin Leitner-Ankerl" in unordered_dense.h
Please explain in the submission comments what you did about this issue._

response: I added the following fields to the 'Authors@R':
```r
person(given = "Martin",
        family = "Leitner-Ankerl",
        role = c("ctb", "cph"),
        email = "martin.ankerl@gmail.com"),
person(given = "Gene",
        family = "Harvey",
        role = c("ctb", "cph"),
        email = "gharveymn@gmail.com")
```

### small package size issue

comment: _Your package is fairly small (only 37 R code lines). CRAN is a
repository for fully developed packages. If you plan to add more
functionalities, please add them before resubmitting. Else, please let
us know that your package is fully developed._

response: The package is fully developed. To address your concerns about the package being small and highlight the non-trivial contribution of the package I added a larger example to the `RPatternJoin-package.Rd` and `similarityJoin.Rd` files. In this example you can see that the same similarity join task takes `63.773 seconds` if you use the `stringdist::stringdistmatrix` function and `0.105 seconds` if you use the `similarityJoin` function from this package. The main contribution of the package is in providing fast algorithms for similarity join tasks. According to my tests (for the paper which is currently in progress) the algorithms we developed are faster than all alternative algorithms for types of input data described in `Description` file. 

## Test Info

### Test Environments

- Local macOS 15.0 (R 4.3.1)
- R-hub (linux, macos, macos-arm64, windows)
- win-builder (windows server)

### R CMD check results

There were no ERRORs or WARNINGs.

### R-hub results

Checked on the following platforms:
- Ubuntu Linux 20.04.5 LTS, R-devel
- macOS 13.7 22H123, R-devel
- macOS 14.7 23H124, R-devel
- Microsoft Windows Server 2022 10.0.20348 Datacenter, R-devel

All checks passed without any issues.

### win-builder results

Checked on the following platforms:
- Windows Server 2022, R-devel

All checks passed without any issues.

### Additional Notes

- The package includes documentation and examples for all exported functions.
- The package includes unit tests that uniformly cover all input data.

Thank you for reviewing our submission.