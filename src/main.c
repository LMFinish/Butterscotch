#include "data_win.h"

#include <stdio.h>

#include "utils.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path to data.win or game.unx>\n", argv[0]);
        return 1;
    }

    const char* filePath = argv[1];
    printf("Loading %s...\n", filePath);

    DataWin* dataWin = DataWin_parse(filePath);

    Gen8* gen8 = &dataWin->gen8;
    printf("Loaded \"%s\" (%d) successfully!\n", gen8->name, gen8->gameID);

    DataWin_free(dataWin);
    return 0;
}
