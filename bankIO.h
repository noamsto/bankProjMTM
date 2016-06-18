/*
 * bankIO.h
 *
 *  Created on: Jun 18, 2016
 *      Author: yali
 */

#ifndef BANKIO_H_
#define BANKIO_H_

#include "client.h"



typedef struct Strings{
	char* familyName;				/* family name of a client */
	char* clientID;					/* the ID number of a client */
	accountNum clientAcc;			/* the client account number */
}clientString;

clientString* clientToString(client*);


clientString* copyClientStings(clientString*);


void openFile(char*,char*);


void closeFile();


void printClientToFile(clientString*);


genTree* readClientFromFile(FILE*);


comparison compareClientSurname(clientString*,clientString*);




#endif /* BANKIO_H_ */
