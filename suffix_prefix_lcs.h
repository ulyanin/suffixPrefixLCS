#ifndef SUFFIX_PREFIX_LCS_H
#define SUFFIX_PREFIX_LCS_H

#include <vector>
#include <string>
#include <cstddef>

using std::size_t;

std::vector <
        std::vector <size_t>
> calculateSuffixPrefixLCS(const std::string &A, const std::string &B);

#endif //SUFFIX_PREFIX_LCS_H
