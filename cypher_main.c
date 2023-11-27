#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <gmp.h>

#include "src/cyphers/cyphers.h"
#include "src/utils/utils.h"
#define CYPHER_COUNTER 4
int g_SIZE_TEXT = 0;

typedef struct Cypher
{
    int id;
    char* name_cypher;

}Cypher;

int main(int argc, char *argv[])
{
    unsigned char s[256];
    char* text;
    char* key;
    char* name_output_file;
    char* name_input_file;
   

    const char* short_options = "hC:t:k:o:f:";

	const struct option long_options[] = {
		{ "help", no_argument, NULL, 'h' },
		{ "Cypher", required_argument, NULL, 'C' },
        { "text", required_argument, NULL, 't' },
        { "key", required_argument, NULL, 'k' },
        { "output", required_argument, NULL, 'o' },
        { "file", required_argument, NULL, 'f' },
		{ NULL, 0, NULL, 0 }
	};

    int flag_C = 0;
    int flag_text = 0;
    int flag_k = 0;
    int flag_o = 0;
    int flag_f = 0;

    int rez;
	int option_index;

    Cypher cyphers[] = {{1,"xor"},{2,"rc4"},{3,"vig"},{4,"rsa"}};

	while ((rez=getopt_long(argc,argv,short_options,
		long_options,&option_index))!=-1)
        {
            switch(rez)
            {
                case 'h':
                    display_help();
                    break;
                case 'C':
                    
                    if (optarg != NULL)
                    {
                        for (int i = 0; i < CYPHER_COUNTER; i++)
                        {
                            if (strcmp(cyphers[i].name_cypher,optarg) == 0)
                            {
                                flag_C = cyphers[i].id;   
                                break;
                            }
                        }
                    }
                    
                    if (flag_C == 0)
                    {
                        printf("This is demo help. Try -h or --help.\n");
                        printf("option_index = %d (\"%s\",%d,%c)\n",
                        option_index,
                        long_options[option_index].name,
                        long_options[option_index].has_arg,
                        long_options[option_index].val
                    );
                    }
                    break;
                case 't':
                    if (optarg != NULL)
                    {
                        text = optarg;
                        flag_text = 1;
                    }
                    break;
                case 'k':
                    if (optarg != NULL)
                    {
                        key = optarg;
                        flag_k = 1;
                    }
                    break; 
                case 'o':
                    if (optarg != NULL)
                    {
                        flag_o = 1;
                        name_output_file = optarg;
                    }
                    break;
                case 'f':
                    if (optarg != NULL)
                    {
                        flag_f = 1;
                        name_input_file = optarg;
                        FILE* input = fopen(name_input_file, "r");
                        int k = 0;
                        text = (char*) malloc(sizeof(char)*1024);
                        while ((text[k]=fgetc(input))!=EOF)
                        {
                            k++;
                        }
                        text[k - 1] = '\0';
                        g_SIZE_TEXT = k - 1 ;
                    }
                    break;
                


            }
        }

char* cypher_text = (char*) malloc(sizeof(char)*strlen(text));
char** table;
    if ( ( flag_C != 0)  && ((flag_text!=0) || (flag_f!=0) ))
    {
        switch(flag_C)
        {
            case 1:
                
                if ( flag_o == 0)
                {
                    cypher_text = xor(text,key,flag_text);
                    for (int i = 0; i<(flag_text==1 ? strlen(cypher_text) : g_SIZE_TEXT);i++)
                    {   
                        printf("0x%hhX ",cypher_text[i]);
                    }
                    printf("\n");
                }
                if ( flag_o == 1)
                {
                    cypher_text = xor(text,key,flag_text);
                    FILE* output = fopen(name_output_file, "w");
                    fprintf(output,"%s", cypher_text);
                    fclose(output); 
                }
                

                break;
            case 2:
                
                if(flag_o == 0)
                {
                    
                    s_block(key,s,strlen(key));
                    cypher_text = PRGA(s,cypher_text,text,flag_text==1 ? strlen(text) : g_SIZE_TEXT);
                    for (int i = 0; i<(flag_text==1 ? strlen(cypher_text) : g_SIZE_TEXT);i++)
                    {
                        printf("0x%hhX ",cypher_text[i]);
                    }
                }
                if (flag_o == 1)
                {
                    s_block(key,s,strlen(key));
                    cypher_text = PRGA(s,cypher_text,text,flag_text==1 ? strlen(text) : g_SIZE_TEXT);
                    FILE* output = fopen(name_output_file, "w");
                    fprintf(output,"%s", cypher_text);
                    fclose(output); 
                }
                break;
            
            case 3:
                if(flag_o == 0)
                {
                    table = generation_table(key);
                    cypher_text = vigener(table,key,text,strlen(text));
                    for (int i = 0; i<strlen(cypher_text);i++)
                    {
                        printf("%c ",cypher_text[i]);
                    }
                }
                if (flag_o == 1)
                {
                    table = generation_table(key);
                    cypher_text = vigener(table,key,text,strlen(text));
                    FILE* output = fopen(name_output_file, "w");
                    fprintf(output,"%s", cypher_text);                
                    fclose(output); 
                }

                
                break;

            case 4:
                if (flag_o == 1) {
                    rsa(text, name_output_file);
                } else {
                    rsa(text, NULL);
                }
                break;
        }
        

       
    }
    
    return 0;
}