#include "cyphers.h"
#include <string.h>
extern int g_SIZE_TEXT;
char* xor(char *text, char *key, int flag_text) {
    int key_len = strlen(key);

    for (int i = 0; i< (flag_text==1 ? strlen(text) : g_SIZE_TEXT); i++) {
        text[i] = text[i]^key[i%key_len];
    }

    return text;
}