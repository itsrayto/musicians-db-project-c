#include "instrument_tree.h"
#include "concerts.h"
#include "concert_instruments_list.h"
#include "musician.h"
#include "musician_list.h"
#include "utilities.h"

void main(int argc, char* argv[])
{
	FILE* instruments = fopen(argv[1], "r");
	InstrumentTree tree;
	ConcertsArray concerts;

	/* question 1 */
	checkFile(instruments);
	makeEmptyTree(&tree);

	buildInstrumentTree(&tree, instruments);
	fclose(instruments);

	/* question 5 */
	concerts.arrOfConcerts = getConcertDetails(tree, &concerts.size);
}