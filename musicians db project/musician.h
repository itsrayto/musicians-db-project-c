#ifndef MUSICIAN_H
#define MUSICIAN_H

#include "musician_list.h"

typedef struct
{
	char** name; // arr of musicians full name
	MPIList instruments; // list of the instruments the musicians plays
} Musician;

#endif // !MUSICIAN_H