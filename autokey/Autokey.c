
#include "Cifruri.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
        if (!isUppercaseLetter(*p)) {
            return 0;
        }
        p++;
    }
    return 1;
}

char* removeDuplicateCharacters(char* text){
    char *p,*newText,*buffer,*q;
    size_t bufferSize = strlen(text) + 1;
    buffer = (char*)malloc(bufferSize*sizeof(char));
    strcpy(buffer,text);
    p=buffer;
    while(*(p+1)!='\000') {
        q=strchr(p+1,*p);
        while(q){
            strcpy(q,q+1);
            q=strchr(p+1,*p);
        }
        p++;
    }
    size_t newTextSize = strlen(buffer) + 1;
    newText = (char*)malloc(newTextSize*sizeof(char));
    strcpy(newText,buffer);
    free(buffer);
    return newText;
}

void mappingMatrix(char *key, char translateLetter, int shiftI, int shiftJ){
    char *p,*newKey;
    newKey = removeDuplicateCharacters(key);
    p = newKey;
    int x=0;
    for(int i=0+shiftI; i<matrixSize+shiftI; i++){
        for(int j=0+shiftJ; j<matrixSize+shiftJ; j++){
            if(*p!='\000') {
                alphabetMatrixAutokey[i][j] = *p;
                p++;
            } else{
                while (strchr(newKey,alphabetUppercase[x])){
                    x++;
                }
                if(alphabetUppercase[x] != translateLetter){
                    alphabetMatrixAutokey[i][j] = alphabetUppercase[x];
                }else{
                    x++;
                    alphabetMatrixAutokey[i][j] = alphabetUppercase[x];
                }
                x++;
            }
        }
    }
}

char* replaceCharacter(char oldCharacter, char newCharacter, char *text)
{
    char *newText, *p;
    size_t newTextSize = strlen(text) + 1;
    newText = (char*)malloc(newTextSize*sizeof(char));
    strcpy(newText,text);
    p=newText;
    while(*p!='\000') {
        if(*p==oldCharacter){
            *p=newCharacter;
        }
        p++;
    }
    return newText;
}

int minimum(int firstNumber, int secondNumber){
    if(firstNumber<secondNumber){
        return firstNumber;
    } else {
        return secondNumber;
    }
}

int maximum(int firstNumber, int secondNumber){
    if(firstNumber>secondNumber){
        return firstNumber;
    } else {
        return secondNumber;
    }
}

struct Slice* sliceExtract(char firstLetter, char secondLetter, int sign){
    struct Slice *slice = (struct Slice*)malloc(sizeof(struct Slice));
    int xFirstLetter,yFirstLetter,xSecondLetter, ySecondLetter, shiftI, shiftJ;
    shiftI=shiftJ=0;
    xFirstLetter=yFirstLetter=xSecondLetter=ySecondLetter=-1;
    if(sign==1){
        shiftI=0;
        shiftJ=0;
    }
    if(sign==-1){
        shiftI=0;
        shiftJ=5;
    }
    for(int i=0+shiftI; i<matrixSize+shiftI; i++){
        for(int j=0+shiftJ; j<matrixSize+shiftJ; j++){
            if(firstLetter==alphabetMatrixAutokey[i][j]){
                xFirstLetter = i;
                yFirstLetter = j;
            }

        }
    }

    if(sign==1){
        shiftI=5;
        shiftJ=5;
    }
    if(sign==-1){
        shiftI=5;
        shiftJ=0;
    }
    for(int i=0+shiftI; i<matrixSize+shiftI; i++){
        for(int j=0+shiftJ; j<matrixSize+shiftJ; j++){
            if(secondLetter==alphabetMatrixAutokey[i][j]){
                xSecondLetter = i;
                ySecondLetter = j;
            }

        }
    }


    if(xFirstLetter != -1 && yFirstLetter != -1 && xSecondLetter != -1 && ySecondLetter != -1) {
        slice->nrRows = (int*)malloc(sizeof(int));
        slice->nrColumns = (int*)malloc(sizeof(int));
        *slice->nrRows = abs(xFirstLetter-xSecondLetter)+1;
        *slice->nrColumns = abs(yFirstLetter-ySecondLetter)+1;
        size_t sliceMatrixSize = (size_t)(*slice->nrRows)*(*slice->nrColumns) + 1;
        slice->matrix = (char*)malloc(sliceMatrixSize*sizeof(char));
        char *p;
        p=slice->matrix;
        if(*slice->nrRows>1 && *slice->nrColumns>1){
            for (int i = minimum(xFirstLetter, xSecondLetter); i <= maximum(xFirstLetter, xSecondLetter); i++) {
                for (int j = minimum(yFirstLetter, ySecondLetter); j <= maximum(yFirstLetter, ySecondLetter); j++) {
                    *p = alphabetMatrixAutokey[i][j];
                    p++;
                }
            }
        } else{
            if(firstLetter == secondLetter){
                *p = firstLetter;
            }
            if(*slice->nrRows==1) {
                for (int i = minimum(xFirstLetter, xSecondLetter); i <= maximum(xFirstLetter, xSecondLetter); i++) {
                    for (int j = 0; j < matrixSizeAutokey; j++) {
                        *p = alphabetMatrixAutokey[i][j];
                        p++;
                    }
                }
                *slice->nrColumns=matrixSizeAutokey;
            }
            if(*slice->nrColumns==1) {
                for (int i = 0; i < matrixSizeAutokey; i++) {
                    for (int j = minimum(yFirstLetter, ySecondLetter); j <= maximum(yFirstLetter, ySecondLetter); j++) {
                        *p = alphabetMatrixAutokey[i][j];
                        p++;
                    }
                }
                *slice->nrRows=matrixSizeAutokey;
            }
        }
        return slice;
    }
    return NULL;
}

struct TwoLetters* twoLettersExtract(struct Slice *slice, char firstLetter, char secondLetter, int sign)
{
    struct TwoLetters *twoLetters =  (struct TwoLetters*)malloc(sizeof(struct TwoLetters));
    twoLetters->firstLetter = (char*)malloc(sizeof(char));
    twoLetters->secondLetter = (char*)malloc(sizeof(char));
    if(*slice->nrRows==1 && *slice->nrColumns>1){
        int j=0;
        while (j<*slice->nrColumns){
            if(*(slice->matrix+j)==firstLetter){
                break;
            }
            j++;
        }
        j=(j+(1*sign));

        if(j>=*slice->nrColumns){
            j=j%*slice->nrColumns;
        }
        if(j<0){
            j=*slice->nrColumns+j;
        }
        *twoLetters->firstLetter = *(slice->matrix+j);

        j=0;
        while (j<*slice->nrColumns){
            if(*(slice->matrix+j)==secondLetter){
                break;
            }
            j++;
        }
        j=(j+(1*sign));

        if(j>=*slice->nrColumns){
            j=j%*slice->nrColumns;
        }
        if(j<0){
            j=*slice->nrColumns+j;
        }
        *twoLetters->secondLetter = *(slice->matrix+j);

    }
    if(*slice->nrColumns==1 && *slice->nrRows>1){
        int i=0;
        while (i<*slice->nrRows){
            if(*(slice->matrix+i)==firstLetter){
                break;
            }
            i++;
        }
        i=(i+(1*sign));

        if(i>=*slice->nrRows){
            i=i%*slice->nrRows;
        }
        if(i<0){
            i=*slice->nrRows+i;
        }
        *twoLetters->firstLetter = *(slice->matrix+i);

        i=0;
        while (i<*slice->nrRows){
            if(*(slice->matrix+i)==secondLetter){
                break;
            }
            i++;
        }
        i=(i+(1*sign));

        if(i>=*slice->nrRows){
            i=i%*slice->nrRows;
        }
        if(i<0){
            i=*slice->nrRows+i;
        }
        *twoLetters->secondLetter = *(slice->matrix+i);
    }
    if(*slice->nrColumns>1 && *slice->nrRows>1){
        if(*slice->matrix==firstLetter){
            *twoLetters->firstLetter = *(slice->matrix+(*slice->nrColumns-1));
            *twoLetters->secondLetter = *(slice->matrix+(*slice->nrRows-1)*(*slice->nrColumns));
        }
        if(*(slice->matrix+(*slice->nrColumns-1))==firstLetter){
            *twoLetters->firstLetter = *slice->matrix;
            *twoLetters->secondLetter = *(slice->matrix+(*slice->nrRows)*(*slice->nrColumns)-1);
        }
        if(*(slice->matrix+(*slice->nrRows-1)*(*slice->nrColumns))==firstLetter){
            *twoLetters->firstLetter= *(slice->matrix+(*slice->nrRows)*(*slice->nrColumns)-1);
            *twoLetters->secondLetter = *slice->matrix;
        }
        if(*(slice->matrix+(*slice->nrRows)*(*slice->nrColumns)-1)==firstLetter){
            *twoLetters->firstLetter= *(slice->matrix+(*slice->nrRows-1)*(*slice->nrColumns));
            *twoLetters->secondLetter = *(slice->matrix+(*slice->nrColumns-1));
        }
        if(*slice->nrColumns==1 && *slice->nrRows==1){
            *twoLetters->firstLetter = *twoLetters->secondLetter = *slice->matrix;
        }
    }
    return twoLetters;
}

char* autokeyUniversal(char *key1, char *key2, char translateLetter, char intoLetter, char *text, int sign){
    if(textIsValid(key1) && textIsValid(key2) && isUppercaseLetter(translateLetter) && isUppercaseLetter(intoLetter) && textIsValid(text)){
        char *newText,*r;
        mappingMatrix("",translateLetter,0,0);
        mappingMatrix(replaceCharacter(translateLetter,intoLetter,key1),translateLetter,0,5);
        mappingMatrix(replaceCharacter(translateLetter,intoLetter,key2),translateLetter,5,0);
        mappingMatrix("",translateLetter,5,5);

        size_t newTextSize = strlen(text) + 1;
        newText = (char*)malloc(newTextSize*sizeof(char));
        r=newText;
        struct Slice *slice;
        struct TwoLetters *twoLetters;
        char *p,*q;
        p=text;
        q=p+1;
        while(*(p+2)!='\000' && *(q+1)!='\000') {
            if(*p!=*q) {
                slice = sliceExtract(*p, *q, sign);
                twoLetters=twoLettersExtract(slice, *p, *q, sign);
            } else{
                slice = sliceExtract(*p, 'X', sign);
                twoLetters=twoLettersExtract(slice, *p, 'X', sign);
            }
            *r=*twoLetters->firstLetter;
            *(r+1)=*twoLetters->secondLetter;
            p = p + 2;
            q = q + 2;
            r = r + 2;
            if(*(p)=='\000') {
                break;
            }
            if(*(q)=='\000') {
                break;
            }
        }
        if(isUppercaseLetter(*p)){
            if(isUppercaseLetter(*q)){
                if(*p!=*q) {
                    slice = sliceExtract(*p, *q, sign);
                    twoLetters=twoLettersExtract(slice, *p, *q, sign);
                } else{
                    slice = sliceExtract(*p, 'X', sign);
                    twoLetters=twoLettersExtract(slice, *p, 'X', sign);
                }
                *r=*twoLetters->firstLetter;
                *(r+1)=*twoLetters->secondLetter;

            } else {
                slice=sliceExtract(*p,'X', sign);
                twoLetters=twoLettersExtract(slice, *p, *q, sign);
                *r=*twoLetters->firstLetter;
                *(r+1)=*twoLetters->secondLetter;
            }
        }
        return newText;
    }
    return NULL;
}

char* autokeyEncrypt(char *key1, char *key2, char translateLetter, char intoLetter, char *text) {
    return autokeyUniversal(key1, key2, translateLetter, intoLetter, text, 1);

}

char* autokeyDecrypt(char *key1, char *key2, char translateLetter, char intoLetter, char *text) {
    return autokeyUniversal(key1, key2, translateLetter, intoLetter, text, -1);
}
