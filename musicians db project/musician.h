#ifndef MUSICIAN_H
#define MUSICIAN_H

#include "instrument_tree.h"
#include "musician_list.h"

typedef struct
{
	char** name; // arr of musicians full name
	MPIList instruments; // list of the instruments the musicians plays
	bool taken;
} Musician;

typedef struct
{
	Musician* musician;
	unsigned short insId;
	char importance;
}concertMusician;

Musician*** createMusicianCollection(Musician** musicianGroup, int numOfMusicians, int numOfInstruments, int* musiciansPerIns);

Musician** createMusicainGroup(FILE* data, InstrumentTree tree, int numOfInstruments, int** musiciansPerIns, int* size);

Musician** memoryAllocations(Musician** arr, int* physicalSize, int logicalSize);

char** getNames(char* line, int index, InstrumentTree tree, char* symbols, char** newLine);

MPIList getInstruments(char* line, char* symbols, InstrumentTree tree, int numOfInstruments, int* musiciansPerIns);

void resetMusucainsAvailabilityStatus(Musician** musicians, int numOfMusicians);

#endif // !MUSICIAN_H