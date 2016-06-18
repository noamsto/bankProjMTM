/*
 * bankIO.c
 *
 *  Created on: Jun 18, 2016
 *      Author: yali
 */

#include "bankIO.h"

FILE* target;


clientString* clientToString(client*);


clientString* copyClientStings(clientString*);


void openFile(char*,char*);


void closeFile(){
	fclose(target);
}


void printClientToFile(clientString* cs)
{
	fprintf(target,"%s %s %d",cs->familyName,cs->clientID,cs->clientAcc);
}


genTree* readClientFromFile(FILE*)
{
	genTree* fileData;
	clientString newClient,*readclient;
	while((fscanf(target,"%s %s %d",newClient.familyName,newClient.clientID,newClient.clientAcc))>0){
		readclient = copyClientStings(newClient);
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
