
#include "Cifruri.h"
#include "Caesar.c"
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

char* beaufortUniversal(char *key, char *text){
    if(textAndKeyIsValid(key,text)){
        char *newText, *pNewText, *pText, *pKey;

        size_t newTextSize = strlen(text) + 1;
        newText = (char*)malloc(newTextSize*sizeof(char));
        pText = text;
        pKey = key;
        pNewText = newText;

        while(*pText!='\000'){
            if(isLowercaseLetter(*pText)){
                *pNewText = positionToLowercaseLetter(alphabetSize-letterToPosition(*pText)+letterToPosition(*pKey));
            }
            if(isUppercaseLetter(*pText)){
                *pNewText = positionToUppercaseLetter(alphabetSize-letterToPosition(*pText)+letterToPosition(*pKey));
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


char* beaufortEncrypt(char *key, char *text){
    return beaufortUniversal(key, text);
}
char* beaufortDecrypt(char *key, char *text){
    return beaufortUniversal(key, text);
}
