/*
    https://leetcode.com/problems/string-compression/

    TC: O(n)
    SC: O(1)

    For each char, iterate till all its duplicates are traversed. We also use a `write_end`
    pointer to track where the data should be written. Once the freq is found, start writing the
    frequency number there if the num digits > 1. Repeat for all the chars.
*/
class Solution {
public:
    int compress(vector<char>& chars) {
        // Points to the position where data will be written
        int write_end = 0;

        for(int start = 0; start < chars.size(); ) {
            char ch = chars[start];
            int freq = 1;
            
            // check the frequency of current char
            int end = start + 1;
            while(end < chars.size() && chars[end] == chars[start])
                ++end, ++freq;

            chars[write_end++] = ch;
            
            // freq should only be put if freq > 1
            if (freq > 1) {
                int digits = 0;
                int write_start = write_end;
                
                // put the frequency from the last to first digit
                while(freq) {
                    chars[write_end++] = (freq % 10) + '0';
                    freq /= 10;
                    ++digits;
                }
                // reverse the number
                reverse(chars.begin() + write_start, chars.begin() + write_end);
            }

            start = end;
        }
        return write_end;
    }
};
