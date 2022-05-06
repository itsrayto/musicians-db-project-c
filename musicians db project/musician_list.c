#include "musician_list.h"
#include "instrument_tree.h"

MusicianPriceInstrument* getListNode(MPIList* lst, int i)
{
	MusicianPriceInstrument* res = lst->head;
	int ind = 0;

	if (i < 0)
		return NULL;

	while (res != NULL || ind < i)
	{
		res = res->next;
		ind++;
	}

	if (ind == i)
		return res;
	else
		return NULL;
}

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

bool isEmptyList(MPIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

void makeEmptyList(MPIList* lst)
{
	lst->head = lst->tail = NULL;
}

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

void insertDataToStartList(MPIList* lst, unsigned short id, float price)
{
	MusicianPriceInstrument* newNode = createNewListNode(id, price, NULL);
	insertNodeToStartList(lst, newNode);
}

void printList(MPIList* lst)
{
	MusicianPriceInstrument* curr;
	curr = lst->head;

	while (curr != NULL)
	{
		printf("instrument ID: %u, price: %.1f\n", curr->insId, curr->price);
		curr = curr->next;
	}
}

void freeList(MPIList* lst)
{
	MusicianPriceInstrument* curr;
	curr = lst->head;

	while (curr != NULL)
	{
		MusicianPriceInstrument* tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	free(lst);
}