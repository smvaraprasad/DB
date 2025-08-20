#ifndef ENGINE_H
#define ENGINE_H

#include "wal.h"
#include "btree.h"

typedef struct {
    WAL *wal;
    BTree *btree;
} Engine;

// Initialize the engine (WAL + B-tree)
Engine *engine_init(const char *wal_path);

// Insert a key-value pair
int engine_put(Engine *engine, const char *key, const char *value);

// Get a value by key
char *engine_get(Engine *engine, const char *key);

// Replay WAL on startup
int engine_replay_wal(Engine *engine);

// Free engine resources
void engine_free(Engine *engine);

#endif // ENGINE_H