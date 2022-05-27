#include "concert_instruments_list.h"
#include "instrument_tree.h"
#include "musician_list.h"
#include "utilities.h"
#include "concerts.h"
#include "musician.h"

void main(int argc, char* argv[])
{
	FILE* instruments = fopen(argv[1], "r"), * Musicians = fopen(argv[2], "r");
	InstrumentTree tree;
	int numOfMusicians, numOfIns;
	Musician** musicianGroup; 
	int* musiciansPerIns;
	Musician*** musicianCollection;

	checkFile(instruments);
	checkFile(Musicians);

	makeEmptyTree(&tree);
	numOfIns = buildInstrumentTree(&tree, instruments);

	musicianGroup = createMusicainGroup(Musicians, tree, numOfIns, &musiciansPerIns, &numOfMusicians);

	musicianCollection = createMusicianCollection(musicianGroup, numOfMusicians, numOfIns, musiciansPerIns);

	manageConcerts(tree, musiciansPerIns, musicianCollection, musicianGroup, numOfMusicians);

	ourFree(tree, musicianGroup, numOfMusicians, musiciansPerIns, musicianCollection, numOfIns);
}
