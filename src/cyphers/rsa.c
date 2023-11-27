#include <stdio.h>
#include <gmp.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 4

int rsa(char *messege, char *output_file)
{
    mpz_t p, q, n, phi, e,gcd_e_phi, x, y,d;
    mpz_inits(p, q, n, phi, e,gcd_e_phi, x, y,d,NULL);

    gmp_randstate_t state;
    gmp_randinit_mt(state);

    unsigned long seed = time(NULL);
    gmp_randseed_ui(state, seed);

    mpz_urandomb(p,state,1024);
    mpz_nextprime(p,p);

    mpz_urandomb(q,state,1024);
    mpz_nextprime(q,q);

    mpz_urandomb(e,state,128);
    mpz_nextprime(e,e);

    gmp_printf("p-> %Zd\n ",p);
    gmp_printf("q-> %Zd\n ",q);

    mpz_mul(n,p,q);
    gmp_printf("n-> %Zd\n ",n);

    mpz_sub_ui(p,p,1);
    mpz_sub_ui(q,q,1);

    mpz_mul(phi,p,q);
    gmp_printf("phi-> %Zd\n ",phi);


    gmp_printf("e-> %Zd -> ",e);

    mpz_gcd(gcd_e_phi,e,phi);
    if( mpz_cmp_ui(gcd_e_phi,1)==0)
    {
        printf("is prime\n");
    }


    // extended_gcd(phi,e,gcd_e_phi,x,y);
    mpz_invert(d, e, phi);

    gmp_printf("d-> %Zd\n", d);

    // encrypt
    // mpz_init_set_ui(m, 111111);
    // gmp_printf("m -> %Zd\n", m);
    // mpz_init(c);

    // mpz_powm(c, m, e, n);
    // gmp_printf("c -> %Zd\n", c);
    //decrypt
    // mpz_powm(c, c, d, n);

    // gmp_printf("c -> %Zd\n", c);

//    char mes[]=messege;
    int mes_len = strlen(messege);

    int add_to_full_block = BLOCK_SIZE - (mes_len%BLOCK_SIZE);

    char *new_full_mes = calloc (mes_len + add_to_full_block, sizeof(char));
    memcpy(new_full_mes, messege,mes_len);

    for (int i = mes_len; i < mes_len + add_to_full_block; i++)
    {
        new_full_mes[i] = ' ';
    }

    int block_counter = (mes_len + add_to_full_block) / BLOCK_SIZE;

    mpz_t encrypt_blocks[block_counter];

    for (size_t i = 0; i < block_counter; i++)
    {
        mpz_t m,c;
        mpz_inits(m,c,NULL);

        char block[BLOCK_SIZE + 1];
        memcpy(block, new_full_mes + i * BLOCK_SIZE, BLOCK_SIZE);
        block[BLOCK_SIZE] = '\0';

        mpz_import(m, BLOCK_SIZE, 1, sizeof(char), 0, 0, block);
        mpz_powm(c, m, e, n);

        gmp_printf(" crypted block[%zu] -> %Zd\n", i, c);

        mpz_init(encrypt_blocks[i]);
        mpz_set(encrypt_blocks[i], c);

        mpz_clears(m, c, NULL);
    }

    for (size_t i = 0; i < block_counter; i++)
    {
        mpz_t m, c;
        mpz_inits(m, c, NULL);

        char decrypted_block[BLOCK_SIZE + 1];
        decrypted_block[BLOCK_SIZE] = '\0';

        mpz_set(c, encrypt_blocks[i]);

        mpz_powm(m, c, d, n);
        mpz_export(decrypted_block, NULL, 1, sizeof(char), 0, 0, m);

        printf("decrypted block [%zu] -> %s\n", i, decrypted_block);

        mpz_clears(m, c, NULL);
    }


    for (size_t i = 0; i < block_counter; i++)
    {
        mpz_clear(encrypt_blocks[i]);
    }

    mpz_clears(p, q, n, phi, e,gcd_e_phi, x, y,d,NULL);

    gmp_randclear(state);
    free(new_full_mes);
    return 0;
}