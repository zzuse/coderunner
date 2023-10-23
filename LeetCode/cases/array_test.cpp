#include "sqrt_sorted_array.h"
#include <catch2/catch_all.hpp>

TEST_CASE("Sqrt Sorted Array", "[sqrtsort]")
{
    SolutionBetter solution;
    std::vector<int> input = {-7, -3, 2, 3, 11};
    auto result = solution.sortedSquares(input);
    REQUIRE(result == std::vector<int>({4, 9, 9, 49, 121}));
}
