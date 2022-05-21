#include "instrument_tree.h"
#include "concerts.h"
#include "concert_instruments_list.h"
#include "musician.h"
#include "musician_list.h"
#include "utilities.h"

void main(int argc, char* argv[])
{
	FILE* instruments = fopen(argv[1], "r"), * Musicians = fopen(argv[2], "r");
	InstrumentTree tree;
	ConcertsArray concerts;
	int numOfMusicians, numOfIns;
	Musician* musicianGroup; //question 3
	int* musiciansPerIns; 
	int* indArray; 
	Musician*** musicianCollection;


	checkFile(instruments);
	checkFile(Musicians);

	/* question 1 */
	makeEmptyTree(&tree);

	numOfIns = buildInstrumentTree(&tree, instruments); //add numOfIns
	fclose(instruments);

	/* question 3 */
	musicianGroup = createMusicainGroup(Musicians, tree, numOfIns, &musiciansPerIns, &numOfMusicians);
	/* need to free memory allocations inside */



	/* question 4 */
	indArray = (int*)malloc(sizeof(int) * numOfIns);
	checkMemoryAllocation(indArray);
	musicianCollection = createMusicianCollection(musicianGroup, numOfMusicians, numOfIns, musiciansPerIns, indArray);


	/* question 5 */
	/*concerts.arrOfConcerts = getConcertDetails(tree, &concerts.size);*/
	/* add stuff for 5 */
}
