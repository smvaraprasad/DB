#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cli.h"

#define MAX_INPUT 1024

static void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') str[len-1] = '\0';
}

void cli_run(Engine *engine) {
    char input[MAX_INPUT];
    printf("Welcome to storage_engine CLI. Type 'help' for commands.\n");
    while (1) {
        printf("engine> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        trim_newline(input);

        // Ignore empty input
        if (strlen(input) == 0) continue;

        // Exit
        if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) break;

        // Help
        if (strcmp(input, "help") == 0) {
            printf("Commands:\n");
            printf("  INSERT <key> <value>   - Insert key-value\n");
            printf("  SELECT <key>           - Get value by key\n");
            printf("  EXIT                   - Quit\n");
            continue;
        }

        // Parse INSERT
        if (strncasecmp(input, "INSERT ", 7) == 0) {
            char *rest = input + 7;
            char *key = strtok(rest, " ");
            char *value = strtok(NULL, "");
            if (key && value) {
                if (engine_put(engine, key, value) == 0)
                    printf("Inserted: %s -> %s\n", key, value);
                else
                    printf("Insert failed\n");
            } else {
                printf("Usage: INSERT <key> <value>\n");
            }
            continue;
        }

        // Parse SELECT
        if (strncasecmp(input, "SELECT ", 7) == 0) {
            char *key = input + 7;
            if (strlen(key) == 0) {
                printf("Usage: SELECT <key>\n");
                continue;
            }
            char *val = engine_get(engine, key);
            if (val)
                printf("%s\n", val);
            else
                printf("(not found)\n");
            continue;
        }

        printf("Unknown command. Type 'help' for list of commands.\n");
    }
    printf("Bye!\n");
}