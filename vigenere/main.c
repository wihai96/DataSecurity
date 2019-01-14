#include <stdio.h>
#include "vigenere.c"

int main() {
    printf("%s\n",vigenereDecrypt("dintnofnthtittf","smbiystsflwqhvwhiobywyllvfmmbrhanvu"));
    printf("%s\n",vigenereEncrypt("DINTNOFNTHTITTF","PEOPUEOFMEDIHCREABIUITYSOMETIMESACQ"));
    return 0;
}
