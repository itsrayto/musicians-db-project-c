#include "instrument_tree.h"
#include "concert_instruments_list.h"

/* this function creates a new CIListNode */
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

/* this function checks if a CIList is an empty List */
bool isEmptyCIList(CIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

/* this function make an empty CIList */
void makeEmptyCIList(CIList* lst)
{
	lst->head = lst->tail = NULL;
}

/* this function inserts an existing node to the beginning of a CIList */
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

/* this function inserts data to the beginning of a CIList */
void insertDataToStartCIList(CIList* lst, char importance, int inst, int num)
{
	ConcertInstrument* newNode = createNewCIListNode(importance, inst, num, NULL);
	insertNodeToStartCIList(lst, newNode);
}

/* this function inserts data to the end of a CIList */
void insertDataToEndCIList(CIList* lst, char importance, int inst, int num)
{
	ConcertInstrument* newTail;
	newTail = createNewCIListNode(importance, inst, num, NULL);
	insertNodeToEndList(lst, newTail);
}

/* this function inserts an existing node to the end of a CIList */
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