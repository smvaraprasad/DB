#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wal.h"

struct WAL {
    FILE *fp;
    char *path;
};

WAL *wal_init(const char *path) {
    WAL *wal = malloc(sizeof(WAL));
    if (!wal) return NULL;
    wal->path = strdup(path);
    wal->fp = fopen(path, "a+");
    return wal;
}

int wal_append(WAL *wal, const char *key, const char *value) {
    if (!wal || !wal->fp) return -1;
    fprintf(wal->fp, "%s\t%s\n", key, value);
    fflush(wal->fp);
    return 0;
}

WAL_Entry *wal_read_all(WAL *wal) {
    if (!wal || !wal->path) return NULL;
    FILE *fp = fopen(wal->path, "r");
    if (!fp) return NULL;
    WAL_Entry *entries = malloc(sizeof(WAL_Entry) * 1024); // up to 1024 entries
    size_t i = 0;
    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        char *key = strtok(line, "\t");
        char *value = strtok(NULL, "\n");
        if (key && value) {
            entries[i].key = strdup(key);
            entries[i].value = strdup(value);
            i++;
        }
    }
    entries[i].key = NULL; // NULL-terminate
    fclose(fp);
    return entries;
}

void wal_free_entries(WAL_Entry *entries) {
    if (!entries) return;
    for (size_t i = 0; entries[i].key; ++i) {
        free(entries[i].key);
        free(entries[i].value);
    }
    free(entries);
}

void wal_free(WAL *wal) {
    if (!wal) return;
    if (wal->fp) fclose(wal->fp);
    free(wal->path);
    free(wal);
}