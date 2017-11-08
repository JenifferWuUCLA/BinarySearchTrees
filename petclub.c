/*
 * petclub.c -- use a binary search tree
 *
 *  Created on: Nov 8, 2017
 *      Author: jenifferwu
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

char menu(void);
void addpet(Tree * pt);
void droppet(Tree * pt);
void showpets(const Tree * pt);
void findpet(const Tree * pt);
void printitem(Item item);
void uppercase(char * str);
char * s_gets(char * st, int n);

int main(void)
{
	Tree pets;
	char choice;

	InitializeTree(&pets);
	while((choice = menu()) != 'q')
	{
		switch(choice)
		{
			case 'a':  addpet(&pets);
				break;
			case 'l':  showpets(&pets);
				break;
			case 'f':  findpet(&pets);
				break;
			case 'n':  printf("%d pets in club\n", TreeItemCount(&pets));
				break;
			case 'd':  droppet(&pets);
				break;
			default:
				puts("Switching error");
		}
	}
	DeleteAll(&pets);
	puts("Bye.");

	return 0;
}

char menu(void)
{
	int ch;

	puts("Nerfville Pet Club Membership Program");
	puts("Enter the letter corresponding to your choice: ");
	puts("a) add a pet		l)  show list of pets");
	puts("n) number of pets		f)  find pets");
	puts("d) delete a pet		q)  quit");
	while ((ch = getchar()) != EOF)
	{
		while (getchar() != '\n')  /* discard rest of line */
			continue;
		ch = tolower(ch);
		if (strchr("alfndq", ch) == NULL)
			puts("Please enter an a, l, f, n, d, or q:");
		else
			break;
	}
	if (ch == EOF)    /* make EOF cause program to quit */
		ch = 'q';

	return ch;
}

void addpet(Tree * pt)
{
	Item temp;

	if (TreeIsFull(pt))
		puts("No room in the club!");
	else
	{
		puts("Please enter name of pet:");
		s_gets(temp.petname, SLEN);
		puts("Please enter pet kind:");
		s_gets(temp.petkind, SLEN);
		uppercase(temp.petname);
		uppercase(temp.petkind);
		AddItem(&temp, pt);
	}
}
