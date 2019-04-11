#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


struct node{

	int value;
	struct node* left;
	struct node* right;
	int height:2;

};



int height(struct node* tree);
void heightupdate(struct node* tree);
struct node * add(int key,struct node* tree);
void inorder(struct node* tree);
struct node* createBST(int key);
struct node* parent(struct node*tree, int key);
struct node* find(struct node* tree,int key);
struct node* successor(struct node* tree, int key);
struct node* delete(struct node* tree, int key);
int k_smallest(struct node* tree, int k);
void rangesearch(struct node* tree, int k1, int k2);
struct node* rotate(struct node* tree, struct node* x, struct node* y, struct node* z);



int height(struct node* tree)
{
	
	if(tree==NULL)
		return (-1);
	
	if( height(tree->right) > height(tree->left) )
		return height(tree->right) +1;
		
	return height(tree->left) +1;

}

void heightupdate(struct node* tree)
{
	if(tree==NULL)
		return;
	
	if(height(tree->right)<height(tree->left))
		tree->height=(-1);
	if(height(tree->right)>height(tree->left))
		tree->height=(1);
	if(height(tree->right)==height(tree->left))
		tree->height=(0);
		
	heightupdate(tree->right);
	heightupdate(tree->left);
	
	
}

struct node* pointofimbalance(struct node* tree, struct node* record)
{
	struct node* runner = record;
	
	while(runner!=NULL)
	{
		if(height(runner->left)-height(runner->right)>1 || height(runner->left)-height(runner->right)<(-1))
		{
			return runner;
		}
		
		runner=parent(tree,runner->value);
	}
	
	return runner;
}


struct node * add(int key,struct node* tree)
{
	struct node* temp = malloc(sizeof(struct node));
	temp->value=key;
	temp->left=NULL;
	temp->right=NULL;
	temp->height=0;
	
	if(tree==NULL)
	{
		tree=temp;
		return tree;
	}
	
	struct node* runner = tree;
	
	while(runner!=NULL)
	{
		if(runner->value<key)
		{
			if(runner->right==NULL)
			{
				runner->right=temp;
				heightupdate(tree);
				
				
				if(pointofimbalance(tree,temp)!=NULL)
				{
					
					//printf("POIMB: %d\n",pointofimbalance(tree,temp)->value);
					struct node* x = pointofimbalance(tree,temp);
					struct node* y;
					
					if(x->value<key)
					{
						y = x->right;
					}
					if(x->value>key)
					{
						y = x->left;
					}
					
					struct node* z;
					
					if(y->value<key)
					{
						z = y->right;
					}
					if(y->value>key)
					{
						z = y->left;
					}
					
					tree = rotate(tree, x,y,z);
					
					
				}
				
				
				
				return tree;
			}
			runner=runner->right;
		}
		
		if(runner->value>key)
		{
			if(runner->left==NULL)
			{
				runner->left=temp;
				heightupdate(tree);
				
				
				if(pointofimbalance(tree,temp)!=NULL)
				{
					
					//printf("POIMB: %d\n",pointofimbalance(tree,temp)->value);
					struct node* x = pointofimbalance(tree,temp);
					struct node* y;
					
					if(x->value<key)
					{
						y = x->right;
					}
					if(x->value>key)
					{
						y = x->left;
					}
					
					struct node* z;
					
					if(y->value<key)
					{
						z = y->right;
					}
					if(y->value>key)
					{
						z = y->left;
					}
					
					tree = rotate(tree, x,y,z);
					
					
				}
				
				
				
				return tree;
			}
			runner=runner->left;
		}
	}
}

void inorder(struct node* tree)
{
	if(tree==NULL)
		return;
	
	if(tree->left==NULL && tree->right==NULL)
	{
		printf("%d\n",tree->value);
		return;
	}
	
	inorder(tree->left);
	printf("%d\n",tree->value);
	inorder(tree->right);
}

struct node* createBST(int key)
{
	struct node* tree = malloc(sizeof(struct node));
	tree->value=key;
	tree->left=NULL;
	tree->right=NULL;
	tree->height=0;
	return tree;
}



struct node* parent(struct node*tree, int key)
{
	if(tree->value==key)
		return NULL;
	
	if(tree==NULL)
		return NULL;
	
	struct node* runner =tree;
	
	struct node* prev = tree;
	
	while(runner!=NULL && runner->value!=key)
	{
		
		if(runner->value<key)
		{
			prev = runner;
			runner=runner->right;
		}
			
		else if(runner->value>key)
		{
			prev=runner;
			runner=runner->left;
		}
		
	}
	
	if(runner==NULL)
		return NULL;
	
	return prev;
}

struct node* find(struct node* tree,int key)
{
	struct node* runner= tree;
	while(runner!=NULL)
	{
		if(runner->value==key)
		{
			//printf("Found the number in the tree");
			return runner;
		}
			
		if(runner->value>key)
			runner=runner->left;
		if(runner->value<key)
			runner=runner->right;
	}
	
	if(runner==NULL)
	{
		printf("Sorry the element is not present\n");
			return NULL;
		
	}
}

struct node* successor(struct node* tree, int key)
{
	if(tree==NULL)
		return NULL;
	
	struct node* temp = find(tree,key);
	
	if(temp->right!=NULL)
	{
		struct node* runner = temp->right;
		//printf("Runner starts at :%d \n",runner->value);
		
		while(runner->left!=NULL)
		{
			runner=runner->left;
		}
		
		
		return runner;
	}
	
	struct node* p = parent(tree, key);
	
	if(p->left==temp)
	{
		return p;
	}
	
	if(p->right==temp)
	{
		
		while(p->left!=temp && p!=NULL && temp==p->right)
		{
			temp=p;
			p=parent(tree,temp->value);
		}
		
		return p;
		
	}
	
}

struct node* delete(struct node* tree, int key)
{
	if(tree==NULL)
		return NULL;
	
	if(tree->value==key && tree->left==NULL && tree->right==NULL)
	{
		free(tree);
		return NULL;
	}
	
	if(tree->value==key && tree->right==NULL && tree->left!=NULL)
	{
		tree=tree->left;
		heightupdate(tree);
		return tree;
	}	
	
	if(tree->value==key && tree->right!=NULL && tree->left==NULL)
	{
		tree=tree->right;
		heightupdate(tree);
		return tree;
	}
	
	
	struct node* t = find(tree,key);
	struct node* p = parent(tree,key);
	
	if(t->right==NULL)
	{
		if(p->right==t)
		{
			p->right=t->left;
			free(t);
		}
		
		else 
		if(p->left==t)
		{
			p->left=t->left;
			free(t);
		}
		
		heightupdate(tree);
		
		while(p!=NULL)
		{
				
			struct node* gp = parent(tree,p->value);
			
			if(pointofimbalance(tree,p)!=NULL)
			{
				
				//printf("POIMB: %d\n",pointofimbalance(tree,p)->value);
				struct node* x = pointofimbalance(tree,p);
				struct node* y;
				
				if(height(x->left)>height(x->right))
					y=x->left;
				if(height(x->left)<height(x->right))
					y=x->right;
				
				struct node* z;
				
				if(height(y->left)>height(y->right))
					z=y->left;
				if(height(y->left)<height(y->right))
					z=y->right;
					
				tree = rotate(tree, x,y,z);
				
				
			}
			
			p=gp;
		
		}
		
		return tree;
		
	}
	
	if(t->left==NULL)
	{
		if(p->right==t)
		{
			p->right=t->right;
			free(t);
		}
		
		if(p->left==t)
		{
			p->left=t->right;
			free(t);
		}
		
		heightupdate(tree);
		
		while(p!=NULL)
		{
				
			struct node* gp = parent(tree,p->value);
			
			if(pointofimbalance(tree,p)!=NULL)
			{
				
				//printf("POIMB: %d\n",pointofimbalance(tree,p)->value);
				struct node* x = pointofimbalance(tree,p);
				struct node* y;
				
				if(height(x->left)>height(x->right))
					y=x->left;
				if(height(x->left)<height(x->right))
					y=x->right;
				
				struct node* z;
				
				if(height(y->left)>height(y->right))
					z=y->left;
				if(height(y->left)<height(y->right))
					z=y->right;
				
				tree = rotate(tree, x,y,z);
				
				
			}
			
			p=gp;
		
		}
	
		
		return tree;
		
	}
	
	
	//what if none of the children are NULL?
	
	struct node* succ = successor(tree,key);
	
	int store = succ->value;
	tree = delete(tree,store);
	t->value=store;	
	
	heightupdate(tree);
	return tree;
	
	
}

int k_smallest(struct node* tree, int k)
{
	struct node* lowest = tree;
	
	while(lowest->left!=NULL)
	{
		lowest=lowest->left;
	}
	
	struct node* answer = lowest;
	
	for(int i=0;i<k-1;i++)
	{
		answer = successor(tree, answer->value);
	}
	
	return answer->value;
}


void rangesearch(struct node* tree, int k1, int k2)
{
	
	if(tree==NULL)
		return ;
		
	if(tree->value<k1)
		rangesearch(tree->left, k1, k2);
		
	if(tree->value>k2)
		rangesearch(tree->right, k1, k2);

	
	if(tree->value<=k2 && tree->value>=k1)
		printf("%d ",tree->value);
	
	rangesearch(tree->left,k1,tree->value);
	rangesearch(tree->right,tree->value,k2);	
	
}


struct node* rotate(struct node* tree, struct node* x, struct node* y, struct node* z)
{
	
	
	if(x->left==y && y->left==z)
	{
		struct node* xp = parent(tree,x->value);
		x->left=y->right;
		y->right=x;
		
		if(xp==NULL)
		{
			tree=y;
			return tree;
		}
		
		if(xp->right==x)
			xp->right=y;
			
		if(xp->left==x)
			xp->left=y;
			
		return tree;
		
	}
	
	if(x->left==y && y->right==z)
	{
		struct node* xp = parent(tree,x->value);
		x->left=z;
		y->right=z->left;
		z->left=y;
		
		x->left=z->right;
		z->right=x;
		
		if(xp==NULL)
		{
			tree=z;
			return tree;
		}
		
		if(xp->right==x)
			xp->right=z;
			
		if(xp->left==x)
			xp->left=z;
			
		return tree;
		
		
	}
	
	if(x->right==y && y->right==z)
	{
		struct node* xp = parent(tree,x->value);
		x->right=y->left;
		y->left=x;
		
		if(xp==NULL)
		{
			tree=y;
			return tree;
		}
		
		if(xp->right==x)
			xp->right=y;
			
		if(xp->left==x)
			xp->left=y;
			
		return tree;

	}
	
	if(x->right==y && y->left==z)
	{
		
		struct node* xp = parent(tree,x->value);
		x->right=z;
		y->left= z->right;
		z->right=y;
		
		x->right=z->left;
		z->left=x;
		
		if(xp==NULL)
		{
			tree=z;
			return tree;
		}
		
		if(xp->right==x)
			xp->right=z;
			
		if(xp->left==x)
			xp->left=z;
			
		return tree;
	}
	
}


int main()
{
	struct node* tree = createBST(3);
	//printf("Root is %d\n",tree->value);
	tree = add(1,tree);
	//printf("Root is %d\n",tree->value);
	tree = add(6,tree);
	//printf("Root is %d\n",tree->value);
	tree = add(10,tree);
	//printf("Root is %d\n",tree->value);
	tree = add(8,tree);
	//printf("Root is %d\n",tree->value);
	tree = add(5,tree);
	//printf("Root is %d\n",tree->value);
	tree = add(7,tree);
	//printf("Root is %d\n",tree->value);
	tree = add(4,tree);
	
	//struct node* temp = find(tree,7);
	//printf("Found: %d\n",temp->value);
	
	inorder(tree);	
	
	//tree= delete(tree,7);
	//inorder(tree);
	//tree= delete(tree,10);
	//inorder(tree);	
	
	//struct node* temp = parent(tree,4);
	//printf("Parent is %d\n",temp->value);
	
	//struct node* temp = successor(tree,3);
	//printf("Successor is %d\n",temp->value);
	
	//printf("Kth smallest %d\n",k_smallest(tree,8));
	
	//rangesearch(tree,3,7);
	
	
}
