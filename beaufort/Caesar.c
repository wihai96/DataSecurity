
#include "Cifruri.h"
#include <stdlib.h>
#include <string.h>

int letterToPosition (char letter) {
    for (int i = 0; i < alphabetSize; ++i) {
        if (letter == alphabetLowercase[i] || letter == alphabetUppercase[i]) {
            return i;
        }
    }
    return -1;
}

char positionToLowercaseLetter(int position){
    if(position / alphabetSize  > 0){
        position = position % alphabetSize;
    }
    if(position < 0) {
        position = alphabetSize - abs(position);
    }
    return alphabetLowercase[position];
}

char positionToUppercaseLetter(int position){
    if(position / alphabetSize  > 0){
        position = position % alphabetSize;
    }
    if(position < 0) {
        position = alphabetSize - abs(position);
    }
    return alphabetUppercase[position];
}

int isLowercaseLetter (char letter){
    if(letter >= 'a' && letter <= 'z'){
        return 1;
    } else {
        return 0;
    }
}

int isUppercaseLetter (char letter){
    if(letter >= 'A' && letter <= 'Z'){
        return 1;
    } else {
        return 0;
    }
}

int textIsValid(char* text) {
    char *p;
    p = text;
    while(*p!='\000') {
        if (!(isLowercaseLetter(*p) || isUppercaseLetter(*p))) {
            return 0;
        }
        p++;
    }
    return 1;
}
