#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* newNode(int value) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int find_height(struct TreeNode* root) {
    if (root) {
        int l_height = find_height(root->left);
        int r_height = find_height(root->right);
        return (l_height >= r_height) ? (l_height + 1) : (r_height + 1);
    }
    return 0;
}

bool findlca(struct TreeNode* root, int tree_height, int cur_level, struct TreeNode** common_lca) {
    if (root) {
        bool l_val = findlca(root->left, tree_height, cur_level + 1, common_lca);
        bool r_val = findlca(root->right, tree_height, cur_level + 1, common_lca);

        if (cur_level == tree_height) {
            *common_lca = root;
            return true;
        }
        if (l_val && r_val) {
            *common_lca = root;
        }
        return (l_val || r_val);
    }
    return false;
}

struct TreeNode* subtreeWithAllDeepest(struct TreeNode* root) {
    int height = find_height(root);
    struct TreeNode* common_lca = NULL;
    findlca(root, height, 1, &common_lca);
    return common_lca;
}

void printTree(struct TreeNode* root) {
    if (root) {
        printf("%d ", root->val);
        printTree(root->left);
        printTree(root->right);
    }
}

int main() {

    struct TreeNode* root = newNode(3);
    root->left = newNode(5);
    root->right = newNode(1);
    root->left->left = newNode(6);
    root->left->right = newNode(2);
    root->right->left = newNode(0);
    root->right->right = newNode(8);
    root->left->right->left = newNode(7);
    root->left->right->right = newNode(4);

    struct TreeNode* lca = subtreeWithAllDeepest(root);
    printf("O menor ancestral comum dos nós mais profundos é: %d\n", lca->val);

    free(root->left->right->right);
    free(root->left->right->left);
    free(root->right->right);
    free(root->right->left);
    free(root->left->right);
    free(root->left->left);
    free(root->right);
    free(root->left);
    free(root);

    return 0;
}