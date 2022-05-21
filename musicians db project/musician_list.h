#ifndef MUSICIAN_LIST_H
#define MUSICIAN_LIST_H

#include "instrument_tree.h"

typedef struct listNode
{
	unsigned short insId; // instrument ID
	float price; // the price the musicians takes for this 
	struct listNode* next;
} MusicianPriceInstrument;

typedef struct
{
	MusicianPriceInstrument* head;
	MusicianPriceInstrument* tail;
}MPIList;


MusicianPriceInstrument* getListNode(MPIList* lst, int i);
MusicianPriceInstrument* createNewListNode(unsigned short id, float price, MusicianPriceInstrument* next);
bool isEmptyList(MPIList* lst);
void makeEmptyList(MPIList* lst);
void insertNodeToStartList(MPIList* lst, MusicianPriceInstrument* node);
void insertDataToStartList(MPIList* lst, unsigned short id, float price);
void printList(MPIList* lst);
void freeList(MPIList* lst);

#endif // !MUSICIAN_LIST_H