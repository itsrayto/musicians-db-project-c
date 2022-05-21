#include "musician.h"
#include "instrument_tree.h"


Musician* createMusicainGroup(FILE* data, InstrumentTree tree, int numOfInstruments, int** musiciansPerIns, int* size)
{
	Musician* res = (Musician*)malloc(sizeof(Musician));
	char line[MAX_LEN], symbols[SYMBOLS] = " ,.;:?!-\t'()[]{}<>~_";
	long int fSize = fileSize(data);
	int physicalSize = 1, logicalSize = 0;
	int* pMusiciansPerIns = (int*)malloc(numOfInstruments * sizeof(int));

	for (int i = 0; i < numOfInstruments; i++)
		pMusiciansPerIns[i] = 0;

	while (ftell(data) < fSize)
	{
		char* newLine;

		fgets(line, (MAX_LEN - 1) * sizeof(char), data);

		res = memoryAllocations(res, &physicalSize, logicalSize);
		res[logicalSize].name = getNames(line, logicalSize, tree, symbols, &newLine);
		res[logicalSize].instruments = getInstruments(newLine, symbols, tree, numOfInstruments, pMusiciansPerIns);
		
		logicalSize++;
	}
	*musiciansPerIns = pMusiciansPerIns;
	*size = logicalSize;
}



Musician* memoryAllocations(Musician* arr, int* physicalSize, int logicalSize)
{
	int pPhysicalSize = *physicalSize;

	if (pPhysicalSize == logicalSize)
	{
		pPhysicalSize *= 2;
		arr = (Musician*)realloc(arr, pPhysicalSize * sizeof(Musician));
		checkMemoryAllocation(arr);
	}

	arr[logicalSize].name = (char**)malloc(sizeof(char*) * 2); //minimum of 2 words in a Musician's name
	checkMemoryAllocation(arr[logicalSize].name);

	*physicalSize = pPhysicalSize;
	return arr;
}


char** getNames(char* line, int index, InstrumentTree tree, char* symbols, char** newLine)
{
	int physicalSize = 2, logicalSize = 0;
	char** res = (char**)malloc(2 * sizeof(char*)), * current;
	bool firstInsFound = false;

	current = strtok(line, symbols);
	/* physical and logical for res!! */

	while (current != NULL && !firstInsFound)
	{
		if (findInsId(tree, current) == -1) //the current string is not an instrument, therefore it's a name
		{
			if (physicalSize == logicalSize)
			{
				physicalSize *= 2;
				res = (char**)realloc(res, physicalSize * sizeof(char*));
				checkMemoryAllocation(res);
			}
			res[logicalSize++] = _strdup(current);
			current = strtok(NULL, symbols);
		}
		else
			firstInsFound = true;
	}

	res = (char**)realloc(res, (logicalSize + 1) * sizeof(char*));
	checkMemoryAllocation(res);
	res[logicalSize] = NULL; //an index for later purposes

	*newLine = current;
	*(current + strlen(current)) = '('; // one of the tokens strtok can work with
	return res;
}


MPIList getInstruments(char* line, char* symbols, InstrumentTree tree, int numOfInstruments, int* musiciansPerIns)
{
	MPIList list;
	unsigned short int insID; 
	float price;
	char* current;

	makeEmptyList(&list);
	current = strtok(line, symbols);

	while (current != NULL)
	{
		if (*current != '\n')
		{
			insID = findInsId(tree, current);
			current = strtok(NULL, symbols);
			sscanf(current, "%f", &price);
			insertDataToStartList(&list, insID, price);
			current = strtok(NULL, symbols);
			musiciansPerIns[insID]++;
		}
		else
			current = NULL;
	}
	return list;
}

// creates a two dimensional array, where each row is an array of all the musicians that play a specific instrument
Musician*** createMusicianCollection(Musician* musicianGroup, int numOfMusicians, int numOfInstruments, int* musiciansPerIns, int* indArray)
{
	Musician*** res;
	res = (Musician***)malloc(sizeof(Musician**) * numOfInstruments); // allocates memory for the musician collection
	checkMemoryAllocation(res);
	int* indArr = (int*)malloc(sizeof(int) * numOfInstruments); // keeps record of the index of the last added musician in a specific instrument array
	checkMemoryAllocation(indArr);
	
	for (int i = 0; i < numOfInstruments; i++) // allocates memory for each instrument array
	{
		res[i] = (Musician**)malloc(sizeof(Musician*) * musiciansPerIns[i]);
		checkMemoryAllocation(res[i]);
		indArr[i] = 0;
	}

	for (int i = 0; i < numOfMusicians; i++) // fills the musician collection
	{
		MusicianPriceInstrument* curr = musicianGroup[i].instruments.head;
		while (curr != NULL) // add musician to all of the corresponding instrument arrays
		{
			int ind = curr->insId;
			res[ind][indArr[ind]] = &musicianGroup[i];
			indArr[ind]++;
		}
	}
	return res;
}