char* xor(char *text, char *key, int flag_text);

void s_block(char* argv, unsigned char* s, int len_key);
char* PRGA(unsigned char* s, char* cyphertext, char* plaintext, int counter);

char **generation_table(char* key);
char *vigener(char **table, char *key, char *text, int g_SIZE_TEXT);

int rsa(char *mes, char *output_file);