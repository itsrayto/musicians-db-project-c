#include "utilities.h"
#include "instrument_tree.h"

/* checkimg if memory allocation has succeeded */
void checkMemoryAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(1);
	}
}

/* checkimg if file opening has succeeded */
void checkFile(FILE* file)
{
	if (file == NULL)
	{
		printf("Couldn't open file!\n");
		exit(1);
	}
}

/* returns the size of a given file */
long int fileSize(FILE* fp)
{
	long int res;
	long int saver = ftell(fp);

	fseek(fp, 0, SEEK_END);
	res = ftell(fp);
	fseek(fp, saver, SEEK_SET);
	return res;
}