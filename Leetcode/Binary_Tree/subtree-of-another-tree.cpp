/*
    https://leetcode.com/problems/subtree-of-another-tree/

    SOLUTION 1
    We use BFS to look for the root mode of tree t. Once a node
    is found in s, we check if t is present as a subtree with that node as root.
    
    TC: O(NM), M: nodes in t, N: nodes in s

    SOLUTION 2: Hashing
    TC: O(N + M)
    SC: O(max(M, N))

    Postorder/ Preorder
    NOTE - One imp thing to take care is with the start of a node. The hash of a subtree might start from the 
    the substring of another tree's node, this can give false positive.
    eg: tree: [21]
    subtree: [1]

        hash: 1 might match with partial node string 21, so we need to ensure that the start of node is clear and cannot be a 
        substring of another node's string value.
    
        This is why if we add ',' before each value, we can ensure that a char is there to mark the start of a node value.
        With this, above problem is resolved, 
        tree hash: ,21,LL
        subtree hash: ,1,LL

        Note - We don't need to mark the recursion end of child call with a special char since we are marking the null nodes
        and they capture the tree structure.

    
    Inorder:
        One caution with inorder, since the left subtree hash is present before the curr + right, the null node of left subtree
        might along with the rest of matching subtree might give a false positive. Here we can use a special symbol to mark the end of recursion
        call, this way after the null node of left subtree we will get * symbols to capture the actual structure.
    
    Subtree
        9
        \
         1
          \
           2   => L, 9, L, 1, 2, L, L

    Main Tree

      9
    /  \
   0    1
    \    \
     8    2   => L, 0, L, 8, L, 9, L, 1, 2, L, L

    Here the main tree doesnt really have the subtree, but without capturing the end of recursion, the null child node of 8 will appear just before 9 and 
    the string search wll turn true.

    Basically since in inorder we rely on : left + curr + right
    If the rightmost subtree of left child has the same structure as that of left subtree of target tree, then the representations will match
    since in inorder we are putting the right subtree of last child in the left subtree. Eg L, 0, L, 8, | L, 9, L, 1, 2, L, L |, right subtree of 8 was L and that appeared
    just before 9 in the serialization and hence a false match.
    What we need is a way to clearly mark the start of end of subtree processing (you can even think of it like the direction in which we moved)
    When we add the marking of a subtree processing, then there is no ambiguity and the subtrees are clear.
    With directional / subtree marking
    Main: L, 0, L, 8, L, *, *, 9, L, 1, 2, L, L, *, *, *
    subtree: L, 9, L, 1, 2, L, L, *, *, *

    Now that we have captured the directional info, we can see that after 8, L, we also have captured *, *, which indicate end of recursion for those 2 subtrees and then coming to node 9 again.

    Why is this not required for preorder and postorder?

    Preorder or postorder already clearly marks the processing of a subtree and hence the directional info is already inherently present.
    Preorder: curr + left + right => curr will always tell you the subtree being processed
    Postorder: left + right + curr => again, the curr at the end indicates the subtree being processed.
    
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
    // TC: O(N)
    bool isIdentical(TreeNode* root1, TreeNode* root2) {
        if(!root1 && !root2)
            return true;
        if(!root1 || !root2)
            return false;
        if(root1->val != root2->val)
            return false;
        return isIdentical(root1->left, root2->left) && 
                isIdentical(root1->right, root2->right);
    }
    
    bool isSubtree(TreeNode* s, TreeNode* t) {
        // Find the root node of subtree t in s
        // using BFS
        queue<TreeNode*> q;
        q.emplace(s);
        
        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            // check if the tree t is a subtree
            if(curr->val == t->val && isIdentical(curr, t))
                return true;
            if(curr->left)
                q.emplace(curr->left);
            if(curr->right)
                q.emplace(curr->right);
        }
        return false;
    }
};

////////////////////////////////// SOLUTION 2 : HASHING
void postorder(TreeNode* root, string& tree_hash) {
        // There can be case where only one child is present, hence
        // we need to fill that null node position
        if(!root) {
            tree_hash += 'L';
            return;
        }
        
        // Use ',' to separate the nodes
        tree_hash += "," + to_string(root->val);
        
        postorder(root->left, tree_hash);
        postorder(root->right, tree_hash);
    }
    
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        // find the hash
        string orig;
        postorder(root, orig);
        
        string subtree;
        postorder(subRoot, subtree);
        
        return orig.find(subtree) != string::npos;
    }



/////////////// HASHING + Inorder
class Solution {
public:
    void hashTree(TreeNode* root, string& hash) {
        if(!hash.empty())
            hash += ',';
        
        if(!root) {
            hash += 'n';
            return;
        }
        
        hashTree(root->left, hash);
        
        hash += to_string(root->val);
        
        hashTree(root->right, hash);
        hash += '*';
    }
    
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        string tree_hash, sub_hash;
        hashTree(subRoot, sub_hash);
        hashTree(root, tree_hash);
        
        auto it = tree_hash.find(sub_hash);
        return it != string::npos;
    }
