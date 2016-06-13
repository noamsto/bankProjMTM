/* bank project
 Yahel Tsufim 304952898
 Noam Stolero 201581683
 file:matam.c
 */




#include "matam.h"
#include <string.h>

/* Allocation Counter. */
static unsigned int allocated_blocks = 0;

void *checked_malloc(unsigned int size) /* allocating memory, checking if succeded and incremneting counter. */
{
	void * ret;

	ret = malloc(size);
	if (!ret) {
		perror ("Memory allocation error");
		exit (1);
	}
	allocated_blocks++;
	return ret;
}

void checked_free (void *ptr)   /* free alocated memory and decrement counter. */
{

	free(ptr);
	allocated_blocks--;
	return;
}

/* print a message if any allocated memory was nit freed. */
void check_for_exit() {
	if (allocated_blocks) {
		fprintf (stderr, "Memory leak: %d memory blocks still allocated \n", allocated_blocks);
		exit(1);
	}
        return;
}

char* str_dup(const char* copy) /* str dup function working with upper functions. */
{
    char* create;
    create = ALLOC(char,(int)strlen(copy));
    strcpy(create,copy);
    return create;
}
