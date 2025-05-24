/*
    https://leetcode.com/problems/valid-anagram/

    1. Hashing solution
    TC: O(n + m)
    SC: O(n + m)

    2. Sorting
    Sort both the strings and just compare if equal

    TC: O(nlogn + mlogm)
    SC: O(n + m)
*/
class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> freq;

        for(char ch: s)
            freq[ch]++;

        for(char ch: t) {
            if (freq.count(ch) == 0)
                return false;
            --freq[ch];

            if (freq[ch] == 0)
                freq.erase(ch);
        }
        
        return freq.size() == 0;
    }
};
