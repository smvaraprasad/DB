#ifndef BTREE_H
#define BTREE_H

typedef struct BTree BTree;

// Initialize B-tree
BTree *btree_init(void);

// Insert key-value pair
int btree_insert(BTree *tree, const char *key, const char *value);

// Search for value by key
char *btree_search(BTree *tree, const char *key);

// Free B-tree resources
void btree_free(BTree *tree);

#endif // BTREE_H