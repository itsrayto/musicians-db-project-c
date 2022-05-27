#include "instrument_tree.h"
#include "concerts.h"
#include "musician.h"

/* this function scans and creates a concert if possible, if not it prints a message about its failure */
void manageConcerts(InstrumentTree tree, int* musiciansPerIns, Musician*** collection, Musician** musicians, int numOfMusicians)
{
	Concert concert;
	bool endOfInputFound = false, validConcert;
	int totalMusicians; //total amount of musicians for a specific concert

	while (!endOfInputFound)
	{
		totalMusicians = 0;
		endOfInputFound = getConcertDetails(&concert, tree, &totalMusicians);
		if (!endOfInputFound)
		{
			validConcert = createConcert(&concert, collection, musiciansPerIns, totalMusicians);
			resetMusucainsAvailabilityStatus(musicians, numOfMusicians);
			printConcert(&concert, validConcert, totalMusicians, tree);
			printf("\n");
		}
		if (!endOfInputFound)
			freeConcert(&concert);
	}
}

/* this function scans the details of a concert from the user */
bool getConcertDetails(Concert* concert, InstrumentTree tree, int* totalMusicians)
{
	Concert pConcert;
	Date date;
	char* concertDetails;
	int length, charsRead, tempCharsRead;
	float minutes;

	pConcert.name = NULL;
	pConcert.musiciansForConcert = NULL;
	concertDetails = scanConcertDetailsToStr(&length);
	if (concertDetails == NULL)
		return true;

	pConcert.name = getConcertName(concertDetails, &charsRead);
	sscanf(concertDetails + charsRead, "%d%d%d%f:%f%n", &date.day, &date.month, &date.year, &date.hour, &minutes, &tempCharsRead);
	charsRead += tempCharsRead;
	date.hour += minutes / 60;
	pConcert.date_of_concert = date;

	makeEmptyCIList(&pConcert.instruments);

	while (charsRead < length)
		getInstrumentDetails(&pConcert, &charsRead, concertDetails, tree, totalMusicians);


	free(concertDetails);
	*concert = pConcert;
	return false;
}

/* this function scans the details of a concert into a string */
char* scanConcertDetailsToStr(int* lenght)
{
	int physicalSize = 2, logicalSize = 0;
	char current;
	char* str = (char*)malloc(2 * sizeof(char));

	checkMemoryAllocation(str);

	scanf("%c", &current);

	if (current == '\n')
	{
		free(str);
		return NULL; //empty line
	}

	while (current != '\n')
	{
		if (physicalSize == logicalSize)
		{
			physicalSize *= 2;
			str = realloc(str, physicalSize);
			checkMemoryAllocation(str);
		}
		str[logicalSize++] = current;
		scanf("%c", &current);
	}
	str = realloc(str, (logicalSize + 1));
	str[logicalSize] = '\0';
	*lenght = logicalSize;
	return str;
}

/* this function scans the concert's name from a string with its details */
char* getConcertName(char* name, int* charsRead)
{
	char* res, current;
	int pCharsRead = 0;

	sscanf(name, "%c", &current);
	pCharsRead++;

	while (current != ' ')
	{
		pCharsRead++;
		sscanf(name + pCharsRead, "%c", &current);
	}

	res = (char*)malloc(pCharsRead + 1 * sizeof(char));
	checkMemoryAllocation(res);

	for (int i = 0; i < pCharsRead; i++)
		res[i] = name[i];
	
	res[pCharsRead] = '\0';

	*charsRead = pCharsRead;
	return res;
}

/* this function scans the instruments requirements for a specific concert from a string with its details */
void getInstrumentDetails(Concert* concert, int* charsRead, char* concertDetails, InstrumentTree tree, int* totalMusicians)
{
	Concert pConcert = *concert;
	char* instrumentName, tempInstName[MAX_LEN];
	int num, importance, tempCharsRead, pCharsRead = *charsRead;
	unsigned short insID;

	sscanf(concertDetails + pCharsRead, "%s%n", tempInstName, &tempCharsRead);
	instrumentName = _strdup(tempInstName);
	pCharsRead += tempCharsRead;
	sscanf(concertDetails + pCharsRead, "%d%d%n", &num, &importance, &tempCharsRead);
	pCharsRead += tempCharsRead;

	insID = findInsId(tree, instrumentName);
	insertDataToEndCIList(&pConcert.instruments, importance, insID, num);

	free(instrumentName);
	*totalMusicians += num;
	*charsRead = pCharsRead;
	*concert = pConcert;
}

/* this function creates a concert based on the requirements of the user. if no such oncert is possile it returns "false" */
bool createConcert(Concert* concert, Musician*** collection, int* musiciansPerIns, int totalMusicians)
{
	Concert pConcert = *concert;
	concertMusician *musicians;
	ConcertInstrument* current = pConcert.instruments.head;
	bool validConcert = true;
	int resIndex = 0;
	unsigned short insId;
	
	pConcert.musiciansForConcert = (Musician**)malloc(sizeof(Musician*) * totalMusicians);
	checkMemoryAllocation(pConcert.musiciansForConcert);

	while (current != NULL)
	{
		int foundMusicianCounter = 0;
		insId = current->inst;
		musicians = createMusiciansForConcert(collection[insId], insId, musiciansPerIns[insId], current->importance);
		qsort(musicians, musiciansPerIns[insId], sizeof(concertMusician), comparePrices); // sorting the array by price

		for (int i = 0; i < musiciansPerIns[insId] && foundMusicianCounter < current->num; i++)
		{
			if (!musicians[i].musician->taken)
			{
				pConcert.musiciansForConcert[resIndex++] = musicians[i].musician;
				musicians[i].musician->taken = true;
				foundMusicianCounter++;
			}
		}

		if (foundMusicianCounter != current->num)
		{
			validConcert = false;
			current = NULL;
		}
		else
			current = current->next;		
		free(musicians);
	}	
	*concert = pConcert;
	return validConcert;
}

/* this function compares the prices of two musicians for the same instrument */
int comparePrices(concertMusician* a, concertMusician* b)
{
	unsigned short insIdA = a->insId, insIdB = b->insId;
	float priceA, priceB, res;
	MusicianPriceInstrument* current = a->musician->instruments.head;

	while (current != NULL)
	{
		if (current->insId == insIdA)
			priceA = current->price;

		current = current->next;
	}

	current = b->musician->instruments.head;
	while (current != NULL)
	{
		if (current->insId == insIdB)
			priceB = current->price;

		current = current->next;
	}

	res = priceA - priceB;
	if (a->importance == 1)
		return (int)res * -1;
	else
		return (int)res;
}

/* this function fills an array of concertMusician with different Musician* and with the same insId and importance to be sent into qsort */
concertMusician* createMusiciansForConcert(Musician** arr, unsigned short insId, int size, char importance)
{
	concertMusician* musicians = (concertMusician*)malloc(sizeof(concertMusician) * size);

	checkMemoryAllocation(musicians);

	for (int i = 0; i < size; i++)
	{
		musicians[i].insId = insId;
		musicians[i].musician = arr[i];
		musicians[i].importance = importance;
	}
	return musicians;
}

/* this function prints a given concert. if the said concert couldn't be created it prints a special message */
void printConcert(Concert* concert, bool valid, int size, InstrumentTree tree)
{
	float minutes = concert->date_of_concert.hour - (int)concert->date_of_concert.hour;
	int	totalPrice = 0, musiciansTakenPerIns = 0, currentPrice = 0;
	char* instrument = NULL;
	ConcertInstrument* current = concert->instruments.head;

	if (valid)
	{		
		printf("%s %02d %02d %d %02d:", concert->name, concert->date_of_concert.day, concert->date_of_concert.month, concert->date_of_concert.year, (int)concert->date_of_concert.hour);
		printf("%02d: ", (int)(minutes * 60));

		for (int i = 0; i < size; i++)
		{
			MusicianPriceInstrument* prices = concert->musiciansForConcert[i]->instruments.head;
			int j = 0;
			while (concert->musiciansForConcert[i]->name[j] != NULL)
				printf("%s ", concert->musiciansForConcert[i]->name[j++]);
			musiciansTakenPerIns++;
			
			instrument = findInsNameAndPrice(tree, prices, current, &currentPrice);			
			if (i < size-1)
				printf("- %s (%d), ", instrument, currentPrice);
			else 
				printf("- %s (%d). ", instrument, currentPrice);
			totalPrice += currentPrice;
			if (musiciansTakenPerIns == current->num)
			{
				musiciansTakenPerIns = 0;
				current = current->next;
			}
		}
		printf("Total cost: %d.\n", totalPrice);
	}
	else
		printf("Could not find musicians for the concert %s\n", concert->name);
}

/* this function returns the current insId and the price of a specific musician on that instrument */
char* findInsNameAndPrice(InstrumentTree tree, MusicianPriceInstrument* prices, ConcertInstrument* current, int* price)
{
	bool foundIns = false;
	int pPrice = 0;
	char* instrument = NULL;

	instrument = reverseFindInsId(tree, current->inst);

	while (!foundIns)
	{
		if (prices->insId == current->inst)
		{
			foundIns = true;
			pPrice = (int)prices->price;
		}
		prices = prices->next;
	}

	*price = pPrice;
	return instrument;
}

/* this function frees all memoery allocation within a concert */
void freeConcert(Concert* concert)
{
	ConcertInstrument* current = concert->instruments.head, * nextSaver = NULL;
	
	free(concert->name);

	while (current != NULL)
	{
		nextSaver = current->next;
		free(current);
		current = nextSaver;
	}

	free(concert->musiciansForConcert);
}