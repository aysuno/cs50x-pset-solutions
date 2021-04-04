#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for(int i = 0; i < strlen(argv[1]); i++)
    {
        if(!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    } //check done
    int conv = atoi(argv[1]);
    string text = get_string("plaintext: ");

    for (int k = 0; k < strlen(text); k++)
    {
        if(isupper(text[k]))
        {
            text[k] = ((text[k] - 'A') + conv ) % 26 + 'A';
        }
        else if(islower(text[k]))
        {
            text[k] = ((text[k] - 'a') + conv ) % 26 + 'a';
        }
        else
        {
            text[k] = text[k];
        }  
    }
    printf("ciphertext: %s\n", text);
}
