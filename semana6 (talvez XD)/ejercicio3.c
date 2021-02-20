#include<stdio.h>

int main(void)
{
    int number[100];

    for(int i = 0; i < 100;i++)
    {
        number[i] = i + 1;
    }

    for(int i = 0; i < 100;i++)
    {
        if(i != 99)
        {
            printf("%d, ", number[i]);
        }
        else
        {
            printf("%d.", number[i]);
        }
    }
}
