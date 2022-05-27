#ifndef CONCERT_INSTRUMENTS_LIST_H
#define CONCERT_INSTRUMENTS_LIST_H

#include "instrument_tree.h"

typedef struct concertInstrument
{
	struct concertInstrument* next;
	int num;
	int inst;
	char importance;
} ConcertInstrument;

typedef struct ConcertInstrumentList
{
	ConcertInstrument* head;
	ConcertInstrument* tail;
} CIList;


ConcertInstrument* createNewCIListNode(char importance, int inst, int num, ConcertInstrument* next);

bool isEmptyCIList(CIList* lst);

void makeEmptyCIList(CIList* lst);

void insertDataToStartCIList(CIList* lst, char importance, int inst, int num);

void insertDataToEndCIList(CIList* lst, char importance, int inst, int num);

void insertNodeToStartCIList(CIList* lst, ConcertInstrument* node);

void insertNodeToEndList(CIList* lst, ConcertInstrument* tail);

#endif // !CONCERT_INSTRUMENTS_LIST_H