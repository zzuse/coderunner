#include "array101.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Sqrt Sorted Array", "[array]")
{
    SolutionBetter solution;
    std::vector<int> input = {-7, -3, 2, 3, 11};
    auto result = solution.sortedSquares(input);
    REQUIRE(result == std::vector<int>({4, 9, 9, 49, 121}));
}

TEST_CASE("Duplicate Zeros", "[array]")
{
    SolutionBetter solution;
    std::vector<int> input1 = {1, 0, 2, 3, 0, 4, 5, 0};
    solution.duplicateZeros(input1);
    REQUIRE(input1 == std::vector<int>({1, 0, 0, 2, 3, 0, 0, 4}));

    cout << endl;
    std::vector<int> input2 = {8, 4, 5, 0, 0, 0, 0, 7};
    solution.duplicateZeros(input2);
    REQUIRE(input2 == std::vector<int>({8, 4, 5, 0, 0, 0, 0, 0}));
}