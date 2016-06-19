/*
 * bankIO.c
 *
 *  Created on: Jun 18, 2016
 *      Author: yali
 */

#include "bank.h"

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


void sortBySurename(char fileName[FILENAMESIZE])
{
    genTree* t = NULL;
    openFile(fileName, "r");
    t = readClientFromFile();
    strcat(fileName, ".sort");
    openFile(fileName, "w+");
    
    print_tree(t, (genPrint)(&printClientString));
    free_list(&t, (genDelete)&deleteClientString);
    closeFile();
}



