#include <iostream>
#include <cstddef>
#include <string>
#include <fstream>
#include <random>
#include "suffix_prefix_lcs_long.h"

using std::size_t;


std::random_device engine;

void generateTest(std::string &A, std::string &B, size_t ASize, size_t BSize, char lowSym='a', char highSym='z')
{
    std::uniform_int_distribution<char> randomSymbol(lowSym, highSym);
    A.resize(ASize);
    B.resize(BSize);
    for (size_t i = 0; i < ASize; ++i) {
        A[i] = randomSymbol(engine);
    }
    for (size_t j = 0; j < BSize; ++j) {
        B[j] = randomSymbol(engine);
    }
}

void generate(const std::string &testPath, size_t firstTest, size_t testsAmount, size_t ASize, size_t BSize, char lSym=' ', char rSym='\127')
{
    std::uniform_int_distribution<int> randomRangeA(ASize / 2, ASize),
                                       randomRangeB(BSize / 2, BSize);
    for (int i = firstTest; i + firstTest < testsAmount; ++i) {
        std::ofstream out_f(testPath + std::to_string(i));
        std::string A, B;
        std::cout << "generate test #" << i << std::endl;
        generateTest(A, B, randomRangeA(engine), randomRangeB(engine), lSym, rSym);
        std::cout << "\t calculate answer" << std::endl;
        auto tmp = calculateSuffixPrefixLCS_long2(A, B);
        out_f << A << std::endl;
        out_f << B << std::endl;
        for (size_t j = 0; j < A.length(); ++j) {
            for (size_t k = 0; k < B.length(); ++k) {
                out_f << tmp[j][k] << " ";
            }
            out_f << std::endl;
        }
        out_f.close();
        std::cout << "\ttest successfully generated" << std::endl;
    }
}

int main(int argc, char ** argv)
{
    //[1]testPath [2]startTestNumver [3]testsAmount [4]AMaxsize [5]BMaxSize [6]lowSymbol [7]highSymbol
    char lSym = 'a';
    char rSym = 'z';
    if (argc > 6) {
        lSym = argv[6][0];
        rSym = argv[7][0];
    }
    generate(argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]), lSym, rSym);
    return 0;
}