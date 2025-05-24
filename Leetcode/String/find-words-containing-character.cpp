/*
    https://leetcode.com/problems/find-words-containing-character/

    TC: O(nL), L = longest word length
    SC: O(1)
*/
class Solution {
public:
    vector<int> findWordsContaining(vector<string>& words, char x) {
        vector<int> result;
        int idx = 0;

        for(string& word: words) {
            for(char& ch: word)
                if (ch == x) {
                    result.emplace_back(idx);
                    break;
                }
            ++idx;
        }
        return result;
    }
};
