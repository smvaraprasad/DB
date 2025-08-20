#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "engine.h"

Engine *engine_init(const char *wal_path) {
    Engine *engine = malloc(sizeof(Engine));
    if (!engine) return NULL;
    engine->wal = wal_init(wal_path);
    engine->btree = btree_init();
    engine_replay_wal(engine);
    return engine;
}

int engine_put(Engine *engine, const char *key, const char *value) {
    if (wal_append(engine->wal, key, value) != 0) return -1;
    return btree_insert(engine->btree, key, value);
}

char *engine_get(Engine *engine, const char *key) {
    return btree_search(engine->btree, key);
}

int engine_replay_wal(Engine *engine) {
    // Replay WAL entries and insert into B-tree
    WAL_Entry *entries = wal_read_all(engine->wal);
    for (size_t i = 0; entries && entries[i].key; ++i) {
        btree_insert(engine->btree, entries[i].key, entries[i].value);
    }
    wal_free_entries(entries);
    return 0;
}

void engine_free(Engine *engine) {
    if (!engine) return;
    wal_free(engine->wal);
    btree_free(engine->btree);
    free(engine);
}