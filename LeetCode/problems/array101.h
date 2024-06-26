#pragma once
#include "common.h"
#include <unordered_set>

class Solution {
public:
    Solution() { spdlog::info("Array Solution"); }

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

    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
    {
        vector<int> temp;
        for (int i = 0; i < m; i++) temp.push_back(nums1[i]);
        int i = 0, j = 0, k = 0;
        while (i < m && j < n && (temp[i] || temp[i] == 0) && (nums2[j] || nums2[j] == 0)) {
            if (temp[i] < nums2[j]) {
                nums1[k] = temp[i];
                k++;
                i++;
            } else {
                nums1[k] = nums2[j];
                k++;
                j++;
            }
        }
        while (i < m && (temp[i] || temp[i] == 0)) {
            nums1[k] = temp[i];
            k++;
            i++;
        }
        while (j < n && (nums2[j] || nums2[j] == 0)) {
            nums1[k] = nums2[j];
            k++;
            j++;
        }
    }

    int removeElement(vector<int>& nums, int val)
    {
        int j = nums.size() - 1;
        if (j < 0) return 0;
        for (int i = 0; (i < j) && (i < nums.size()); i++) {
            if (nums[i] == val) {
                int temp = nums[i];
                while (nums[j] == val && (j > i)) j--;
                nums[i] = nums[j];
                nums[j] = temp;
                j--;
            }
        }
        while ((j >= 0) && nums[j] == val) j--;
        return j + 1;
    }

    int removeDuplicates(vector<int>& nums)
    {
        int cur = 1, uni = 0;
        if (nums.size() == 2) {
            if (nums[cur] == nums[uni]) {
                return 1;
            } else {
                return 2;
            }
        }
        if (nums.size() < 2) return nums.size();
        while (cur < (nums.size() - 1)) {
            if ((cur != uni) && (nums[cur] == nums[uni])) cur++;
            if (cur == nums.size()) return ++uni;
            if (nums[cur] != nums[uni]) {
                uni++;
                nums[uni] = nums[cur];
                cur++;
            }
        }
        if ((cur == (nums.size() - 1)) && nums[cur] != nums[uni]) {
            uni++;
            nums[uni] = nums[cur];
        }
        return ++uni;
    }

    bool checkIfExist(vector<int>& arr)
    {
        std::unordered_set<int> mySet{};
        for (int i = 0; i < arr.size(); i++) {
            mySet.insert(arr[i]);
        }
        int zero_count = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == 0) {
                zero_count++;
                continue;
            };
            int element1 = arr[i] * 2;
            int element2 = -10000;
            if (arr[i] % 2 == 0) {
                element2 = arr[i] / 2;
            }
            if (auto iter = mySet.find(element1); iter != mySet.end()) return true;
            if (element2 != -10000) {
                if (auto iter = mySet.find(element2); iter != mySet.end()) return true;
            }
        }
        if (zero_count > 1) return true;
        return false;
    }

    bool validMountainArray(vector<int>& arr)
    {
        int i = 0;
        int j = arr.size() - 1;
        if (arr.size() < 3) {
            return false;
        }
        while ((i < arr.size() - 1) && (arr[i] < arr[i + 1])) {
            i++;
        }
        while ((j > 0) && (arr[j] < arr[j - 1])) {
            j--;
        }
        if ((j > 0) && (i == j) && (i < arr.size() - 1)) {
            return true;
        } else {
            return false;
        }
    }

    vector<int> replaceElements(vector<int>& arr)
    {
        for (int i = 0; i <= arr.size() - 1; i++) {
            int max = -1;
            for (int j = i + 1; j <= arr.size() - 1; j++) {
                if (arr[j] > max) {
                    max = arr[j];
                }
            }
            arr[i] = max;
        }
        return arr;
    }

    void moveZeroes(vector<int>& nums)
    {
        int write = 0;
        int read = 1;
        while (read < nums.size() && write < nums.size()) {
            while (write < nums.size() && nums[write] != 0) {
                write++;
            }
            while ((read < nums.size()) && (nums[read] == 0 || read <= write)) {
                read++;
            }
            if (write < read && write < nums.size() && read < nums.size()) {
                int tmp = nums[write];
                nums[write] = nums[read];
                nums[read] = tmp;
            }
        }
    }

    vector<int> sortArrayByParity(vector<int>& nums)
    {
        int odd = 0, even = 0;
        while (odd < nums.size() && even < nums.size()) {
            while (odd < nums.size() && nums[odd] % 2 == 0) odd++;
            while (even < nums.size() && nums[even] % 2 != 0) even++;
            if (odd < nums.size() && even < nums.size() && odd < even) {
                int temp = nums[odd];
                nums[odd] = nums[even];
                nums[even] = temp;
            } else {
                even++;
            }
        }
        return nums;
    }

    int heightChecker(vector<int>& heights)
    {
        vector<int> arr_sorted = heights;
        std::sort(arr_sorted.begin(), arr_sorted.end());
        int count = 0;
        for (int i = 0; i < heights.size(); i++) {
            if (arr_sorted[i] != heights[i]) {
                count++;
            }
        }
        return count;
    }

    vector<int> findDisappearedNumbers(vector<int>& nums)
    {
        auto sorted_array = nums;
        auto lack = vector<int>{};
        int index_pos = 0, sorted_pos = 0;
        std::cout << "index_pos"
                  << " "
                  << "sort_value" << std::endl;
        std::sort(sorted_array.begin(), sorted_array.end());
        while (index_pos < sorted_array.size()) {
            std::cout << index_pos + 1 << "     ";
            std::cout << sorted_array[sorted_pos] << std::endl;
            if ((index_pos + 1) == sorted_array[sorted_pos]) {
                sorted_pos++;
                index_pos++;
            } else if ((index_pos + 1) > sorted_array[sorted_pos]) {
                sorted_pos++;
            } else if ((index_pos + 1) < sorted_array[sorted_pos]) {
                while ((index_pos + 1) < sorted_array[sorted_pos]) {
                    lack.push_back(index_pos + 1);
                    index_pos++;
                }
            }
            if (sorted_pos == (sorted_array.size() - 1) && index_pos < sorted_array.size()) {
                while ((index_pos + 1) != sorted_array[sorted_pos] && index_pos < sorted_array.size()) {
                    lack.push_back(index_pos + 1);
                    index_pos++;
                }
                if ((index_pos + 1) == sorted_array[sorted_pos] && index_pos < sorted_array.size()) {
                    index_pos++;
                    while (index_pos < sorted_array.size()) {
                        lack.push_back(index_pos + 1);
                        index_pos++;
                    }
                }
            }
        }
        return lack;
    }
};

class SolutionBetter {
public:
    SolutionBetter() { spdlog::info("Array Solution Better"); }

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

    vector<int> sortedSquaresCenter(vector<int>& nums)
    {
        int left_idx = 0, right_idx = 0;
        int len = nums.size();
        int i = 0;
        vector<int> result;

        for (i = 0; i < len; i++) {
            if (nums[i] >= 0) {
                left_idx = i - 1;
                right_idx = i;
                break;
            }

            if (i == len - 1) {
                left_idx = len - 1;
                right_idx = len;
            }
        }

        while (left_idx >= 0 && right_idx < len) {
            if ((nums[left_idx] * -1) < nums[right_idx]) {
                result.push_back(nums[left_idx] * nums[left_idx]);
                left_idx--;
            } else {
                result.push_back(nums[right_idx] * nums[right_idx]);
                right_idx++;
            }
        }

        while (left_idx >= 0) {

            result.push_back(nums[left_idx] * nums[left_idx]);
            left_idx--;
        }

        while (right_idx < len) {

            result.push_back(nums[right_idx] * nums[right_idx]);
            right_idx++;
        }

        return result;
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

    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n)
    {
        int i = m - 1;
        int j = n - 1;
        int k = nums1.size() - 1;
        while (i >= 0 && j >= 0) {
            if (nums1[i] < nums2[j]) {
                nums1[k--] = nums2[j--];
            } else {
                nums1[k--] = nums1[i--];
            }
        }
        while (i >= 0) {
            nums1[k--] = nums1[i--];
        }
        while (j >= 0) {
            nums1[k--] = nums2[j--];
        }
    }

    int removeDuplicates(vector<int>& nums)
    {
        int j = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[i - 1]) {
                nums[j] = nums[i];
                j++;
            }
        }
        return j;
    }

    bool checkIfExist(vector<int>& arr)
    {
        std::unordered_set<int> mySet;
        for (int i = 0; i < arr.size(); i++) {
            if ((mySet.count(2 * arr[i]) > 0) || ((arr[i] % 2 == 0) && mySet.count(arr[i] / 2) > 0)) {
                return true;
            }
            mySet.insert(arr[i]);
        }
        return false;
    }

    vector<int> replaceElements(vector<int>& arr)
    {
        int max = -1;
        int tmp = arr[arr.size() - 1];
        arr[arr.size() - 1] = max;
        for (int i = arr.size() - 1; i > 0; i--) {
            if (tmp > max) {
                max = tmp;
            }
            tmp = arr[i - 1];
            arr[i - 1] = max;
        }
        return arr;
    }

    void moveZeroes(vector<int>& nums)
    {
        int i = 0, j = 0;
        int n = nums.size();
        while (i < n && j < n) {
            if (nums[i] == 0 && nums[j] != 0) {
                nums[i] = nums[j];
                nums[j] = 0;
            } else if (nums[i] != 0 && nums[j] == 0) {
                i++;
            } else
                j++;
        }
    }

    int thirdMax(vector<int>& nums)
    {
        long long firstMax = numeric_limits<long long>::min();
        long long secondMax = numeric_limits<long long>::min();
        long long thirdMax = numeric_limits<long long>::min();
        for (int& num : nums) {
            if (firstMax == num || secondMax == num || thirdMax == num) {
                continue;
            }
            if (firstMax <= num) {
                thirdMax = secondMax;
                secondMax = firstMax;
                firstMax = num;
            } else if (secondMax <= num) {
                thirdMax = secondMax;
                secondMax = num;
            } else if (thirdMax <= num) {
                thirdMax = num;
            }
        }
        if (thirdMax == numeric_limits<long long>::min()) {
            return firstMax;
        }
        return thirdMax;
    }

    vector<int> findDisappearedNumbers(vector<int>& nums)
    {
        vector<int> ans;
        for (auto c : nums) nums[abs(c) - 1] = -abs(nums[abs(c) - 1]); // mark c is present by negating nums[c-1]
        for (int i = 0; i < size(nums); i++)
            if (nums[i] > 0) ans.push_back(i + 1); // nums[i] > 0 means i+1 isnt present in nums
        return ans;
    }
};