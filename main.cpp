#include <iostream>
#include <fstream>
#include "suffix_prefix_lcs.h"
#include "suffix_prefix_lcs_long.h"
#include <gtest/gtest.h>
#include <random>
#include <chrono>

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

    virtual double GenerateRightAnswer()
    {
        auto start(std::chrono::steady_clock::now());
        ans_ = calculateSuffixPrefixLCS_long(A_, B_);
        auto end(std::chrono::steady_clock::now());
        return std::chrono::duration_cast<std::chrono::duration<double> > (end - start).count();
    }

    virtual bool readAnswerFromFile(const std::string &fname) {
        std::ifstream in_f;
        in_f.open(fname);
        std::cout << fname << std::endl;
        if (!in_f.good())
            return false;
        size_t sizeA, sizeB;
        getline(in_f, A_);
        getline(in_f, B_);
        sizeA = A_.size();
        sizeB = B_.size();
        ans_.assign(sizeA, std::vector<size_t> (sizeB));
        for (size_t i = 0; i < sizeA; ++i) {
            for (size_t j = 0; j < sizeB; ++j) {
                in_f >> ans_[i][j];
            }
        }
        in_f.close();
        return true;
    }

    virtual double CalculateAnswer()
    {
        auto start(std::chrono::steady_clock::now());
        test_ = calculateSuffixPrefixLCS(A_, B_);
        auto end(std::chrono::steady_clock::now());
        return std::chrono::duration_cast<std::chrono::duration<double> > (end - start).count();
    }

    void Compare()
    {
        size_t n = A_.size(),
               m = B_.size();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
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
        GenerateTest(AMaxSize, BMaxSize, t, 'a', 'i');
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
        std::cout << "\tstarting dp O(n^3) solution" << std::endl;
        double s1 = GenerateRightAnswer();
        std::cout << "\t\tcompleted for a " << s1 << " seconds" << std::endl;
        std::cout << "\tstarting super dp O(n^2) solution" << std::endl;
        double s2 = CalculateAnswer();
        std::cout << "\t\tcompleted for a " << s2 << " seconds" << std::endl;
        std::cout << std::endl;
        Compare();
    }
}

TEST_F(SuffixPrefixLCSTests, MaxTests)
{
    size_t maxTestSize = 2000;
    int tests = 2;
    randomRange = std::uniform_int_distribution<size_t>(maxTestSize / 2, maxTestSize - 1);
    for (int t = 0; t < tests; ++t) {
        GenerateTest(randomRange(engine), randomRange(engine), t, ' ', 127);
        //std::cout << A_ << std::endl;
        //std::cout << B_ << std::endl;
        std::cout << "generated test size " << A_.size() << "x" << B_.size() << std::endl;
        std::cout << "\tstarting dp O(n^3) solution" << std::endl;
        double s1 = GenerateRightAnswer();
        std::cout << "\t\tcompleted for a " << s1 << " seconds" << std::endl;
        std::cout << "\tstarting super dp O(n^2) solution" << std::endl;
        double s2 = CalculateAnswer();
        std::cout << "\t\tcompleted for a " << s2 << " seconds" << std::endl;
        std::cout << std::endl;
        Compare();
    }
}

TEST_F(SuffixPrefixLCSTests, TestFromFile)
{
    int startTest = 0;
    int lastTest = 20;
    for (int t = startTest; t <= lastTest; ++t) {
        if (!readAnswerFromFile(std::string("tests/") + std::to_string(t)))
            continue;
        std::cout << "read test; size " << A_.size() << "x" << B_.size() << std::endl;
        std::cout << "\tstarting super dp O(n^2) solution" << std::endl;
        double s2 = CalculateAnswer();
        std::cout << "\t\tcompleted for a " << s2 << " seconds" << std::endl;
        Compare();
    }
}


int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
