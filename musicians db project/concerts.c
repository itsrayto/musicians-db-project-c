#include "concerts.h"
#include "instrument_tree.h"


Concert* getConcertDetails(InstrumentTree tree, int* size)
{
	Concert* arrOfConcerts = (Concert*)malloc(sizeof(Concert));
	int physicalSize = 1, logicalSize = 0;
	bool endOfLineFound = false;

	while (!endOfLineFound)
	{
		if (logicalSize == physicalSize)
		{
			physicalSize *= 2;
			arrOfConcerts = realloc(arrOfConcerts, physicalSize * sizeof(Concert));
			checkMemoryAllocation(arrOfConcerts);
		}

		endOfLineFound = getConcertDetailsHelper(&arrOfConcerts[logicalSize], tree);

		if (!endOfLineFound)
			logicalSize++;
	}

	*size = logicalSize;
	return arrOfConcerts;
}


bool getConcertDetailsHelper(Concert* concert, InstrumentTree tree)
{
	Concert pConcert;
	Date date;
	char* concertDetails;
	int length, charsRead;
	float minutes;

	concertDetails = scanConcertDetailsToStr(&length);
	if (concertDetails == NULL)
		return true;

	sscanf(concertDetails, "%d%d%d%f:%f%n", &date.day, &date.month, &date.year, &date.hour, &minutes, &charsRead);
	date.hour += minutes / 60;
	pConcert.date_of_concert = date;

	makeEmptyCIList(&pConcert.instruments);

	while (charsRead < length)
		getInstrumentDetails(&pConcert, &charsRead, concertDetails, tree);

	*concert = pConcert;
	return false;
}


char* scanConcertDetailsToStr(int* lenght)
{
	int physicalSize = 2, logicalSize = 0;
	char current;
	char* str = (char*)malloc(2 * sizeof(char)), * res;

	checkMemoryAllocation(str);

	scanf("%c", &current);

	if (current == '\n')
		return NULL; //empty line

	while (current != '\n');
	{
		if (physicalSize == logicalSize)
		{
			str = realloc(str, physicalSize * 2);
			checkMemoryAllocation(str);
			physicalSize *= 2;
		}
		str[logicalSize] = current;
		logicalSize++;
		scanf("%c", &current);
	}
	res = _strdup(str);
	free(str);
	*lenght = (int)strlen(res);
	return res;
}


void getInstrumentDetails(Concert* concert, int* charsRead, char* concertDetails, InstrumentTree tree)
{
	Concert pConcert = *concert;
	char* instrumentName, tempInstName[MAX_LEN];
	int num, importance, insID, tempCharsRead, pCharsRead = *charsRead;


	sscanf(concertDetails + pCharsRead, "%s%n", tempInstName, &tempCharsRead);
	instrumentName = _strdup(tempInstName);
	pCharsRead += tempCharsRead;
	sscanf(concertDetails + pCharsRead, "%d%d%n", &num, &importance, &tempCharsRead);
	pCharsRead += tempCharsRead;

	insID = findInsId(tree, instrumentName);
	insertDataToEndCIList(&pConcert.instruments, importance, insID, num);

	*charsRead = pCharsRead;
	*concert = pConcert;
}
