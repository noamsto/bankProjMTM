#include "matam.h"
#include <string.h>


static unsigned int allocated_blocks = 0;

void *checked_malloc(unsigned int size)
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

void checked_free (void *ptr)
{

	free(ptr);
	allocated_blocks--;
	return;
}

void check_for_exit() {
	if (allocated_blocks) {
		fprintf (stderr, "Memory leak: %d memory blocks still allocated \n", allocated_blocks);
		exit(1);
	}
        return;
}

char* str_dup(const char* copy)
{
    char* create;
    create = ALLOC(char,(int)strlen(copy));
    strcpy(create,copy);
    return create;
}
