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

    void duplicateZeros(vector<int>& arr)
    {
        for (int i = 0; i < arr.size();) {
            if (arr[i] == 0) {
                int j = arr.size() - 1;
                while (j > i + 1) {
                    arr[j] = arr[j - 1];
                    j--;
                }
                if ((i + 1) < arr.size()) arr[i + 1] = 0;
                i = i + 2;
            } else {
                i++;
            }
        }
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

    void duplicateZeros(vector<int>& arr)
    {
        int count = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == 0) {
                count++;
            }
        }
        int i = arr.size() - 1;
        for (int j = count + arr.size() - 1; j >= 0 && i >= 0;) {
            if (j > arr.size() - 1) {
                if (arr[i] == 0) {
                    j--;
                    i--;
                    if (j > arr.size() - 1) {
                        j--;
                    } else {
                        arr[j] = 0;
                        j--;
                    }
                } else {
                    j--;
                    i--;
                }
            } else {
                spdlog::info("j: {} arr[j]: {}", j, arr[j]);
                // cout << "j" << j << " " << arr[j] << endl;
                if (arr[i] == 0) {
                    arr[j] = 0;
                    j--;
                    arr[j] = 0;
                    i--;
                    j--;
                } else {
                    arr[j] = arr[i];
                    j--;
                    i--;
                }
            }
        }
    }
};