
#include "vigenere.h"
#include "vigenere.c"
#include <stdlib.h>

int textAndKeyIsValid(char *key , char *text){
    char *pText, *pKey;
    pText = text;
    pKey = key;
    while(*pText!='\000') {
        if (!(isLowercaseLetter(*pText) || isUppercaseLetter(*pText))) {
            return 0;
        }
        if (!(isLowercaseLetter(*pKey) || isUppercaseLetter(*pKey))) {
            return 0;
        }
        if (!(isLowercaseLetter(*pText) == isLowercaseLetter(*pKey)
              || isUppercaseLetter(*pText) == isUppercaseLetter(*pKey))){
            return 0;
        }
        pText++;
        pKey++;
        if(*pKey == '\000'){
            pKey=key;
        }
    }
    return 1;
}

char* vigenereUniversal(char *key, char *text, int sign){
    if(textAndKeyIsValid(key,text)){
        char *newText, *pNewText, *pText, *pKey, c;

        size_t newTextSize = strlen(text) + 1;
        newText = (char*)malloc(newTextSize*sizeof(char));
        pText = text;
        pKey = key;
        pNewText = newText;

        while(*pText!='\000'){
            if(isLowercaseLetter(*pText)){
                *pNewText = positionToLowercaseLetter(letterToPosition(*pText)+(letterToPosition(*pKey)*sign));
            }
            if(isUppercaseLetter(*pText)){
                *pNewText = positionToUppercaseLetter(letterToPosition(*pText)+(letterToPosition(*pKey)*sign));
            }
            pText++;
            pKey++;
            pNewText++;
            if(*pKey == '\000'){
                pKey=key;
            }
        }
        return newText;
    }
    return NULL;
}


char* vigenereEncrypt(char *key, char *text){
    return vigenereUniversal(key, text, 1);
}
char* vigenereDecrypt(char *key, char *text){
    return vigenereUniversal(key, text, -1);
}
