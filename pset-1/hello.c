#include <stdio.h> // print
#include <cs50.h>  // get_int

int main(void)
{
    string name = get_string("Enter your name: ");
    printf("Hello, %s\n", name);

}


