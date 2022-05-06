#include "instrument_tree.h"
#include "concert_instruments_list.h"
#include "utilities.h"


ConcertInstrument* createNewCIListNode(char importance, int inst, int num, ConcertInstrument* next)
{
	ConcertInstrument* res;
	res = (ConcertInstrument*)malloc(sizeof(ConcertInstrument));
	checkMemoryAllocation(res);
	res->next = next;
	res->importance = importance;
	res->inst = inst;
	res->num = num;
	return res;
}


bool isEmptyCIList(CIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}


void makeEmptyCIList(CIList* lst)
{
	lst->head = lst->tail = NULL;
}


void insertNodeToStartCIList(CIList* lst, ConcertInstrument* node)
{
	if (isEmptyCIList(lst))
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


void insertDataToStartCIList(CIList* lst, char importance, int inst, int num)
{
	ConcertInstrument* newNode = createNewCIListNode(importance, inst, num, NULL);
	insertNodeToStartCIList(lst, newNode);
}


void insertDataToEndCIList(CIList* lst, char importance, int inst, int num)
{
	ConcertInstrument* newTail;
	newTail = createNewCIListNode(importance, inst, num, NULL);
	insertNodeToEndList(lst, newTail);
}


void insertNodeToEndList(CIList* lst, ConcertInstrument* tail)
{
	if (isEmptyCIList(lst) == true)
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}


void freeCIList(CIList* lst) /* adjust to CIList */
{
	ConcertInstrument* curr;
	curr = lst->head;

	while (curr != NULL)
	{
		ConcertInstrument* tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	free(lst);
}