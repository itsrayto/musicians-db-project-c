#ifndef UTILITIES_H
#define UTILITIES_H

#include "instrument_tree.h"
#include "musician.h"

void checkMemoryAllocation(void* ptr);

void checkFile(FILE* file);

long int fileSize(FILE* fp);

void ourFree(InstrumentTree tree, Musician** musicianGroup, int numOfMusicians, int* musiciansPerIns, Musician*** musicianCollection, int numOfIns);

void freeTree(TreeNode* root);

void freeMusicianGroup(Musician** musicianGroup, int numOfMusicians);

void freeMusicianCollection(Musician*** musicianCollection, int numOfIns);

#endif // !UTILITIES_H