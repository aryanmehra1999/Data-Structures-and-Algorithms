#include<stdio.h>
#include<stdlib.h>

int hash(char *string, int basenumber, int tablesize);
int collision_count(char **string, int basenumber, int tablesize, int number);
int check(char *string);
void profiling(char **book, int * tablesize, int * basenumber);
char ** parsing();


int insertioncost;
int querycost;
int elementcost;

struct node {
	char string[1000];
	int count;
	int index;
	struct node* next;
};

struct slot{
	
	struct node* head;
	int listcount;
	
};
