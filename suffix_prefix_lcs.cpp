#include "suffix_prefix_lcs.h"

std::vector<
        std::vector<size_t>
> calculateSuffixPrefixLCS(const std::string &A, const std::string &B)
{
    size_t n = A.size(),
           m = B.size();
    std::vector< std::vector<size_t> > dp (n + 1, std::vector<size_t>(m + 1, 0));

    return dp;
}
