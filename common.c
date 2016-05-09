/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:common.c
 */

#include "common.h"
#include <string.h>
#include <ctype.h>


/*max string to read in fgets*/
#define MAXSTRING 50


/*get string from user, check for legibility comparing to length of word and only letters.*/
void getName(char** name , int length, char* output){
    int i,len;
    boolean check = TRUE;       /*flag for testing input*/
    char temp[MAXSTRING];
    i=0;
    do{
        printf("%s",output);
        check = TRUE;
        fgets(temp, MAXSTRING, stdin);
        /*check entered string length*/
        len=(int)strlen(temp);
        if(len>length || len<2){
            check = FALSE;
            printf("the lengh of word is not in range(1-%d)\n",length);
            continue;
        }
        /*check if string has only letters.*/
        for(i=0;i<len-1;i++)     /* -1 in order to ignore the '\n'*/
            if(!isalpha(temp[i])){
                check=FALSE;
                printf("illegal characters\n");
                break;
            }
    }while(check==FALSE);
    temp[i]='\0';
    *name = str_dup(temp);
}

/*get client id from user with 9 digits.*/
void getClientID(clientID * id){
    char temp[MAXSTRING];
    boolean check = TRUE;    /*flag for testing input*/
    int i=0 ,len=0;
    
    do{
        check = TRUE;
        printf("Please enter client ID (9 digits)\n");
        fgets(temp, MAXSTRING, stdin);
        /*check id length*/
        len=(int)strlen(temp);
        if(len-1!=CLIENTIDL-1){   /* -1 in order to ignore the '\n'*/
            check=FALSE;
            printf("Wrong id length (%d)\n",CLIENTIDL-1);
            continue;
        }
        /*check if id have only digits*/
        for(i=0;i<len-1;i++)    /* -1 in order to ignore the '\n'*/
            if(!isdigit(temp[i])){
                check=FALSE;
                printf("illegal characters\n");
                break;
            }
    }while(check==FALSE);
    temp[CLIENTIDL-1]='\0';
    strcpy(id, temp);
}



/*get an integer from user */
void getInt(int* num,char* output){
    char temp[MAXSTRING];
    int i,len;
    boolean check;  /*flag for testing input*/
    
    do{
        check = TRUE;
        printf("%s",output);
        fgets(temp, MAXSTRING, stdin);
        
        /*check entered string is number*/
        len=(int)strlen(temp);
        for(i=0;i<len-1;i++)     /* -1 in order to ignore the '\n'*/
            if(!isdigit(temp[i])){
                check=FALSE;
                printf("illegal characters\n");
                break;
            }
    }while(check==FALSE);
    *num = atoi(temp);
}

/*get an double from user */
void getDouble(double* num, char* output){
    char temp[MAXSTRING];
    int i,len;
    boolean check;  /*flag for testing input*/

    do{
        check = TRUE;
        printf("%s",output);
        fgets(temp, MAXSTRING, stdin);

        /*check entered string is number*/
        len=(int)strlen(temp);
        for(i=0;i<len-1;i++)     /* -1 in order to ignore the '\n'*/
            if(!isdigit(temp[i])){
                check=FALSE;
                printf("illegal characters\n");
                break;
            }
    }while(check==FALSE);
    *num = atol(temp);
}
