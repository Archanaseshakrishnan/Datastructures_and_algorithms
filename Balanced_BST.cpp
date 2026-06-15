#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    int height(TreeNode* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    int balanceFactor(TreeNode* node) {
        if (!node) return 0;
        return height(node->left) - height(node->right);
    }

    TreeNode* rotateRight(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        return x;
    }

    TreeNode* rotateLeft(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        return y;
    }

    TreeNode* height_balancer(TreeNode* node) {
        if (!node) return nullptr;

        node->left = height_balancer(node->left);
        node->right = height_balancer(node->right);

        int bf = balanceFactor(node);

        // Left-heavy
        if (bf > 1) {
            // Left-Right case
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }

            // Left-Left case
            return rotateRight(node);
        }

        // Right-heavy
        if (bf < -1) {
            // Right-Left case
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }

            // Right-Right case
            return rotateLeft(node);
        }

        return node;
    }

    void insertBST_helper(TreeNode** root, int val) {
        TreeNode* node = *root;
        TreeNode* parent = nullptr;

        while (node) {
            parent = node;
            if (val < node->val) {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        TreeNode* new_node = new TreeNode(val);

        if (!parent) {
            *root = new_node;
        } else if (val < parent->val) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
    }

public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        insertBST_helper(&root, val);
        root = height_balancer(root);
        return root;
    }
};

// Helper function to print tree in-order
void inorderTraversal(TreeNode* root) {
    if (!root) return;
    inorderTraversal(root->left);
    cout << root->val << " ";
    inorderTraversal(root->right);
}

// Helper function to print tree level-order (BFS)
void levelorderTraversal(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        cout << node->val << " ";
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}

// Helper function to get height of tree
int getHeight(TreeNode* node) {
    if (!node) return 0;
    return 1 + max(getHeight(node->left), getHeight(node->right));
}

// Test driver
int main() {
    cout << "=== Balanced BST Test Driver ===" << endl;

    Solution sol;
    TreeNode* root = nullptr;

    // Test case 1: Insert values and check if tree remains balanced
    cout << "\nTest 1: Insert values [5, 3, 7, 2, 4, 6, 8]" << endl;
    int values[] = {5, 3, 7, 2, 4, 6, 8};
    for (int val : values) {
        root = sol.insertIntoBST(root, val);
        cout << "Inserted " << val << endl;
    }

    cout << "In-order traversal: ";
    inorderTraversal(root);
    cout << endl;

    cout << "Level-order traversal: ";
    levelorderTraversal(root);
    cout << endl;

    cout << "Tree height: " << getHeight(root) << endl;

    // Test case 2: Insert values that could create imbalance
    cout << "\nTest 2: Insert sequential values [10, 11, 12, 13, 14]" << endl;
    TreeNode* root2 = nullptr;
    int values2[] = {10, 11, 12, 13, 14};
    for (int val : values2) {
        root2 = sol.insertIntoBST(root2, val);
        cout << "Inserted " << val << endl;
    }

    cout << "In-order traversal: ";
    inorderTraversal(root2);
    cout << endl;

    cout << "Level-order traversal: ";
    levelorderTraversal(root2);
    cout << endl;

    cout << "Tree height: " << getHeight(root2) << endl;

    // Test case 3: Single value
    cout << "\nTest 3: Insert single value [42]" << endl;
    TreeNode* root3 = nullptr;
    root3 = sol.insertIntoBST(root3, 42);
    cout << "In-order traversal: ";
    inorderTraversal(root3);
    cout << endl;
    cout << "Tree height: " << getHeight(root3) << endl;

    cout << "\n=== Tests Complete ===" << endl;
    return 0;
}
