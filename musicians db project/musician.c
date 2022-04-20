#include "musician.h"

// creates a two dimensional array, where each row is an array of all the musicians that play a specific instrument
Musician** createMusicianCollection(Musician* musicianGroup, int numOfMusicians, int numOfInstruments, int* musiciansPerIns)
{
	Musician** res;
	res = (Musician**)malloc(sizeof(Musician*) * numOfInstruments); // allocates memory for the musician collection
	checkMemoryAlloc(res);
	int* indArr = (int*)malloc(sizeof(int) * numOfInstruments); // keeps record of the index of the last added musician in a specific instrument array
	checkMemoryAlloc(indArr);
	
	for (int i = 0; i < numOfInstruments; i++) // allocates memory for each instrument array
	{
		res[i] = (Musician*)malloc(sizeof(Musician) * musiciansPerIns[i]);
		checkMemoryAlloc(res[i]);
		indArr[i] = 0;
	}

	for (int i = 0; i < numOfMusicians; i++) // fills the musician collection
	{
		MusicianPriceInstrument* curr = musicianGroup[i].instruments.head;
		while (curr != NULL) // add musician to all of the corresponding instrument arrays
		{
			int ind = curr->insId;
			res[ind][indArr[ind]] = musicianGroup[i];
			indArr[ind]++;
		}
	}
	return res;
}