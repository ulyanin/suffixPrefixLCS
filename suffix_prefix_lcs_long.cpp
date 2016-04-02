#include "suffix_prefix_lcs_long.h"
#include <iostream>
#include <cstring>

std::vector< std::vector<size_t> > calculateSuffixPrefixLCS_long(const std::string &A, const std::string &B)
{
    const std::string &s = B;
    const std::string &t = A;
    std::vector< std::vector<size_t> > ans(s.size(),
                 std::vector<size_t > (t.size())
    );
    int n = s.length();
    int m = t.length();
    size_t dp[m + 1][m + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < m; ++i) {
        for (int k = 1; k <= n; ++k) {
            dp[i][i][k] = std::max((size_t)(t[i] == s[k - 1]), dp[i][i][k - 1]);
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = i + 1; j < m; ++j) {
            for (int k = 1; k <= n; ++k) {
                dp[i][j][k] = std::max(dp[i][j - 1][k], dp[i][j][k - 1]);
                if (t[j] == s[k - 1])
                    dp[i][j][k] = std::max(dp[i][j][k], dp[i][j - 1][k - 1] + 1);
            }
        }
    }
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            //std::cout << dp[j][m - 1][i + 1] << " ";
            ans[j][i] = dp[j][m - 1][i + 1];
        }
        //std::cout << std::endl;
    }
    return ans;
}