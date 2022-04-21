#include "instrument_tree.h"

// searches the tree for the requested instrument and returns its ID
int findInsId(InstrumentTree tree, char* instrument)
{
	return findInsIdHelper(tree.root, instrument);
}

int findInsIdHelper(TreeNode* root, char* instrument)
{
	if (root == NULL) // if empty tree
		return -1;
	int side = strcmp(root->instrument, instrument);

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