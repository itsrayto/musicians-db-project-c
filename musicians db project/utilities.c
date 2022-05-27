#include "instrument_tree.h"
#include "musician.h"
#include "utilities.h"

/* checkimg if memory allocation has succeeded */
void checkMemoryAllocation(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(1);
	}
}

/* checkimg if file opening has succeeded */
void checkFile(FILE* file)
{
	if (file == NULL)
	{
		printf("Couldn't open file!\n");
		exit(1);
	}
}

/* returns the size of a given file */
long int fileSize(FILE* fp)
{
	long int res;
	long int saver = ftell(fp);

	fseek(fp, 0, SEEK_END);
	res = ftell(fp);
	fseek(fp, saver, SEEK_SET);
	return res;
}

/* frees all memory allocation */
void ourFree(InstrumentTree tree, Musician** musicianGroup, int numOfMusicians, int* musiciansPerIns, Musician*** musicianCollection, int numOfIns)
{
	freeTree(tree.root);
	freeMusicianGroup(musicianGroup, numOfMusicians);
	freeMusicianCollection(musicianCollection, numOfIns);
	free(musiciansPerIns);
}

/* free all memory allocations of an InstrumentsTree */
void freeTree(TreeNode* root)
{
	if (root == NULL)
		return;

	freeTree(root->left);
	freeTree(root->right);
	free(root->instrument);
	free(root);
}

/* free all memory allocations of the "musiciansGroup array */
void freeMusicianGroup(Musician** musicianGroup, int numOfMusicians)
{
	for (int i = 0; i < numOfMusicians; i++)
	{
		MusicianPriceInstrument* current = musicianGroup[i]->instruments.head, * nextSaver;
		int j = 0;		
		while (musicianGroup[i]->name[j] != NULL)
			free(musicianGroup[i]->name[j++]);
		free(musicianGroup[i]->name);

		while (current != NULL)
		{
			nextSaver = current->next;
			free(current);
			current = nextSaver;
		}
		free(musicianGroup[i]);
	}

	free(musicianGroup);
}

/* free all memory allocations of the musicianCollection array */
void freeMusicianCollection(Musician*** musicianCollection, int numOfIns)
{
	for (int i = 0; i < numOfIns; i++)
		free(musicianCollection[i]);
	free(musicianCollection);
}