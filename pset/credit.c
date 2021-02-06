#include<stdio.h>
#include<cs50.h>

int main(void) {

    string code = get_string("Ingrese el codigo de su tarjeta de credito");
    /* 378282246310005 */
    printf("%c", code[1]);


    return 0;
}