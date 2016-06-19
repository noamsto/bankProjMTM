/*
 * bankIO.h
 *
 *  Created on: Jun 18, 2016
 *      Author: yali
 */

#ifndef BANKIO_H_
#define BANKIO_H_

#include "client.h"

#define FILENAMESIZE 20


typedef struct Strings{
	char* familyName;				/* family name of a client */
	char* clientID;					/* the ID number of a client */
	accountNum clientAcc;			/* the client account number */
}clientString;

clientString* clientToString(client*);


clientString* copyClientStings(clientString*);



try openFile(char*,char*);


void closeFile();


void printClientToFile(client*);


genTree* readClientFromFile();


comparison compareClientSurname(clientString*,clientString*);


void sortBySurename(char*);


#endif /* BANKIO_H_ */
