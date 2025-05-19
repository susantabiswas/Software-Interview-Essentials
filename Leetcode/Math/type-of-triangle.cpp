/*
    https://leetcode.com/problems/type-of-triangle/

    TC: O(1)
    SC: O(1)
*/
class Solution {
public:
    string triangleType(vector<int>& nums) {
        long total = 0;
        for(auto num: nums)
            total += num;

        int longest = max(nums[0], max(nums[1], nums[2]));
        int shortest = min(nums[0], min(nums[1], nums[2]));
        int third_side = total - longest - shortest;

        if (longest >= shortest + third_side)
            return "none";

        if (longest == shortest)
            return "equilateral";
        else if (shortest == third_side || third_side == longest)
            return "isosceles";
        return "scalene";
    }
};
