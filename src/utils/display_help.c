#include <stdio.h>

void display_help() {
    FILE *file = fopen("src/utils/help.txt", "r");
    if (file == NULL) {
        perror("Error opening help.txt");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}