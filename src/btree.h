#ifndef BTREE_H
#define BTREE_H
 
/* Order-16 B-Tree key/value store.
 * Order M = 16  ->  max 15 keys / 16 children per node
 * Min degree t  = M/2 = 8  ->  min 7 keys per non-root node
 */
 
typedef struct BTree BTree;
 
BTree *btree_init(void);
int    btree_insert(BTree *tree, const char *key, const char *value);
char  *btree_search(BTree *tree, const char *key);
void   btree_free(BTree *tree);
 
#endif /* BTREE_H */