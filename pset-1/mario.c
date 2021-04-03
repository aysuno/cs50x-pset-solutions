#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int input = 0;
    do 
    {
        input = get_int("Height: ");
    }
    while (input < 1 || input > 8);

    for (int i = 1; i <= input; i++)
    {
      for(int k=1; k <= input-i; k++)
      {
        printf(" ");
      }
      for (int j = 1; j <= i ; j++)
      {
          printf("#");
      }
      printf("\n");

  }

}
