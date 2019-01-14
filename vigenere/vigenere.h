
#define CIFRURI_LIBRARY_H
#define CIFRURI_LIBRARY_H

#define alphabetSize 26

const char alphabetLowercase[alphabetSize] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
const char alphabetUppercase[alphabetSize] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

char* caesarEncrypt(int , char* );
char* caesarDecrypt(int , char* );

char* vigenereEncrypt(char* , char* );
char* vigenereDecrypt(char* , char* );

#endif
