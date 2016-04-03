#include <iostream>
#include "suffix_prefix_lcs.h"
#include "suffix_prefix_lcs_long.h"
#include <gtest/gtest.h>
#include <random>

class SuffixPrefixLCSTests : public ::testing::Test
{
public:
    virtual void SetUp()
    {
        engine.seed(42 + 666 * 13);
    }

    virtual void TearDown()
    { }

    virtual void Init(const std::string &A, const std::string &B)
    {
        A_ = A;
        B_ = B;
    }

    virtual void GenerateTest(size_t ASize, size_t BSize,
                              int salt=42 + 666 * 13, char lowSym='a', char highSym='z')
    {
        engine.seed(salt + (ASize * BSize + (highSym - lowSym)) % 1000000009);
        randomSymbol = std::uniform_int_distribution<char>(lowSym, highSym);
        A_.resize(ASize);
        B_.resize(BSize);
        for (size_t i = 0; i < ASize; ++i)
        {
            A_[i] = randomSymbol(engine);
        }
        for (size_t j = 0; j < BSize; ++j) {
            B_[j] = randomSymbol(engine);
        }
    }

    virtual void GenerateRightAnswer()
    {
        ans_ = calculateSuffixPrefixLCS_long2(A_, B_);
    }

    virtual void CalculateAnswer()
    {
        test_ = calculateSuffixPrefixLCS(A_, B_);
    }

    void Compare()
    {
        size_t n = A_.size(),
               m = B_.size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                EXPECT_EQ(ans_[i][j], test_[i][j])
                                    << "for substring A[" << i + 1 << "..|A|]=\""
                                    << A_.substr(i) << "\"" <<std::endl
                                    << "for substring B[1.." << j << "]=\""
                                    << B_.substr(1, j + 1) << "\"" << std::endl;
            }
        }
    }

protected:
    std::default_random_engine engine;
    std::uniform_int_distribution<char> randomSymbol;
    std::uniform_int_distribution<size_t> randomRange;
    std::string A_, B_;
    std::vector< std::vector <size_t> > ans_, test_;
};

TEST_F(SuffixPrefixLCSTests, smallTest)
{
    std::string A = "abcdef";
    std::string B = "cgabdfe";
    Init(A, B);
    GenerateRightAnswer();
    std::cout << "simple test right answer and our answer:" << std::endl;
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < B.size(); ++j) {
            std::cout << ans_[i][j] << " ";
        }
        std::cout << std::endl;
    }
    CalculateAnswer();
    std::cout << std::endl;
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < B.size(); ++j) {
            std::cout << test_[i][j] << " ";
        }
        std::cout << std::endl;
    }
    Compare();
}

TEST_F(SuffixPrefixLCSTests, simpleTests)
{
    int tests = 100;
    size_t AMaxSize = 15;
    size_t BMaxSize = 15;
    for (int t = 0; t < tests; ++t) {
        GenerateTest(AMaxSize, BMaxSize, t);
        //std::cout << A_ << std::endl;
        //std::cout << B_ << std::endl;
        GenerateRightAnswer();
        CalculateAnswer();
        Compare();
    }
}

TEST_F(SuffixPrefixLCSTests, extremeTests)
{
    size_t maxTestSize = 2000;
    for (int t = 0; t < 5; ++t) {
        std::cout << "starting extreme test #" << t << std::endl;
        std::cout << "part 1: 1x1" << std::endl;
        GenerateTest(1, 1, t, ' ', 'z');
        GenerateRightAnswer();
        CalculateAnswer();
        Compare();
        std::cout << "part 2: 1xMAX" << std::endl;
        GenerateTest(1, maxTestSize, t, ' ', 'z');
        GenerateRightAnswer();
        CalculateAnswer();
        Compare();
        std::cout << "part 3: MAXx1" << std::endl;
        GenerateTest(maxTestSize, 1, t, ' ', 'z');
        GenerateRightAnswer();
        CalculateAnswer();
        Compare();
    }
}
TEST_F(SuffixPrefixLCSTests, regularTests)
{
    size_t maxTestSize = 100;
    int tests = 100;
    randomRange = std::uniform_int_distribution<size_t>(1, maxTestSize - 1);
    for (int t = 0; t < tests; ++t) {
        GenerateTest(randomRange(engine), randomRange(engine), t, 'a', 'z');
        //std::cout << A_ << std::endl;
        //std::cout << B_ << std::endl;
        //std::cout << "O(n^3)" << std::endl;
        GenerateRightAnswer();
        //std::cout << "O(n^2)" << std::endl;
        CalculateAnswer();
        Compare();
    }
}


TEST_F(SuffixPrefixLCSTests, BigTests)
{
    size_t maxTestSize = 700;
    int tests = 5;
    randomRange = std::uniform_int_distribution<size_t>(maxTestSize / 2, maxTestSize - 1);
    for (int t = 0; t < tests; ++t) {
        GenerateTest(randomRange(engine), randomRange(engine), t, ' ', 127);
        //std::cout << A_ << std::endl;
        //std::cout << B_ << std::endl;
        std::cout << "generated test size " << A_.size() << "x" << B_.size() << std::endl;
        std::cout << "starting dp O(n^3) solution" << std::endl;
        GenerateRightAnswer();
        std::cout << "starting super dp O(n^2) solution" << std::endl;
        CalculateAnswer();
        Compare();
    }
}

TEST_F(SuffixPrefixLCSTests, MaxTests)
{
    size_t maxTestSize = 2000;
    int tests = 4;
    randomRange = std::uniform_int_distribution<size_t>(maxTestSize / 2, maxTestSize - 1);
    for (int t = 0; t < tests; ++t) {
        GenerateTest(randomRange(engine), randomRange(engine), t, ' ', 127);
        //std::cout << A_ << std::endl;
        //std::cout << B_ << std::endl;
        std::cout << "generated test size " << A_.size() << "x" << B_.size() << std::endl;
        std::cout << "starting dp O(n^3) solution" << std::endl;
        GenerateRightAnswer();
        std::cout << "starting super dp O(n^2) solution" << std::endl;
        CalculateAnswer();
        Compare();
    }
}

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
