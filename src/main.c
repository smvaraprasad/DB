#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "cli.h"

int main(int argc, char *argv[]) {
    Engine *engine = engine_init("data/wal.log");
    if (!engine) {
        fprintf(stderr, "Failed to initialize engine\n");
        return 1;
    }

    cli_run(engine);

    engine_free(engine);
    return 0;
}