#ifndef MUSICIAN_H
#define MUSICIAN_H

#include "musician_list.h"
#include "instrument_tree.h"

typedef struct
{
	char** name; // arr of musicians full name
	MPIList instruments; // list of the instruments the musicians plays
} Musician;

Musician*** createMusicianCollection(Musician* musicianGroup, int numOfMusicians, int numOfInstruments, int* musiciansPerIns);

Musician* createMusicainGroup(FILE* data, InstrumentTree tree, int numOfInstruments, int** musiciansPerIns, int* size);

Musician* memoryAllocations(Musician* arr, int* physicalSize, int logicalSize);

char** getNames(char* line, int index, InstrumentTree tree, char* symbols, char** newLine);

MPIList getInstruments(char* line, char* symbols, InstrumentTree tree, int numOfInstruments, int* musiciansPerIns);

#endif // !MUSICIAN_H