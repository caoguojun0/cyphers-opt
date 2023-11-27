#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>

void s_block(char* argv, unsigned char* s, int len_key)
{
    for ( int i = 0; i<256; i++)
    {
        s[i] = i;
    }

    int j = 0;

    for (int i = 0; i<256; i++)
    {
        j = (j + s[i] + argv[i%len_key]) % 256;

        unsigned int temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

void PRGA(unsigned char* s, char* cyphertext, char* plaintext, int counter)
{
    int i = 0;
    int j = 0;

    for ( int k = 0; k<counter; k++)
    {
        i = (i+1)%256;
        j = (j+s[i])%256;

        unsigned int temp = s[i];
        s[i] = s[j];
        s[j] = temp;

        int rnd = s[(s[i]+s[j])%256];
        cyphertext[k] = rnd ^ plaintext[k];
    }

}
