#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int counter = 0;
    float my_input;
    
    do 
    {
        my_input = get_float("Change owed: \n");
    }
    while (my_input <= 0);
       
    int act_input = round(my_input * 100);
    
    int twentyfive = act_input / 25;
    counter = counter + twentyfive;
    int first_remain = act_input % 25;
    int ten = first_remain / 10;
    counter = counter + ten;
    int second_remain = first_remain % 10;
    int five = second_remain / 5;
    counter = counter + five;   
    int third_remain = second_remain % 5;
    counter = counter + third_remain;
    
    printf("%i\n", counter);  
}
