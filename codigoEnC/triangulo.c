#include<stdio.h>

const char* validar_un_triangulo(int angulo1, int angulo2, int angulo3);

int main(void) {
    const char* xdd = validar_un_triangulo(1, 1, 3);

    printf("\n%s\n", xdd);
    return 0;
}

/* Código spagueti :,v */
const char* validar_un_triangulo(int angulo1, int angulo2, int angulo3) {
    if(angulo1 > 0 && angulo2 > 0 &&  angulo3 > 0) { /* Valida todos los lados */
        if(angulo1+angulo2 > angulo3) {
            if(angulo1 + angulo3 > angulo2) {
                if(angulo2 + angulo3 > angulo1) { /* Valida la suma de dos angulos son mayores al tercero */
                    return "Si es un triangulo";
                } else {
                    return "Un lado no es igual";
                }
            } else {
                return "Un lado no es igual";
            }
        } else {
            return "Un lado no es igual";
        }
    }
    return "sdadc";
}
