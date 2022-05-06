#ifndef MUSICIAN_H
#define MUSICIAN_H

#include "musician_list.h"
#include "instrument_tree.h"

typedef struct
{
	char** name; // arr of musicians full name
	MPIList instruments; // list of the instruments the musicians plays
} Musician;

Musician*** createMusicianCollection(Musician* musicianGroup, int numOfMusicians, int numOfInstruments, int* musiciansPerIns, int** indArray);

#endif // !MUSICIAN_H