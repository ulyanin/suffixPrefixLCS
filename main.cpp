#include <iostream>
#include "suffix_prefix_lcs.h"
#include "suffix_prefix_lcs_long.h"
#include <gtest/gtest.h>
#include <random>

class SuffixPrefixLCSgenTests : public ::testing::Test
{
public:
    virtual void SetUp()
    {
        engine.seed(42 + 666 * 13);
    }

    virtual void TearDown()
    { }

protected:
    std::default_random_engine engine;
    std::uniform_int_distribution<char> randomSymbol;
};


int main(int argc, char ** argv)
{
    //testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
    std::string A = "abcdef";
    std::string B = "cgabdfe";
    auto arr = calculateSuffixPrefixLCS(A, B);
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < B.size(); ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
