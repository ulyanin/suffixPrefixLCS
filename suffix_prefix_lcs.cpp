#include "suffix_prefix_lcs.h"
#include <iostream>

std::vector<
        std::vector<size_t>
> calculateSuffixPrefixLCS_reversed(const std::string &A, const std::string &B)
{
    size_t n = A.size(),
           m = B.size();
    std::vector< std::vector<size_t> > ans(n, std::vector<size_t>(m));
    std::vector< std::vector<size_t> > criticalMomentsVertical(n + 1, std::vector<size_t>(m + 1, 0));
    std::vector< std::vector<size_t> > criticalMomentsHorizontal(n + 1, std::vector<size_t>(m + 1, 0));
    for (size_t j = 0; j <= m; ++j) {
        criticalMomentsHorizontal[0][j] = j + 1;
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            size_t x = criticalMomentsVertical[i][j];
            size_t y = criticalMomentsHorizontal[i][j];
            size_t &w = criticalMomentsHorizontal[i + 1][j];
            size_t &z = criticalMomentsVertical[i][j + 1];
            if (x < y) {
                if (A[i] == B[j]) {
                    w = x;
                    z = y;
                } else {
                    w = y;
                    z = x;
                }
            } else {
                w = x;
                z = y;
            }
        }
    }
    /*for (size_t i = 0; i <= n; ++i) {
        for (size_t j = 0; j <= m; ++j) {
            std::cout << criticalMomentsVertical[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (size_t i = 0; i <= n; ++i) {
        for (size_t j = 0; j <= m; ++j) {
            std::cout << criticalMomentsHorizontal[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;*/
    for (size_t j = 0; j < m; ++j) {
        ans[0][j] = (j < criticalMomentsVertical[0][m] ? 1 : 0);
    }
    for (size_t i = 1; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            ans[i][j] = ans[i - 1][j] + (j < criticalMomentsVertical[i][m] ? 1 : 0);
        }
    }
    return ans;
}


std::vector<
        std::vector<size_t>
> calculateSuffixPrefixLCS(const std::string &A, const std::string &B)
{
    size_t n = A.size(),
            m = B.size();
    std::vector< std::vector<size_t> > ans(n, std::vector<size_t>(m));
    auto tmp = calculateSuffixPrefixLCS_reversed(B, A);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ans[i][j] = tmp[j][i];
        }
    }
    return ans;
}