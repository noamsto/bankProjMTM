/*
 * bankIO.c
 *
 *  Created on: Jun 18, 2016
 *      Author: yali
 */

#include "bank.h"
#include <ctype.h>

#define MASC_ODD	85
#define MASC_EVEN	170

FILE* target;


clientString* clientToString(client*);


clientString* copyClientStings(clientString*);


void closeFile(){
    if(target)
        fclose(target);
    target=NULL;
}

/* convert a client struct to a clientString struct */
clientString* clientToString(client* c){
    clientString *cString=NULL;
    cString = ALLOC(clientString, 1); /* allocate a new client String struct.*/
    
    if (!c)
        return NULL;
    
    
    /* copy relevant fields */
    cString->familyName =str_dup(c->surname);
    cString->clientID= str_dup(c->cID);
    cString->clientAcc=c->accNum;
    return cString;
}


/* copy clientString to a another */
clientString* copyClientStings(clientString* source){
    clientString *target=NULL;
    if (!source)
        return NULL;
    target = ALLOC(clientString, 1); /* allocate a new client String struct.*/
    
    /* copy relevant fields */
    target->clientAcc=source->clientAcc;
    target->clientID=str_dup(source->clientID);
    target->familyName=str_dup(source->familyName);
    return target;
}


void printClientString(clientString* cs)
{
    fprintf(target,"%s %s %d\n",cs->familyName,cs->clientID,cs->clientAcc);
    
}
void printClientToFile(client* cs)
{
    fprintf(target,"%s %s %d\n",cs->surname,cs->cID,cs->accNum);
}


/* open file for read or write purposes. */
try openFile(char*path ,char* restrictions){
    
    if (target) /*if file was already open close it */
        closeFile();
    
    target=fopen(path, restrictions);   /* open file with relevant restrictions */
    if (target==NULL)
        return FAIL;
    return SUCCESS;
}


genTree* readClientFromFile()
{
    genTree* fileData=NULL;
    clientString newClient,*readclient;
    char surname[20],id[20];
    while((fscanf(target,"%s %s %d",surname,id, &newClient.clientAcc))>0){
        newClient.clientID=id;
        newClient.familyName=surname;
        readclient = copyClientStings(&newClient);
        fileData = add_new_node(fileData,readclient,(genCmp)(&compareClientSurname));
    }
    return fileData;
}


comparison compareClientSurname(clientString* a,clientString* b)
{
    int res;
    res = strcmp(a->familyName,b->familyName);
    if(res>0)
        return GREATER;
    else if(res<0)
        return SMALLER;
    return EQUAL;
}

void deleteClientString(clientString* del)
{
    FREE(del->clientID);
    FREE(del->familyName);
    FREE(del);
}

char* sortBySurename(char fileName[FILENAMESIZE])
{
    genTree* t = NULL;
    openFile(fileName, "r");
    t = readClientFromFile();
    strcat(fileName, ".sort");
    openFile(fileName, "w+");
    
    print_tree(t, (genPrint)(&printClientString));
    free_list(&t, (genDelete)&deleteClientString);
    closeFile();
    return fileName;
    
}


char* changeToNumber(char* str)
{
    char* head = str;
    while(*str!='\0'){
        *str = toupper(*str);
        *str = (*str - 'A' + 2);
        str++;
    }
    return head;
}




void compressor(char* str, char* cmpr){
    char mask=32, res = '\0';
    int i=8, len=0;
    len=(int)strlen(str);
    while (len--){
        
        for (mask=16; mask>0; mask>>=1){
            if (i==0){
                *(cmpr++)=res;
                i=8;
                res=0;
            }
            res<<=1;
            if ((*str & mask) !=0){
                res |=1;
            }
            i--;
        }
        str++;
    }
    if (i>0){
        res<<=i;
        *cmpr=res;
    }
}





//void compressStr(char* str,char** cmpr)
//{
//    int cmprInd=0,cpyI=0,i=0;
//    char temp[20]={0};
//    while(*str!=0){/*loop for all the string*/
//        for(cpyI=4;cpyI>=0;cpyI--){
//            
//            if(cmprInd==8){
//                i++;
//                cmprInd=0;
//            }
//            temp[i] = temp[i] | ((*str >> cpyI) & 1);
//            if(cpyI)
//                temp[i] <<= 1;
//            cmprInd++;
//        }
//        str++;
//    }
//}

char* nameCmpr(char* str)
{
    char len, *cmpr=NULL;
    len = (char)strlen(str);
    cmpr=ALLOC(char, len);
    str = changeToNumber(str);
    cmpr++;
    compressor(str,cmpr);
    cmpr--;
    cmpr[0]=(len*5/8)+1;
    return cmpr;
    
}




void printCmpr(clientString *c){
    char *cmpr;
    short accNum;
    cmpr=nameCmpr(c->familyName);
    fwrite(cmpr, cmpr[0]+1, sizeof(char), target);
    fwrite(c->clientID,CLIENTIDL,sizeof(char),target);
    accNum=(short)(c->clientAcc);
    fwrite(&accNum, 1, sizeof(short), target);
}

char* compressFile(char * fileName){
    
    genTree* t = NULL;
    openFile(fileName, "r");
    t = readClientFromFile();
    
    strcat(fileName, ".cmpr");
    openFile(fileName, "w+");
    
    print_tree(t, (genPrint)(&printCmpr));
    free_list(&t, (genDelete)&deleteClientString);
    closeFile();
    
    return fileName;
}


char charEncDec(char* a)/* encrypt the received char and return an encrypted char */
{
	char encrypt=0;
	char odd,even;
	odd = (*a & MASC_ODD) << 1;
	even = (*a & MASC_EVEN) >> 1;
	encrypt =  odd | even;
	return encrypt;

}



void textEncDec(char* text,long textSize)
{
	long i=0;
	for(i=0;i<textSize;i++){
		text[i] = charEncDec(text+i);
	}

}



char* readBinaryFile(FILE* file,long* byteSize)
{
	char* text=NULL;
	fseek(file,0,SEEK_END);
	*byteSize = ftell(file);
	text = ALLOC(char,*byteSize);
	fread(text,sizeof(char),*byteSize,file);
	return text;

}


void writeBinaryFile(FILE* output,char* text,long length)
{
	fwrite(text,sizeof(char),length,output);
}



char* fileEncDec(char* fileName,char* addFileName)
{
	char* text=NULL;
	long fileSize=0;
	openFile(fileName, "r");
	text = readBinaryFile(target,&fileSize);
	textEncDec(text,fileSize);
	closeFile();
	strcat(fileName,addFileName);
	openFile(fileName,"w+");
	writeBinaryFile(target,text,fileSize);
	return fileName;
}


