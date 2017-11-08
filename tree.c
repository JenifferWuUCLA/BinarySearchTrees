/*
 * tree.c -- tree support functions
 *
 *  Created on: Nov 7, 2017
 *      Author: jenifferwu
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/* local data type */
typedef struct pair {
	Trnode * parent;
	Trnode * child;
}Pair;

/* prototypes for local functions */
static Trnode * MakeNode(const Item * pi);
static bool ToLeft(const Item * i1, const Item * i2);
static bool ToRight(const Item * i1, const Item * i2);
static void AddNode(Trnode * new_node, Trnode * root);
static void InOrder(const Trnode * root, void (* pfun)(Item item));
static Pair SeekItem(const Item * pi, const Tree * ptree);
static void DeleteNode(Trnode **ptr);
static void DeleteAllNodes(Trnode * ptr);

/* function definitions */
void InititalizeTree(Tree * ptree)
{
	ptree->root = NULL;
	ptree->size = 0;
}

bool TreeIsEmpty(const Tree * ptree)
{
	if (ptree->root == NULL)
		return true;
	else
		return false;
}

bool TreeIsFull(const Tree * ptree)
{
	if (ptree->size == MAXITEMS)
		return true;
	else
		return false;
}

int TreeItemCount(const Tree * ptree)
{
	return ptree->size;
}

bool AddItem(const Item * pi, Tree * ptree)
{
	Trnode * new_node;

	if (TreeIsFull(ptree))
	{
		fprintf(stderr, "Tree is full\n");
		return false;  /* early return */
	}
	if (SeekItem(pi, ptree).child != NULL)
	{
		fprintf(stderr, "Attempted to add duplicate item\n");
		return false;  /* early return */
	}
	new_node = MakeNode(pi);  /* points to new node */
	if (new_node == NULL)
	{
		fprintf(stderr, "Couldn't create node\n");
		return false;  /* early return */
	}
	/* succeed in creating a new node */
	ptree->size++;

	if(ptree->root == NULL)    /* case 1: tree is empty */
		ptree->root = new_node;  /* new node is tree root */
	else
		AddNode(new_node, ptree->root);  /* add node to tree */

	return false;  /* successful return */
}
