#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<assert.h>

struct leaf{
	
	char* string;

};


struct node{

	char* string;
	struct node ** child;
	int numc;
	struct leaf* ad; 

};


char ** splitdomain(char *str)
{
	char ** arr = malloc(sizeof(char*) * 1);
	arr[0] = malloc(sizeof(char)*50);  
   char* token = strtok(str, "."); 
  
	int count =1;  
   
   while (token != NULL) 
   { 
       arr = realloc(arr,sizeof(char*)*count);
       arr[count-1] = malloc(sizeof(char)*50);
       //printf("%s\n", token);
       strcpy(arr[count-1],token);
       token = strtok(NULL, "."); 
       count++;
   } 
	
	return arr;
	
}

int hostlen(char* str)
{
	 //printf("String received %s",str);
	 
	 char* token = strtok(str, "."); 
	 int count=0;
	 while (token != NULL) 
   { 
       //printf("%s\n", token);
       token = strtok(NULL, "."); 
       count++;
   } 
   
   return count;
}

struct node* createDNS()
{
	struct node* db = malloc(sizeof(struct node));
	db->string = NULL;
	db->child = NULL;
	db->ad=NULL;
	db->numc=0;
	return db;
}

struct node* find(struct node** child, int numc ,char * str)
{
	if(child==NULL || str==NULL)
		return NULL;
	
	for(int i=0;i<numc;i++)
	{	
		if(strcmp(child[i]->string,str)==0)
			return child[i];
	}
	
	return NULL;
	
	
}

struct node* insert(struct node* db, char* str, char *ip)
{
	char* a = malloc(sizeof(char)*50);
	strcpy(a,str);
	char** split = splitdomain(str);
	int len = hostlen(a);
	
	//printf("len is %d\n",len);
	//for(int j=0;j<len;j++)
		//printf("split[%d] is %s\n",j,split[j]); 
	//getchar();
	
	
	struct node* runner = db;
	
	for(int i=len-1;i>=0;i--)
	{
		
		struct node* st = runner;
		runner = find(runner->child,runner->numc,split[i]);
		
		//printf("i is %d\n",i); getchar();
		
		if(runner==NULL)
		{
			for(;i>=0;i--)
			{
				struct node* temp = malloc(sizeof(struct node));
				
				//printf("i is %d",i); 
				//getchar();
				
				temp->string = malloc(sizeof(char)*50);
				strcpy(temp->string,split[i]);
				temp->numc=0;
				temp->child = NULL;
				temp->ad=NULL;
				//getchar();
				
				//printf("%d\n",st->numc);
				st->child = realloc(st->child,sizeof(struct node*) * st->numc+1);
				st->numc++;
				st->child[(st->numc)-1] = temp;
				
				if(i==0)
				{
					struct leaf* temp2 = malloc(sizeof(struct leaf));
					temp2->string = malloc(sizeof(char)*50);
					strcpy(temp2->string,ip);
					//printf("%s\n",temp2->string);
					temp->ad = temp2;
				}
				
				st = temp;
								
			}
			
			return db;
		}
		
		else
		{
			if(i==0 && runner->ad==NULL)
			{
				struct leaf* temp2 = malloc(sizeof(struct leaf));
				temp2->string = malloc(sizeof(char)*50);
				strcpy(temp2->string,ip);
				//printf("%s\n",temp2->string);
				runner->ad = temp2;
				return db;
			}
			
			if(i==0 && runner->ad!=NULL)
			{
				printf("\nALREADY INSERTED\n");
				return db;
			}	
		}
	}

}

void lookup(struct node* db,char *str)
{

	struct node* runner = db;
	
	char* a = malloc(sizeof(char)*50);
	strcpy(a,str);
	char** split = splitdomain(str);
	int len = hostlen(a);
	
	char *path = malloc(sizeof(char)*20);
	
	for(int i=len-1;i>=0;i--)
	{
		struct node* st = runner;
		runner = find(runner->child,runner->numc,split[i]);
		
		if(runner==NULL)
		{
			printf("%s\n",path);
			return;
		}
		
		else
		{
			int j=0;
			
			while(st->child[j]!=runner)
				j++;
			
			char c = 48+j;
			char *source = malloc(sizeof(char)*3);
			source[0]=' ';
			source[1]=c;
			source[3]='\0';
		
			strcat(path,source);
			
			if(i==0)
			{
				printf("IP is %s\n",runner->ad->string);
				return;
			}
			
			
		}
	}	

}


struct node* readData()
{
	struct node* db = createDNS();
	
	FILE* fp = fopen("Data","r");
	assert(fp!=NULL);
	
	int option;
	fscanf(fp,"%d",&option);
	//getchar();
	
	while(option!=(-1))
	{
		if(option==1)
		{
			int num;
			fscanf(fp,"%d\n",&num);
			
			for(int i=0;i<num;i++)
			{
				char *str1 = malloc(sizeof(char)*50);
				char *str2 = malloc(sizeof(char)*50);
				
				fscanf(fp,"%s %s\n",str1,str2);
				//printf("%s %s\n",str1,str2);
				db = insert(db,str1,str2);
				
			}
		
		}
		
		if(option==2)
		{
			char *str = malloc(sizeof(char)* 50);
			fscanf(fp,"%s\n",str);
			//printf("%s\n",str);
			
			lookup(db,str);
			
		}
	
		fscanf(fp,"%d",&option);
	}
	
	return db;
}



int main()
{
	
		
	//char * str1 = malloc(sizeof(char)*50);
	//strcpy(str1,"swd.pilani.ac.in");
	
	//char * str2 = malloc(sizeof(char)*50);
	//strcpy(str2,"172.12.17.26");
	
	//struct node* db = createDNS();
	
	struct node* db = readData();
	
	//db = insert(db,str1,str2);

	
	//char * str3 = malloc(sizeof(char)*50);
	//strcpy(str3,"bits.pilani.ac.in");
	
	//db = insert(db,str3,str2);
	
	//struct node* root = db;
	//int i=0;
	
	//while(root->child!=NULL)
	//{
		//root = root->child[0];
		//printf("Inside % d: %s and numc %d \n",i,root->string,root->numc);
		//i++;
	//}
	
	//printf("%s\n",root->ad->string);
	
	//char * str = malloc(sizeof(char)*50);
	//strcpy(str,"bits.pilani.ac.in");
	//printf("%d\n",hostlen(str));
	
}

