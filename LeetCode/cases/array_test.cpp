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

TEST_CASE("Merge Sorted Array", "[array]")
{
    SolutionBetter solution;
    SECTION("two array greater than 1")
    {
        std::vector<int> nums1 = {1, 2, 3, 0, 0, 0};
        std::vector<int> nums2 = {2, 5, 6};
        int m = 3, n = 3;
        REQUIRE(nums1.size() == m + n);
        REQUIRE(nums2.size() == n);
        solution.merge(nums1, m, nums2, n);
        REQUIRE(nums1 == std::vector<int>({1, 2, 2, 3, 5, 6}));
    }
    SECTION("first array equal 1")
    {
        std::vector<int> nums1 = {1};
        std::vector<int> nums2 = {};
        int m = 1, n = 0;
        REQUIRE(nums1.size() == m + n);
        REQUIRE(nums2.size() == n);
        solution.merge(nums1, m, nums2, n);
        REQUIRE(nums1 == std::vector<int>({1}));
    }
    SECTION("second array equal 1")
    {
        std::vector<int> nums1 = {0};
        std::vector<int> nums2 = {1};
        int m = 0, n = 1;
        REQUIRE(nums1.size() == m + n);
        REQUIRE(nums2.size() == n);
        solution.merge(nums1, m, nums2, n);
        REQUIRE(nums1 == std::vector<int>({1}));
    }
    SECTION("include negative numbers")
    {
        spdlog::info("include negative numbers");
        std::vector<int> nums1 = {-5, -1, 0, 1, 4, 5, 0, 0, 0};
        std::vector<int> nums2 = {-2, 2, 3};
        int m = 6, n = 3;
        REQUIRE(nums1.size() == m + n);
        REQUIRE(nums2.size() == n);
        solution.merge(nums1, m, nums2, n);
        REQUIRE(nums1 == std::vector<int>({-5, -2, -1, 0, 1, 2, 3, 4, 5}));
    }
}
