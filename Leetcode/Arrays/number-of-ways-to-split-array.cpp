/*
    https://leetcode.com/problems/number-of-ways-to-split-array/

    TC: O(N)
    SC: O(1)

    The problem is basically to determine if at ith index, the sum of left side 
    elements >= sum of right side elements.
    So, we first find the total sum of all the elements, this will help us
    answer the problem statement at any index.

    We start the traversal from left and we also start tracking the cummulative sum
    this time. At ith index, we update the cummulative sum which gives the sum of left side
    elements and then just subtract the ith element from total, this gives us the sum of right
    side elements.

    if left_sum >= right_sum => ++splits
*/
class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
        // total sum of all the elements
        long total = accumulate(nums.begin(), nums.end(), 0l);
        // calc the cummulative sum from left to right
        long cumm_sum = 0;
        int splits = 0;

        for(int i = 0; i < nums.size() - 1; i++) {
            cumm_sum += nums[i];
            total = total - nums[i];
            if (cumm_sum >= total)
                ++splits;
        }
        return splits;
    }
};
