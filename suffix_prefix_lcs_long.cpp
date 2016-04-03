#include "suffix_prefix_lcs_long.h"
#include <iostream>
#include <cstring>

using std::size_t;

// O(|A| * |B|) memory
std::vector< std::vector<size_t> > calculateSuffixPrefixLCS_long(const std::string &A, const std::string &B)
{
    const std::string &s = B;
    const std::string &t = A;
    std::vector< std::vector<size_t> > ans(t.size(),
                 std::vector<size_t > (s.size())
    );
    int n = s.length();
    int m = t.length();
    //size_t dp[m + 1][n + 1];
    std::vector< std::vector<size_t> > dp(
            std::vector<std::vector<size_t > > (m + 1, std::vector<size_t > (n + 1))
    );
    for (int i = 0; i < m; ++i) {
        // for step Zi dp[j][k] = lcs(t[i..j], s[1..k])
        for (int k = 1; k <= n; ++k) {
            dp[i][k] = std::max((size_t)(t[i] == s[k - 1]), dp[i][k - 1]);
        }
        for (int j = i + 1; j < m; ++j) {
            for (int k = 1; k <= n; ++k) {
                dp[j][k] = std::max(dp[j - 1][k], dp[j][k - 1]);
                if (t[j] == s[k - 1])
                    dp[j][k] = std::max(dp[j][k], dp[j - 1][k - 1] + 1);
            }
        }
        for (int k = 1; k <= n; ++k)
            ans[i][k - 1] = dp[m - 1][k];
    }
    return ans;
}

// O(|A|*|A|) memory
std::vector< std::vector<size_t> > calculateSuffixPrefixLCS_long2(const std::string &A, const std::string &B)
{
    const std::string &s = B;
    const std::string &t = A;
    int n = s.length();
    int m = t.length();
    std::vector< std::vector<size_t> > ans(m,
                 std::vector<size_t > (n)
    );
    //size_t dp[2][m + 1][m + 1];
    std::vector< std::vector<size_t> > dp[2];
    for (int i = 0; i < 2; ++i)
        dp[i] = std::vector<std::vector<size_t > > (m + 1, std::vector<size_t > (m + 1));
    for (int k = 1; k <= n; ++k) {
        dp[k & 1].assign(m + 1, std::vector<size_t > (m + 1, 0));
        //memset(dp[k & 1], 0, sizeof(dp[k & 1]));
        for (int i = 0; i < m; ++i) {
            // for step k, i dp[k][i][j] = lcs(t[i..j], s[1..k])
            // and for step k only two arrays, because other k do not needed
            dp[k & 1][i][i] = std::max((size_t)(t[i] == s[k - 1]), dp[(k + 1) & 1][i][i]);
            for (int j = i + 1; j < m; ++j) {
                dp[k & 1][i][j] = std::max(dp[k & 1][i][j - 1], dp[(k + 1) & 1][i][j]);
                if (t[j] == s[k - 1])
                    dp[k & 1][i][j] = std::max(dp[k & 1][i][j], dp[(k + 1) & 1][i][j - 1] + 1);
                if (j == m - 1)
                    ans[i][k - 1] = dp[k & 1][i][j];
            }
        }
        ans[m - 1][k - 1] = dp[k & 1][m - 1][m - 1];
    }
    return ans;
}