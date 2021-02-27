#include<stdio.h>
#include<cs50.h>
// Importing the POSIX regex library
#include <regex.h>

int main(void) {
    regex_t regex;
    string return_value = get_string("Ingrese una palabra de la a-Z");
    // return_value = regcomp(&regex,"[:lower:]",0);
    if (regcomp(&regex, "%[a-zA-Z]", )){
        printf("Regular expression compiled successfully.");
    }
    else{
        printf("Compilation error.");
    }
    return 0;
}