#ifndef INSTRUMENT_TREE_H
#define INSTRUMENT_TREE_H

typedef struct treeNode {
	char* instrument; // name of instrument
	unsigned short insId; // instrument ID
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree {
	TreeNode* root;
} InstrumentTree;

int findInsId(InstrumentTree tree, char* instrument);

#endif // !INSTRUMENT_TREE_H