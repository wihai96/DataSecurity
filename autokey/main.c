#include <stdio.h>
#include "Autokey.c"
int main() {
    printf("%s",autokeyEncrypt("GHEORGHE","MADALIN",'J','I',"ANAAREMERE"));
    printf("\n%s",autokeyDecrypt("GHEORGHE","MADALIN",'J','I',"EGEVUANAUA"));
    return 0;
}
