#ifndef CONCERTS_H
#define CONCERTS_H

#include "instrument_tree.h"
#include "musician.h"
#include "concert_instruments_list.h"
#include "musician_list.h"

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
	Musician** musiciansForConcert;
} Concert;


void manageConcerts(InstrumentTree tree, int* musiciansPerIns, Musician*** collection, Musician** musicians, int numOfMusicians);

bool getConcertDetails(Concert* concert, InstrumentTree tree, int* totalMusicians);

char* getConcertName(char* name, int* charsRead);

char* scanConcertDetailsToStr(int* lenght);

void getInstrumentDetails(Concert* concert, int* charsRead, char* concertDetails, InstrumentTree tree, int* totalMusicians);

bool createConcert(Concert* concert, Musician*** collection, int* musiciansPerIns, int totalMusicians);

concertMusician* createMusiciansForConcert(Musician** arr, unsigned short insId, int size, char importance);

int comparePrices(concertMusician* a, concertMusician* b);

void printConcert(Concert* concert, bool valid, int size, InstrumentTree tree);

char* findInsNameAndPrice(InstrumentTree tree, MusicianPriceInstrument* prices, ConcertInstrument* current, int* price);

void freeConcert(Concert* concert);

#endif // !CONCERTS_H