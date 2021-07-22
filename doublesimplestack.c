//implementation of the stack data structure FOR DOUBLES
//unlike what the name may imply, the complexity of handling both stacks should be the same
//this relies on a series of linked nodes, and a pointer to the top
#include "doublesimplestack.h"

//given a reference to a pointer to the top, and a double, inserts a node and makes input pointer point to the top of the stack
void DS_Push(double newData, DStackNode **top)
{
	DStackNode *newNode = (DStackNode*)malloc( sizeof(DStackNode) );
	if(newNode == NULL)
	{
		printf("unable to allocate memory\n");
		return;
	}

	//strcpy(newNode->data, newData);
	newNode->data = newData;

	if(*top == NULL)
	{
		//printf("creating new stack...\n");
		newNode->below = NULL;
		*top = newNode;
	}
	else
	{
		//printf("pushing new node on top of stack...\n");
		newNode->below = *top;
		*top = newNode;
	}
}

//given a reference to a pointer to the top, deletes the topmost node and points the pointer to the immediate successor to the late pointer
//who knew switching some variables would save me from a hack involving a memory leak (:
void DS_Pop(DStackNode **top)
{
	DStackNode *temp = *top;
	*top = temp->below;
	free(temp);
}

//given a pointer to the top, returns a double
//or one could hack it and use it to return the the pointers data
double DS_Top(DStackNode *top)
{
	return top->data;
}

//given a pointer to the top, prints the entire stack
void DS_PrintStack(DStackNode *top)
{
	DStackNode *node = NULL;
	node = top;
	while(node != NULL)
	{
		printf("%lf ", node->data);
		node = node->below;
	}
	printf("\n");
}

/*main function for testing purposes only
//also shows usage
int main()
{
	DStackNode *top = NULL;
	double e = 4.52;

	DS_Push(e, &top);
	DS_PrintStack(top);

	DS_Push(3.14, &top);
	DS_PrintStack(top);

	DS_Push(2.153, &top);
	DS_PrintStack(top);

	DS_Push(1.1, &top);
	DS_PrintStack(top);

	DS_Pop(&top);

	double f = DS_Top(top);
	printf( "value of topmost node: %lf\n", f );

	DS_PrintStack(top);

	/*example of nondestructive iteration
	StackNode *node = NULL;
	node = top;
	while(node != NULL)
	{
		//do stuff with data
		node = node->below;
	}
	
	return 0;
}*/
