#include <string.h>
#include <stdlib.h>

char **generation_table(char* key)
{
    int size_key = strlen(key);
    int size_table = size_key * 26;

    char **table=(char**) malloc(size_key*sizeof(char*));
    for (int i = 0; i < size_key; i++)
    {
        table[i] = (char*) malloc(26*sizeof(char*));
    }

    for (int i = 0; i < size_key; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            table[i][j] = (((key[i] - 'a') + j) % 26) + 'a';

        }

    }
    return table;
}

char *vigener(char **table, char *key, char *text, int g_SIZE_TEXT)
{
    int size_key = strlen(key);
    char *cypher_text = (char*) malloc (sizeof(char)*g_SIZE_TEXT);
    for ( int i = 0; i < g_SIZE_TEXT; i++) {
        cypher_text[i] = text[i] >= 'a' && text[i] <= 'z' ? table[i % size_key][text[i] - 'a'] : text[i];
    }
    return cypher_text;
}