#include<stdio.h>
#include<cs50.h>

int main(void) {
    int height = 0;
    height = get_int("\nIngrese la altura de la piramide\n");


    for(int i = 0; i<=height - 1; i++) {
        for(int j = 0; j <= height; j++) {
            if(j > height - i) {
                printf("#");
            } else {
                printf("-");
            }
            if(j == height) {
                printf("\n");
            }
        }
        printf("\n");
    }

    return 0;
}