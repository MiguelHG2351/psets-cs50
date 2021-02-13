#include<stdio.h>
#include<cs50.h>

int main(void) {
    int number;
    number = get_int("\nIngrese número entre 1 y 100  \"*\" \n ");

    if(number >= 1 && number <= 100)
    {
        for(int i = 1; number * i <= 100; i++)
        {
            printf("%d\n", number * i);
        }
    }
    else
    {
        printf("No");
    }
    return 0;
}
