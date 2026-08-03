#include <stdlib.h>
#include <string.h>
#include "btree.h"

// Simple binary tree for demonstration
typedef struct BTreeNode {
    char *key;
    char *value;
    struct BTreeNode *left, *right;
} BTreeNode;

struct BTree {
    BTreeNode *root;
};

BTree *btree_init(void) {
    BTree *tree = malloc(sizeof(BTree));
    tree->root = NULL;
    return tree;
}

static BTreeNode *insert_node(BTreeNode *node, const char *key, const char *value) {
    if (!node) {
        node = malloc(sizeof(BTreeNode));
        node->key = strdup(key);
        node->value = strdup(value);
        node->left = node->right = NULL;
        return node;
    }
    int cmp = strcmp(key, node->key);
    if (cmp < 0)
        node->left = insert_node(node->left, key, value);
    else if (cmp > 0)
        node->right = insert_node(node->right, key, value);
    else {
        free(node->value);
        node->value = strdup(value);
    }
    return node;
}

int btree_insert(BTree *tree, const char *key, const char *value) {
    if (!tree) return -1;
    tree->root = insert_node(tree->root, key, value);
    return 0;
}

static char *search_node(BTreeNode *node, const char *key) {
    if (!node) return NULL;
    int cmp = strcmp(key, node->key);
    if (cmp == 0)
        return node->value;
    else if (cmp < 0)
        return search_node(node->left, key);
    else
        return search_node(node->right, key);
}

char *btree_search(BTree *tree, const char *key) {
    if (!tree) return NULL;
    return search_node(tree->root, key);
}

static void free_node(BTreeNode *node) {
    if (!node) return;
    free(node->key);
    free(node->value);
    free_node(node->left);
    free_node(node->right);
    free(node);
}

void btree_free(BTree *tree) {
    if (!tree) return;
    free_node(tree->root);
    free(tree);
}