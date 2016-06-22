/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:bankIO.c
 */

#ifndef BANKIO_H_
#define BANKIO_H_

#include "client.h"

#define FILENAMESIZE 50


typedef struct Strings{
	char* familyName;				/* family name of a client */
	char clientID[CLIENTIDL];					/* the ID number of a client */
	accountNum clientAcc;			/* the client account number */
}clientString;


char * decompressFile( char *);


    
char* compressFile(char*);

    
clientString* clientToString(client*);


clientString* copyClientStings(clientString*);



try openFile(char*,char*);


void closeFile();


void printClientToFile(client*);


genTree* readClientFromFile();


comparison compareClientSurname(clientString*,clientString*);


char* sortBySurename(char*);


char* fileEncDec(char*,char*);


#endif /* BANKIO_H_ */
