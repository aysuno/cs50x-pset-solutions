#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./vigenere key\n");
        return 1;
    }
    for(int i = 0; i < strlen(argv[1]); i++)
    {
        if(isalpha(argv[1][i]) == false)
        {
            printf("Usage: ./vigenere key\n");
            return 1;
        }
    } //check done
    string key = argv[1];
    string text = get_string("plaintext: ");
    for (int k = 0, index = 0; k < strlen(text); k++)
    {
            if(text[k] >= 'A' && text[k] <= 'Z')
            {
                for (int m = 0; m < strlen(key); m++)
                {
                    key[m] = toupper(key[m]);
                }
                text[k] = ((text[k] - 'A') + (key[index % strlen(key)]-'A') ) % 26 + 'A';
                index = (index + 1);
            }
            else if(text[k] >= 'a' && text[k] <= 'z')
            {
                for (int n = 0; n < strlen(key); n++)
                {
                    key[n] = tolower(key[n]);
                }
                text[k] = ((text[k] - 'a') + (key[index % strlen(key)]- 'a') ) % 26 + 'a';
                index = (index + 1);
            }
            else
            {
                text[k] = text[k];      
            }             
    }
    printf("ciphertext: %s\n", text);
}
