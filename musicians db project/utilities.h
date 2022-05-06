#ifndef UTILITIES_H
#define UTILITIES_H

#include "instrument_tree.h"

void checkMemoryAllocation(void* ptr);

void checkFile(FILE* file);

long int fileSize(FILE* fp);

#endif // !UTILITIES_H