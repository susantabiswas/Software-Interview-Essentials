/*
    https://leetcode.com/problems/binary-tree-right-side-view/

    SOLUTION 1
    Do normal BFS so that we can be aware of the level. In each level add the last
    node to the traversal result.
    TC: O(N)

    SOLUTION 2
    Recursive sol
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        
        queue<TreeNode*> q;
        // Add non-null root
        if(root)
            q.emplace(root);
        int n_level = q.size();
        
        while(!q.empty()) {
            TreeNode *curr = q.front();
            q.pop();
            --n_level;
            
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
            
            // end of level
            if(n_level == 0) {
                // add the last node of current level
                result.emplace_back(curr->val);
                n_level = q.size();
            }
        }
        
        return result;
    }
};

////////////////////////// SOLUTION 2.A
class Solution {
public:
    void preorder(TreeNode* root, int curr_depth, int& max_depth, vector<int>& view) {
        if(!root)
            return;
        
        if(curr_depth > max_depth) {
            view.emplace_back(root->val);
            max_depth = curr_depth;
        }
        
        preorder(root->right, curr_depth + 1, max_depth, view);
        preorder(root->left, curr_depth + 1, max_depth, view);
    }
    
    vector<int> rightSideView(TreeNode* root) {
        vector<int> view;
        int max_depth = 0;
        
        preorder(root, 1, max_depth, view);
        return view;
    }
};

////////////////////////// SOLUTION 2.B
class Solution {
public:
    void dfs(TreeNode* root, int& max_level, int level, vector<int>& right) {
        if (!root)
            return;

        if (max_level < level) {
            right.push_back(root->val);
            max_level = level;
        }

        dfs(root->right, max_level, level+1, right);
        dfs(root->left, max_level, level+1, right);
    }

    vector<int> rightSideView(TreeNode* root) {
        int max_level = 0;
        vector<int> right;
        dfs(root, max_level, 1, right);

        return right;
    }
};
