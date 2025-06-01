/*
    https://leetcode.com/problems/combination-sum-ii/

    TC: O(2 ^ (Target / min element))
    SC: O(Target / min element)

    Idea is to sort the elements. We start with empty set and for
    the current element, add it to the subset and recurse further.

    For the current subset, the next element to be added should not
    be a duplicate of current element which was added.

*/
class Solution {
public:
    void findCmb(int curr, vector<int>& subset, int target,
        vector<int>& nums, vector<vector<int>>& result) {
        
        if (target == 0) {
            result.push_back(subset);
            return;
        }
        if (curr == nums.size() || target < 0)
            return;

        for(int i = curr; i < nums.size(); i++) {
            // skip the duplicate element's addition to the subset
            if (i == curr || nums[i] != nums[i-1]) {
                subset.push_back(nums[i]);
                findCmb(i+1, subset, target - nums[i], nums, result);
                subset.pop_back();
            }
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> subset;
        vector<vector<int>> result;
        sort(candidates.begin(), candidates.end());
        findCmb(0, subset, target, candidates, result);

        return result;
    }
};
