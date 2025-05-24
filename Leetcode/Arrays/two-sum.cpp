/*
    https://leetcode.com/problems/two-sum/

    TC: O(n)
    SC: O(n)
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;

        for(int i = 0; i < nums.size(); i++) {
            int& num = nums[i];
            int other = target - num;

            if (seen.count(other))
                return vector<int>{seen[other], i};
            seen[num] = i;
        }

        return {};
    }
};
