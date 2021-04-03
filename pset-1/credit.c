// Office hour (credit 50:05): www.youtube.com/watch?v=8i_Zu3lwtD8&t=30s

#include <stdio.h>
#include <cs50.h>

int main(void)
{
long number = get_long("Kredi kartı numarası: ");

long check = number;
int counter = 0;
int ilk_iki = 0;

while(check > 0)
{
if(check <100 && check >10)
{
ilk_iki = check;
} // ilk iki basamağı tutuyorum

counter ++;
check /= 10; // check = check/10     1. 234321234     1/10 =0    12.34321234    1.234321234
}


int a = 0; // altı çizili olmayan sayıları toplama sayacı
int b = 0; //altı çizili olan sayıları toplama sayacı
while( number > 0)
{
    a += number % 10; // 13434324423 %10 = 3 
    number /= 10; // 1343432442.3
    if(number > 0)
    {
        int c = (number%10) *2; // 1343432442.3 9*2 =18 1+8 =9
        b += c/10; // 2*2 =4 4/10 = 0, 4%10 =4 0+4 = b
        b += c%10; // 18/10 = 1 ve 18%10 =8   1+8 = 9
        number /= 10; // 134343244.23
    }
}
int kalan = (a+b)%10; // son basamak sıfır mı? 13+12 =25 %10 ==5,        15+15=30%10 =0 bu kart gerçek
if( ((counter != 13) || (counter !=15) || (counter !=16)) && kalan !=0) 
{
    printf("INVALID\n");
}
else
{
    if(counter == 15 && ((ilk_iki == 34) || (ilk_iki == 37))) 
    {
        printf("AMEX\n");
    }
    else if( (ilk_iki == 51 || ilk_iki == 52  || ilk_iki == 53 || ilk_iki == 54 || ilk_iki == 55)  && counter ==16)
    {
        printf("MASTERCARD\n");
    }
    else if((ilk_iki/10 ==4) && (counter ==13 || counter ==16)) // 45/10 = 4
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
}

