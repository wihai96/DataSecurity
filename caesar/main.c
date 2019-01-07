#include<stdio.h>

int main()
{
    int a;
    scanf("%d", &a);
    if(a==1)
        encrypt();
    else
        decrypt();

    return 0;

}
void encrypt()
{
    char message[100], ch;
    int i, key;
    printf("Enter a message to encrypt: ");
    scanf("%s", message);
 /* gets(message);*/
    printf("Enter key: ");
    scanf("%d", &key);

    for(i = 0; message[i] != '\0'; ++i){
        ch = message[i];

        if(ch >= 'a' && ch <= 'z'){
            ch = ch + key;

            if(ch > 'z'){
                ch = ch - 'z' + 'a' - 1;
            }

            message[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch + key;

            if(ch > 'Z'){
                ch = ch - 'Z' + 'A' - 1;
            }

            message[i] = ch;
        }
    }

    printf("Encrypted message: %s", message);
}

void decrypt()
{
    char message[100], ch;
    int i, key;
    printf("Enter a message to decrypt: ");
    scanf("%s", message);
   /* gets(message);*/
    printf("Enter key: ");
    scanf("%d", &key);

    for(i = 0; message[i] != '\0'; ++i){
        ch = message[i];

        if(ch >= 'a' && ch <= 'z'){
            ch = ch - key;

            if(ch < 'a'){
                ch = ch + 'z' - 'a' + 1;
            }

            message[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch - key;

            if(ch < 'A'){
                ch = ch + 'Z' - 'A' + 1;
            }

            message[i] = ch;
        }
    }

    printf("Decrypted message: %s", message);
}