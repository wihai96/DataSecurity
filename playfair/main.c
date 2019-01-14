#include <stdio.h>
#include "Playfair.c"

int main() {
    printf("%s\n",playfairEncrypt("POWERFULL",'J','I',"OQRMRUMIVPUQGHGGFGDI"));
    printf("%s\n",playfairDecrypt("POWERFULL",'J','I',"EMOSOBSDTOAMHINWLCGC"));
    return 0;
}
