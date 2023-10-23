#pragma once
#include "common.h"

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums)
    {
        vector<int> results1, results2, results3;
        for (int num : nums) {
            if (num >= 0) { // increase
                num = num * num;
                results1.push_back(num);
            } else { // decrease
                num = num * num;
                results2.push_back(num);
            }
        }
        std::reverse(results2.begin(), results2.end());
        int i = 0, j = 0;
        int len1 = results1.size();
        int len2 = results2.size();
        while (i < len1 && j < len2) {
            if (results1[i] <= results2[j]) {
                results3.push_back(results1[i]);
                i++;
            } else {
                results3.push_back(results2[j]);
                j++;
            }
        }
        while (i >= len1 && j < len2) {
            results3.push_back(results2[j]);
            j++;
        }
        while (j >= len2 && i < len1) {
            results3.push_back(results1[i]);
            i++;
        }
        return results3;
    }
};

class SolutionBetter {
public:
    vector<int> sortedSquares(vector<int>& nums)
    {
        vector<int> results(nums.size(), 0);
        int k = nums.size() - 1;
        for (int i = 0, j = nums.size() - 1; (i <= j) && (k >= 0);) {
            if (abs(nums[i]) < abs(nums[j])) {
                results[k] = nums[j] * nums[j];
                j--;
                k--;
            } else {
                results[k] = nums[i] * nums[i];
                i++;
                k--;
            }
        }
        return results;
    }
};