#include <stdlib.h>
#include <string.h>
#include "btree.h"

/* Order M = 16 */
#define BTREE_ORDER   16
#define MIN_DEGREE    (BTREE_ORDER / 2)      /* t = 8  */
#define MAX_KEYS      (BTREE_ORDER - 1)      /* 15     */
#define MIN_KEYS      (MIN_DEGREE - 1)       /* 7      */

typedef struct BTreeNode {
    int   num_keys;
    char *keys[MAX_KEYS];
    char *values[MAX_KEYS];
    struct BTreeNode *children[BTREE_ORDER];
    int   leaf;   /* 1 = leaf, 0 = internal */
} BTreeNode;

struct BTree {
    BTreeNode *root;
};

/* ---------- node helpers ---------- */

static BTreeNode *create_node(int leaf) {
    BTreeNode *n = malloc(sizeof(BTreeNode));
    n->num_keys = 0;
    n->leaf = leaf;
    memset(n->children, 0, sizeof(n->children));
    return n;
}

BTree *btree_init(void) {
    BTree *tree = malloc(sizeof(BTree));
    tree->root = NULL;
    return tree;
}

/* ---------- search ---------- */

static char *search_node(BTreeNode *node, const char *key) {
    if (!node) return NULL;

    int i = 0;
    while (i < node->num_keys && strcmp(key, node->keys[i]) > 0)
        i++;

    if (i < node->num_keys && strcmp(key, node->keys[i]) == 0)
        return node->values[i];

    if (node->leaf)
        return NULL;

    return search_node(node->children[i], key);
}

char *btree_search(BTree *tree, const char *key) {
    if (!tree) return NULL;
    return search_node(tree->root, key);
}

/* ---------- insert ---------- */

/* Split full child x->children[i] (which has MAX_KEYS keys) in two,
 * pushing its median key/value up into parent x. */
static void split_child(BTreeNode *x, int i) {
    BTreeNode *y = x->children[i];
    BTreeNode *z = create_node(y->leaf);
    z->num_keys = MIN_KEYS;

    for (int j = 0; j < MIN_KEYS; j++) {
        z->keys[j]   = y->keys[j + MIN_DEGREE];
        z->values[j] = y->values[j + MIN_DEGREE];
    }

    if (!y->leaf) {
        for (int j = 0; j < MIN_DEGREE; j++)
            z->children[j] = y->children[j + MIN_DEGREE];
    }

    y->num_keys = MIN_KEYS;

    for (int j = x->num_keys; j >= i + 1; j--)
        x->children[j + 1] = x->children[j];
    x->children[i + 1] = z;

    for (int j = x->num_keys - 1; j >= i; j--) {
        x->keys[j + 1]   = x->keys[j];
        x->values[j + 1] = x->values[j];
    }
    x->keys[i]   = y->keys[MIN_DEGREE - 1];
    x->values[i] = y->values[MIN_DEGREE - 1];
    x->num_keys++;
}

/* Insert into a node known not to be full. Handles in-place update
 * of an existing key at any level (internal or leaf). */
static void insert_non_full(BTreeNode *x, const char *key, const char *value) {
    int pos = 0;
    while (pos < x->num_keys && strcmp(key, x->keys[pos]) > 0)
        pos++;

    if (pos < x->num_keys && strcmp(key, x->keys[pos]) == 0) {
        free(x->values[pos]);
        x->values[pos] = strdup(value);
        return;
    }

    if (x->leaf) {
        for (int j = x->num_keys - 1; j >= pos; j--) {
            x->keys[j + 1]   = x->keys[j];
            x->values[j + 1] = x->values[j];
        }
        x->keys[pos]   = strdup(key);
        x->values[pos] = strdup(value);
        x->num_keys++;
        return;
    }

    if (x->children[pos]->num_keys == MAX_KEYS) {
        split_child(x, pos);
        if (strcmp(key, x->keys[pos]) > 0) {
            pos++;
        } else if (strcmp(key, x->keys[pos]) == 0) {
            free(x->values[pos]);
            x->values[pos] = strdup(value);
            return;
        }
    }

    insert_non_full(x->children[pos], key, value);
}

int btree_insert(BTree *tree, const char *key, const char *value) {
    if (!tree) return -1;

    if (!tree->root) {
        tree->root = create_node(1);
    }

    BTreeNode *r = tree->root;

    if (r->num_keys == MAX_KEYS) {
        BTreeNode *s = create_node(0);
        s->children[0] = r;
        tree->root = s;
        split_child(s, 0);
        insert_non_full(s, key, value);
    } else {
        insert_non_full(r, key, value);
    }

    return 0;
}

/* ---------- free ---------- */

static void free_node(BTreeNode *node) {
    if (!node) return;

    for (int i = 0; i < node->num_keys; i++) {
        free(node->keys[i]);
        free(node->values[i]);
    }

    if (!node->leaf) {
        for (int i = 0; i <= node->num_keys; i++)
            free_node(node->children[i]);
    }

    free(node);
}

void btree_free(BTree *tree) {
    if (!tree) return;
    free_node(tree->root);
    free(tree);
}