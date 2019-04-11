#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<assert.h>

//#include "hashing.h"

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


int hash(char *string, int basenumber, int tablesize)
{
	//printf("Printing:  %ld\n",strlen(string));
	int sum=0;
	for(int i=0;i<strlen(string);i++)
	{
		sum= sum + string[i];
	}
	
	return (sum%basenumber) %tablesize;
}

int collision_count(char **string, int basenumber, int tablesize, int number)
{
	int arr[tablesize] ;
	
	for(int i=0;i<tablesize;i++)
		arr[i]=0;
		
	int collide=0;
	
	//printf("%s",string[0]);
	
	for(int i=0;i<number;i++)
	{
		//printf("%d\n",hash(string[i],basenumber,tablesize));
		if(arr[hash(string[i],basenumber,tablesize)]==1)
			collide++;
		else
			arr[hash(string[i],basenumber,tablesize)]=1;
	}
	
	return collide;
	
}

int check(char *string)
{
	int i=0;
	
	while(string[i]!='\0')
	{
		
		if(string[i]<65 || string[i]>122 || (string[i]>90 && string[i]<97))
			return 0;
		i++;
	}
	
	return 1;
}


char ** parsing()
{
	FILE *fp = fopen("aliceinwonderland.txt","r");
	assert(fp!=NULL);
	int count=0;
	
	char **book = malloc(sizeof(char*));
	
	int total=0;
	
	char *string;
	string = malloc(sizeof(char)*1000);
	
	while(fscanf(fp,"%s ",string)!=EOF)
	{
		//printf("Word detected: %s", string);
		//getchar();
		
		if(check(string)==1)
		{
			count++;
			book = realloc(book,count * sizeof(char*));
			book[count-1]=malloc(sizeof(char)*1000);
			strcpy(book[count-1],string);
		}
		
		total++;
		
	}
	
	
	
	fclose(fp);
	
	printf("The count of ascii words is %d \n and total words is %d\n\n",count,total);
	
	return book;
	
}

void profiling(char **book, int * tablesize, int * basenumber)
{
	int best1 = tablesize[0];
	int best2 = basenumber[1];
	
	for(int i=0;i<3;i++)
	{
		for(int j=i*3;j<(i+1)*3;j++)
		{
			
			printf("The basenumber :%d and tablesize :%d \n", basenumber[j],tablesize[i]);
			printf("The collision count is %d \n\n", collision_count(book,basenumber[j],tablesize[i],22698));
			
			
			if(collision_count(book,basenumber[j],tablesize[i],22698) < collision_count(book,best2,best1,22698))
			{
				best1 = tablesize[i];
				best2 = basenumber[j];
			}
			
		}
	}

	printf("Best tablesize is %d and basenumber is %d \n",best1,best2);
	
}



struct slot* createtable(int tablesize)
{
	struct slot* table = malloc(sizeof(struct slot)*tablesize);
	
	for(int i=0;i<tablesize;i++)
	{
		table[i].head=NULL;
		table[i].listcount=0;
	}
	
	insertioncost=0;
	querycost=0;
	elementcost=0;
	
	return table;
}


void insert(struct slot* table, char **book, int ind, int tablesize)
{
	if ( table[(hash(book[ind],6029,tablesize))].head==NULL)
	{
		struct node* record = malloc(sizeof(struct node));
		strcpy(record->string,book[ind]);
		record->count=1;
		record->index=ind;
		record->next=NULL;
		table[(hash(book[ind],6029,tablesize))].head = record;
		table[(hash(book[ind],6029,tablesize))].listcount=1;
		
	}
	
	else
	{
		struct node* temp = table[(hash(book[ind],6029,tablesize))].head;
	
		while(temp!=NULL)
		{
			if(strcmp(temp->string,book[ind])==0)
			{
				break;
			}			
			temp=temp->next;
		}
		
		if(temp==NULL)
		{
			struct node* record = malloc(sizeof(struct node));
			strcpy(record->string,book[ind]);
			record->count=1;
			record->index=ind;
			record->next=NULL;
			
			struct node* temp1 = table[(hash(book[ind],6029,tablesize))].head;
			
			while(temp1->next!=NULL)
				temp1=temp1->next;
			 
			temp1->next = record;
			
			
			insertioncost += table[(hash(book[ind],6029,tablesize))].listcount++;
								
		}
		
		else
		{
			temp->count++;			
		}
	}
}

void printtable(struct slot* table)
{
	
	
	for(int i=0;i<5000;i++)
	{
		struct node* runner = table[i].head;
		
		while(runner!=NULL)
		{
			printf("%s with count as %d and index is %d\n",runner->string,runner->count,runner->index);	
			
			runner=runner->next;
		}
	}
	
	
}

int insertall(char** book, struct slot* table)
{
	for(int i=0;i<22698;i++)
	{
		insert(table,book,i,5000);
	}
	
	return insertioncost;
}

struct node* lookup(struct slot* table, char *string)
{
	int jumps=0;
	struct node * runner = table[hash(string,6029,5000)].head;
	
	if(runner==NULL)
		return NULL;
	
	else
	while(runner!=NULL)
	{
		if(strcmp(runner->string,string)==0)
		{
			querycost+=jumps;
			return runner;		
			
		}
		runner=runner->next;
		jumps++;
	}
	
	querycost+=jumps;
	return runner;
}

int lookupall(struct slot* table,char** book, float m)
{
	
	querycost=0;
	int number = (int)(m*22698);
	//printf("Number is %d",number);
	
	
	for(int i=0;i<number;i++)
	{
		lookup(table,book[i]);
		//printf("%d ",querycost);
	}
	
	return querycost;
	
}



int main()
{	

	char ** book = parsing();
	
	// in this example all combo are giving same answer 
	// try changing the 5000 to 100 and observe the changes
	
	int tablesize[3] = {5000,50000,500000};
	int basenumber[9] = {6029,7307,8681,60089,74471,93967,590407,670343,914339};
	
	//profiling(book,tablesize,basenumber);	
	
	struct slot* table = createtable(5000);
	
	insertall(book,table);	
	
	printf("Insertion Cost is : %d \n",insertioncost);
	
	//printtable(table);
	
	//struct node* found = lookup(table,"question");
	//printf("%s\n",found->string);
	
	//printf("%d\n",querycost);
	
	printf("Query cost is %d\n", lookupall(table,book,0.42));
	
}
