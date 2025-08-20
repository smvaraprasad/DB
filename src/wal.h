#ifndef WAL_H
#define WAL_H

typedef struct {
    char *key;
    char *value;
} WAL_Entry;

typedef struct WAL WAL;

// Initialize WAL
WAL *wal_init(const char *path);

// Append entry to WAL
int wal_append(WAL *wal, const char *key, const char *value);

// Read all entries from WAL (returns NULL-terminated array)
WAL_Entry *wal_read_all(WAL *wal);

// Free WAL entries array
void wal_free_entries(WAL_Entry *entries);

// Free WAL resources
void wal_free(WAL *wal);

#endif // WAL_H