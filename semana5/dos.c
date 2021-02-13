#include<stdio.h>
#include<cs50.h>

int main() {
    int number;
    int number2 = 95;

    number = get_int("\nIngrese el número 95\n");

    if(number >= 100) {
        printf("Error, el número debe ser > 0 y < 100\n");
        // Para que finalize el  código
        return 0;
    }
    if(number >= 90 && number <= 100) {
        printf("Tienes una A\n");
        // Para que finalize el  código
        return 0;
    }
    if(number >= 80 && number < 90) {
        printf("Tienes una B\n");
        // Para que finalize el  código
        return 0;
    }
    if(number >= 60 && number < 80) {
        printf("Tienes una C\n");
        // Para que finalize el  código
        return 0;
    }
    if(number < 60) {
        printf("Tienes una D\n");
        // Para que finalize el  código
        return 0;
    }
    if(number > 0) {
        printf(">:v\n");
        // Para que finalize el  código
        return 0;
    }

}
