/*
    https://leetcode.com/problems/contains-duplicate/

    TC: O(nlogn + n) ~ O(n)
    SC: O(n) // Sorting
*/

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int start = 0, curr = 0;
        while(start < nums.size()) {
            while(curr < nums.size() && nums[start] == nums[curr]) {
                ++curr;
                // Early exit: there is a duplicate if the diff between start and curr index is > 1
                // we dont need to even traverse the currentelement's duplicates
                if(curr - start > 1)
                    return true;
            }
            
            start = curr;
        }

        return false;
    }
};

//// Solution 2: Seen set
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        
        for(auto num: nums) {
            if(seen.count(num))
                return true;
            seen.emplace(num);
        }
        return false;
    }
};
