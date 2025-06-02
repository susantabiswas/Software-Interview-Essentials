/*
    https://leetcode.com/problems/count-subarrays-with-median-k/

    TC: O(N)
    SC: O(N), max sum cannot exceed total number of elements.

    For k to be a median in a subarray, the following cases are required:
    1. Odd len subarray: Count of elements less than k and count of elments greater than
        k should be equal.
    2. Even len subarray:  
        Count(Smaller) < Count(Greater) + 1
        Since the smaller element's count is 1 less than greater's, we can place the median K there
        since for even len, the median is the last element of smaller side.

    So essentially we need to track the counts of smaller and greater elements wrt K. To make it 
    easier, assign +1 for greater and -1 for smaller.

    Once we find the position of median element in the array, we compute the delta of counts on right side.
    Then iterate from left of median and for each delta count, check if there is a counterpart balance count
    on the right to satisfy the conditions mentioned above.

    For odd length, total balance = 0 (equal smaller and greater)
    For even length, total balance = 1 (1 extra greater element)

    ans for each delta count would be finding if there is a substring of even and odd length with above 
    balance constraint.
*/
class Solution {
public:
    int countSubarrays(vector<int>& nums, int k) {
        // Find the position of median element
        int median_pos = -1;
        for(int i = 0; i < nums.size(); i++)
            if (nums[i] == k) {
                median_pos = i;
                break;
            }

        // <balance, count>: How many times a balance value was found in the array
        // +1 for > k, -1 for < k, 0 for k
        unordered_map<int, int> balance_seen;
        // NOTE: median element can always have a subarray of size 1 => [k],
        // but we dont need to update it here since it will be updated on the right
        // side traversal as the traversal starts from the median position itself.
        // Not Required: balance_seen[0] = 1;

        // Tracks the count of smaller and larger elements in a contiguous subarray
        int balance = 0;
        int ans = 0;

        // We need to compute the balance for any one of the sides
        // Here we will compute the balance of smaller and larger elements on the right
        for(int i = median_pos; i < nums.size(); i++) {
            // For a smaller el than k, assign -1
            // For a larger el than k, assign +1
            // balance represents the delta between the two
            balance += (nums[i] == k) ? 0 : (nums[i] < k ? -1 : 1);
            ++balance_seen[balance];
        }

        // Now we can traverse the left side and for each position,
        // check if there are elements on its right to create the following:
        // 1. Even length subarray with median K: 
        // Cnt(smaller) < Cnt(Greater) => Smaller1...SmallerN-1..median....Greater1..GreaterN
        // Since for even len, median is the last element of smaller side, total smaller 
        // elements should be 1 less than count of greater element and median will fit in as the last
        // element of smaller side. => Balance of +1 is required
        //
        // 2. Odd length subarray with median k:
        // Cnt(smaller) = Cnt(Greater) => SmallerN...median....GreaterN
        // Ensure that balance 0 is required
        balance = 0;
        for(int i = median_pos; i >= 0; i--) {
            balance += (nums[i] == k) ? 0 : (nums[i] < k ? -1 : 1);
            // Odd length subarray
            ans += balance_seen[-balance]; 
            // Even length subarray
            ans += balance_seen[-balance + 1];
            // NOTE: We dont update the hash table here since we strictly want to get the
            // balancing done by the elements on the right of median element
        }

        return ans;
    }
};
