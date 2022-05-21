#ifndef INSTRUMENT_TREE_H
#define INSTRUMENT_TREE_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 151
#define SYMBOLS 21

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

int findInsIdHelper(TreeNode* root, char* instrument);

void makeEmptyTree(InstrumentTree* tree);

void Insert(InstrumentTree* pt, char* instrument, short int insID_counter);

TreeNode* FindPlace(TreeNode* currentNode, char* instrument);

bool isEmptyTree(InstrumentTree t);

int buildInstrumentTree(InstrumentTree* tree, FILE* instruments);

long int fileSize(FILE* fp);

void checkFile(FILE* file);

void checkMemoryAllocation(void* ptr);

#endif // !INSTRUMENT_TREE_H