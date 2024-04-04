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

TEST_CASE("Remove Element", "[array]")
{
    Solution solution;
    SECTION("Remove from start")
    {
        std::vector<int> nums = {3, 2, 2, 3};      // Input array
        int val = 3;                               // Value to remove
        std::vector<int> expectedNums = {2, 2};    // The expected answer with correct length.
                                                   // It is sorted with no values equaling val.
        int k = solution.removeElement(nums, val); // Calls your implementation
        CHECK(k == expectedNums.size());
        std::sort(nums.begin(), nums.begin() + k); // Sort the first k elements of nums
        for (int i = 0; i < k; i++) {
            CHECK(nums[i] == expectedNums[i]);
        }
    }
    SECTION("Remove from end 1")
    {
        std::vector<int> nums = {4, 5};            // Input array
        int val = 5;                               // Value to remove
        std::vector<int> expectedNums = {4};       // The expected answer with correct length.
                                                   // It is sorted with no values equaling val.
        int k = solution.removeElement(nums, val); // Calls your implementation
        CHECK(k == expectedNums.size());
        std::sort(nums.begin(), nums.begin() + k); // Sort the first k elements of nums
        for (int i = 0; i < k; i++) {
            CHECK(nums[i] == expectedNums[i]);
        }
    }
    SECTION("Remove from end 2")
    {
        std::vector<int> nums = {2, 3, 3};         // Input array
        int val = 3;                               // Value to remove
        std::vector<int> expectedNums = {2};       // The expected answer with correct length.
                                                   // It is sorted with no values equaling val.
        int k = solution.removeElement(nums, val); // Calls your implementation
        CHECK(k == expectedNums.size());
        std::sort(nums.begin(), nums.begin() + k); // Sort the first k elements of nums
        for (int i = 0; i < k; i++) {
            CHECK(nums[i] == expectedNums[i]);
        }
    }
    SECTION("Remove All 1")
    {
        std::vector<int> nums = {3};               // Input array
        int val = 3;                               // Value to remove
        std::vector<int> expectedNums = {};        // The expected answer with correct length.
                                                   // It is sorted with no values equaling val.
        int k = solution.removeElement(nums, val); // Calls your implementation
        CHECK(k == expectedNums.size());
        std::sort(nums.begin(), nums.begin() + k); // Sort the first k elements of nums
        for (int i = 0; i < k; i++) {
            CHECK(nums[i] == expectedNums[i]);
        }
    }
    SECTION("Remove All 2")
    {
        std::vector<int> nums = {3, 3};            // Input array
        int val = 3;                               // Value to remove
        std::vector<int> expectedNums = {};        // The expected answer with correct length.
                                                   // It is sorted with no values equaling val.
        int k = solution.removeElement(nums, val); // Calls your implementation
        CHECK(k == expectedNums.size());
        std::sort(nums.begin(), nums.begin() + k); // Sort the first k elements of nums
        for (int i = 0; i < k; i++) {
            CHECK(nums[i] == expectedNums[i]);
        }
    }
    SECTION("None ")
    {
        std::vector<int> nums = {};                // Input array
        int val = 3;                               // Value to remove
        std::vector<int> expectedNums = {};        // The expected answer with correct length.
                                                   // It is sorted with no values equaling val.
        int k = solution.removeElement(nums, val); // Calls your implementation
        CHECK(k == expectedNums.size());
        std::sort(nums.begin(), nums.begin() + k); // Sort the first k elements of nums
        for (int i = 0; i < k; i++) {
            CHECK(nums[i] == expectedNums[i]);
        }
    }
}

TEST_CASE("Remove Duplicates from Sorted Array", "[array]")
{
    SolutionBetter solution;
    SECTION("1 ")
    {
        std::vector<int> nums = {1};             // Input array
        std::vector<int> expectedNums = {1};     // The expected answer with correct length.
                                                 // It is sorted with no values equaling val.
        int k = solution.removeDuplicates(nums); // Calls your implementation
        CHECK(k == expectedNums.size());
        for (int i = 0; i < k; i++) {
            CHECK(nums[i] == expectedNums[i]);
        }
    }
    SECTION("2 ")
    {
        std::vector<int> nums = {1, 1, 2};       // Input array
        std::vector<int> expectedNums = {1, 2};  // The expected answer with correct length.
                                                 // It is sorted with no values equaling val.
        int k = solution.removeDuplicates(nums); // Calls your implementation
        CHECK(k == expectedNums.size());
        for (int i = 0; i < k; i++) {
            CHECK(nums[i] == expectedNums[i]);
        }
    }
    SECTION("5 ")
    {
        std::vector<int> nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4}; // Input array
        std::vector<int> expectedNums = {0, 1, 2, 3, 4};        // The expected answer with correct length.
                                                                // It is sorted with no values equaling val.
        int k = solution.removeDuplicates(nums);                // Calls your implementation
        CHECK(k == expectedNums.size());
        for (int i = 0; i < k; i++) {
            CHECK(nums[i] == expectedNums[i]);
        }
    }
}

TEST_CASE("Check If N and Its Double Exist", "[array]")
{
    SolutionBetter solution;
    SECTION("10 2 5 3 ")
    {
        std::vector<int> nums = {10, 2, 5, 3}; // Input array
        bool k = solution.checkIfExist(nums);  // Calls your implementation
        CHECK(k == true);
    }
    SECTION("3 1 7 11 ")
    {
        std::vector<int> nums = {3, 1, 7, 11}; // Input array
        bool k = solution.checkIfExist(nums);  // Calls your implementation
        CHECK(k == false);
    }
    SECTION("0 0 0 0 ")
    {
        std::vector<int> nums = {0, 0, 0, 0}; // Input array
        bool k = solution.checkIfExist(nums); // Calls your implementation
        CHECK(k == true);
    }
    SECTION("1 12 ")
    {
        std::vector<int> nums = {1, 12};      // Input array
        bool k = solution.checkIfExist(nums); // Calls your implementation
        CHECK(k == false);
    }
}

TEST_CASE("Valid Mountain Array", "[array]")
{
    Solution solution;
    SECTION("0,3,2,1")
    {
        std::vector<int> nums = {0, 3, 2, 1};       // Input array
        bool k = solution.validMountainArray(nums); // Calls your implementation
        CHECK(k == true);
    }
    SECTION("2,1")
    {
        std::vector<int> nums = {2, 1};             // Input array
        bool k = solution.validMountainArray(nums); // Calls your implementation
        CHECK(k == false);
    }
    SECTION("3,5,5")
    {
        std::vector<int> nums = {3, 5, 5};          // Input array
        bool k = solution.validMountainArray(nums); // Calls your implementation
        CHECK(k == false);
    }
    SECTION("2,0,2")
    {
        std::vector<int> nums = {2, 0, 2};          // Input array
        bool k = solution.validMountainArray(nums); // Calls your implementation
        CHECK(k == false);
    }
    SECTION("0,1,2,3,4,5,6,7,8,9")
    {
        std::vector<int> nums = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // Input array
        bool k = solution.validMountainArray(nums);             // Calls your implementation
        CHECK(k == false);
    }
    SECTION("0,1,2,1,2")
    {
        std::vector<int> nums = {0, 1, 2, 1, 2};    // Input array
        bool k = solution.validMountainArray(nums); // Calls your implementation
        CHECK(k == false);
    }
}

TEST_CASE("Replace Elements with Greatest Element on Right Side", "[array]")
{
    SolutionBetter solution;
    SECTION("17,18,5,4,6,1")
    {
        std::vector<int> nums = {17, 18, 5, 4, 6, 1};
        std::vector<int> expectedNums = {18, 6, 6, 6, 1, -1};
        auto k = solution.replaceElements(nums);
        CHECK(k == expectedNums);
    }
    SECTION("400")
    {
        std::vector<int> nums = {400};
        std::vector<int> expectedNums = {-1};
        auto k = solution.replaceElements(nums);
        CHECK(k == expectedNums);
    }
}

TEST_CASE("Move Zeroes", "[array]")
{
    SolutionBetter solution;
    SECTION("0,1,0,3,12")
    {
        std::vector<int> nums = {0, 1, 0, 3, 12};
        std::vector<int> expectedNums = {1, 3, 12, 0, 0};
        solution.moveZeroes(nums);
        CHECK(nums == expectedNums);
    }
    SECTION("0")
    {
        std::vector<int> nums = {0};
        std::vector<int> expectedNums = {0};
        solution.moveZeroes(nums);
        CHECK(nums == expectedNums);
    }
    SECTION("0,1")
    {
        std::vector<int> nums = {0, 1};
        std::vector<int> expectedNums = {1, 0};
        solution.moveZeroes(nums);
        CHECK(nums == expectedNums);
    }
    SECTION("0,0")
    {
        std::vector<int> nums = {0, 0};
        std::vector<int> expectedNums = {0, 0};
        solution.moveZeroes(nums);
        CHECK(nums == expectedNums);
    }
}

TEST_CASE("Sort Array By Parity", "[array]")
{
    Solution solution;
    SECTION("3,1,2,4")
    {
        std::vector<int> nums = {3, 1, 2, 4};
        std::vector<int> expectedNums = {2, 4, 3, 1};
        auto k = solution.sortArrayByParity(nums);
        CHECK(k == expectedNums);
    }
    SECTION("0")
    {
        std::vector<int> nums = {0};
        std::vector<int> expectedNums = {0};
        auto k = solution.sortArrayByParity(nums);
        CHECK(k == expectedNums);
    }
    SECTION("0,1")
    {
        std::vector<int> nums = {0, 1};
        std::vector<int> expectedNums = {0, 1};
        auto k = solution.sortArrayByParity(nums);
        CHECK(k == expectedNums);
    }
}

TEST_CASE("Height Checker", "[array]")
{
    Solution solution;
    SECTION("1,1,4,2,1,3")
    {
        std::vector<int> nums = {1, 1, 4, 2, 1, 3};
        // std::vector<int> expectedNums = {1, 1, 1, 2, 3, 4};
        auto k = solution.heightChecker(nums);
        CHECK(k == 3);
    }
    SECTION("5,1,2,3,4")
    {
        std::vector<int> nums = {5, 1, 2, 3, 4};
        // std::vector<int> expectedNums = {1,2,3,4,5};
        auto k = solution.heightChecker(nums);
        CHECK(k == 5);
    }
    SECTION("1,2,3,4,5")
    {
        std::vector<int> nums = {1, 2, 3, 4, 5};
        // std::vector<int> expectedNums = {1,2,3,4,5};
        auto k = solution.heightChecker(nums);
        CHECK(k == 0);
    }
}

TEST_CASE("The Third Distinct Maximum Number", "[array]")
{
    SolutionBetter solution;
    SECTION("3,2,1")
    {
        std::vector<int> nums = {3, 2, 1};
        auto k = solution.thirdMax(nums);
        CHECK(k == 1);
    }
    SECTION("1,2")
    {
        std::vector<int> nums = {1, 2};
        auto k = solution.thirdMax(nums);
        CHECK(k == 2);
    }
    SECTION("2,2,3,1")
    {
        std::vector<int> nums = {2, 2, 3, 1};
        auto k = solution.thirdMax(nums);
        CHECK(k == 1);
    }
}