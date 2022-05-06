#ifndef CONCERTS_H
#define CONCERTS_H

#include "instrument_tree.h"
#include "concert_instruments_list.h"

typedef struct
{
	int day, month, year;
	float hour;
} Date;

typedef struct
{
	Date date_of_concert;
	char* name;
	CIList instruments;
} Concert;

typedef struct
{
	Concert* arrOfConcerts;
	int size;
} ConcertsArray;


Concert* getConcertDetails(InstrumentTree tree, int* size);

bool getConcertDetailsHelper(Concert* concert, InstrumentTree tree);

char* scanConcertDetailsToStr(int* lenght);

void getInstrumentDetails(Concert* concert, int* charsRead, char* concertDetails, InstrumentTree tree);

#endif // !CONCERTS_H