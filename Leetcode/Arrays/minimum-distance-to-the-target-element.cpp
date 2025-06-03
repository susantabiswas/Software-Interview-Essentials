/*
    https://leetcode.com/problems/minimum-distance-to-the-target-element/
*/
class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int dist = INT_MAX;
        for(int i = 0; i < nums.size(); i++) {
            if (nums[i] == target) {
                dist = min(dist, abs(i - start));
            }
        }

        return dist;
    }
};
