#include "instrument_tree.h"

/* searches the tree for the requested instrument and returns its ID */ 
int findInsId(InstrumentTree tree, char* instrument)
{
	int res = findInsIdHelper(tree.root, instrument);
	if (res == -1)
		return res;
	else
		return (unsigned short)res;
}


int findInsIdHelper(TreeNode* root, char* instrument)
{
	int side;

	if (root == NULL) // if empty tree
		return -1;

	side = strcmp(root->instrument, instrument);

	if (side == 0) // if the root is with the requested instrument
		return root->insId;
	else if (side < 0) // if the root ins is smaller (alphabetical order) than requested ins, search right sub tree
	{
		return findInsIdHelper(root->right, instrument);
	}
	else // side > 0 ,if the root ins is bigger (alphabetical order) than requested ins, search left sub tree
	{
		return findInsIdHelper(root->left, instrument);
	}
	return -1;
}

/* initializes a tree to be empty */
void makeEmptyTree(InstrumentTree* tree)
{
	tree->root = NULL;
}

/* Insert instrument into its proper place */
void Insert(InstrumentTree* pt, char* instrument, unsigned short insID_counter)
{
	TreeNode* father;
	TreeNode* new_instrument;


	new_instrument = (TreeNode*)malloc(sizeof(TreeNode));
	checkMemoryAllocation(new_instrument);
	new_instrument->instrument = _strdup(instrument);
	new_instrument->left = NULL;
	new_instrument->right = NULL;
	new_instrument->insId = insID_counter;

	if (isEmptyTree(*pt))
		pt->root = new_instrument;
	else
	{
		father = FindPlace(pt->root, instrument);
		if (strcmp(instrument, father->instrument) < 0)
			father->left = new_instrument;
		else
			father->right = new_instrument;
	}
}

/* Returning the parent of the new instrument needed to be inserted */
TreeNode* FindPlace(TreeNode* currentNode, char* instrument)
{
	if (strcmp(instrument, currentNode->instrument) < 0)
	{
		if (currentNode->left == NULL)
			return currentNode;
		else
			return FindPlace(currentNode->left, instrument);
	}
	else
	{
		if (currentNode->right == NULL)
			return currentNode;
		else
			return FindPlace(currentNode->right, instrument);
	}
}

/* Checking if the tree is empty */
bool isEmptyTree(InstrumentTree t)
{
	return (t.root == NULL);
}

/* builds an binary search tree of instruments based on a given file */
int buildInstrumentTree(InstrumentTree* tree, FILE* instruments)
{
	char str[MAX_LEN];
	unsigned short insID_counter = 0;
	long int fSize = fileSize(instruments);

	fscanf(instruments, "%s", str);

	while (ftell(instruments) < fSize)
	{
		Insert(tree, str, insID_counter);
		fscanf(instruments, "%s", str);
		insID_counter++;
	}
	Insert(tree, str, insID_counter++);

	fclose(instruments);
	return insID_counter;
}

/* this function searches the tree for the requested insID and returns its name */
char* reverseFindInsId(InstrumentTree tree, unsigned short insId)
{
	return reversFindInsIdHelper(tree.root, insId);
}


char* reversFindInsIdHelper(TreeNode* root, unsigned short insId)
{
	int side;
	char* leftIns, * rightIns;

	if (root == NULL) // if empty tree
		return NULL;

	if (root->insId == insId)
		return root->instrument;
	leftIns = reversFindInsIdHelper(root->left, insId);
	if (leftIns != NULL)
		return leftIns;
	rightIns = reversFindInsIdHelper(root->right, insId);
	return rightIns;
}