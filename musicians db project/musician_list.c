#include "instrument_tree.h"
#include "musician_list.h"

/* this function creates a new MPIListNode */
MusicianPriceInstrument* createNewListNode(unsigned short id, float price, MusicianPriceInstrument* next)
{
	MusicianPriceInstrument* res;
	res = (MusicianPriceInstrument*)malloc(sizeof(MusicianPriceInstrument));
	checkMemoryAllocation(res);
	res->insId = id;
	res->price = price;
	res->next = next;
	return res;
}

/* this function check whether an MPIList is empty */
bool isEmptyList(MPIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

/* this function makes a given MPIList empty */
void makeEmptyList(MPIList* lst)
{
	lst->head = lst->tail = NULL;
}

/* this function inserts a given MPIListNode to the start of an MPIList */
void insertNodeToStartList(MPIList* lst, MusicianPriceInstrument* node)
{
	if(isEmptyList(lst))
	{
		lst->head = lst->tail = node;
		node->next = NULL;
	}
	else
	{
		node->next = lst->head;
		lst->head = node;
	}

}

/* this function inserts data to the start of an MPIList */
void insertDataToStartList(MPIList* lst, unsigned short id, float price)
{
	MusicianPriceInstrument* newNode = createNewListNode(id, price, NULL);
	insertNodeToStartList(lst, newNode);
}