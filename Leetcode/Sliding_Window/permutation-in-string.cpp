/*
    https://leetcode.com/problems/permutation-in-string/
    
    Since we are looking for the pmt of s1, we just need to check if can
    find a window the same size as that of s1 which has the same number of chars
    as that of s1. Since it is pmt we are looking for, that can be formed with just
    rearranging the chars in that window.
    TC: O(N), SC: O(1)
*/
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if(s1.size() > s2.size())
            return false;
        vector<int> s1_freq(26, 0), s2_freq(26, 0);
        
        // check if the frequency of s1 is there in s2 with a window size equal to s1
        int i = 0;
        for(; i < s1.size(); i++) {
            // compute the frequency of each char for the first window
            ++s1_freq[s1[i] - 'a'];
            ++s2_freq[s2[i] - 'a'];
        }
        
        if(s1_freq == s2_freq)
            return true;
        // search the remaining windows
        for(; i < s2.size(); i++) {
            // remove the first char of current window and add the current char
            --s2_freq[s2[i - s1.size()] - 'a'];
            ++s2_freq[s2[i] - 'a'];
            if(s1_freq == s2_freq)
                return true;
        }
        return false;
    }
};


////////////////////////////// Style 3
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s2.size(), k = s1.size();

        // if smaller string is greater than the bigger string, not possible
        if (s1.size() > s2.size())
            return false;
        // if the substring is empty, it is possible
        if (s1.empty())
            return true;

        unordered_map<char, int> freq;

        // find the substring's freq
        for(char& ch: s1)
            ++freq[ch];

        // process the 1st window
        int req = k;
        int i = 0;

        while(i < k) {
            // req chars is only affected as long as we are not seeing surplus
            if (--freq[s2[i]] >= 0)
                --req;
            ++i;
        }

        if (req == 0)
            return true;

        // process the remaining windows
        for(; i < n; i++) {
            // remove the oldest char of last window
            if (++freq[s2[i - k]] > 0)
                ++req;

            // add the last char of current window
            if (--freq[s2[i]] >= 0)
                --req;

            if (req == 0)
                return true;
        }

        return false;
    }
};

