//implementation of the stack data structure FOR STRINGS
//this relies on a series of linked nodes, and a pointer to the top
#include "charsimplestack.h"

//given a reference to a pointer to the top, and pointer to char, inserts a node and makes input pointer point to the top of the stack
//warning: if used in a function, make sure that the function arguement is a pointer to pointer, or else it is known to break
void S_Push(char *newData, CStackNode **top)
{
	CStackNode *newNode = (CStackNode*)malloc( sizeof(CStackNode) );
	if(newNode == NULL)
	{
		printf("Error from S_Push(): Unable to allocate memory\n");
		return;
	}

	strcpy(newNode->data, newData);
	//newNode->data = newData;

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
void S_Pop(CStackNode **top)
{
	CStackNode *temp = *top;
	*top = temp->below;
	free(temp);
}

//given a pointer to the top, returns a pointer to the start of the char array
//or one could hack it and use it to return the the pointers data
char* S_Top(CStackNode *top)
{
	return top->data;
}

//given a pointer to the top, prints the entire stack
void S_PrintStack(CStackNode *top)
{
	CStackNode *node = NULL;
	node = top;
	while(node != NULL)
	{
		printf("%s ", node->data);
		node = node->below;
	}
	printf("\n");
}

//prints debug info of the whole stack
//(oviously doesnt print jack shit if the node is null)
void S_PrintStackDebug(CStackNode *top)
{
	CStackNode *node = NULL;
	int i = 0;

	node = top;

	while(node != NULL)
	{
		printf("debug info for node %d\n", i);
		printf("address of current node: %p\n", (void*)node);
		printf("contains: %s\n", node->data);
		
		if(node != NULL)
		{
			printf("address of next node: %p\n\n", (void*)(node->below) );
			node = node->below;
		}
		i++;
	}
	printf("\n");
}

void S_NodeDebugInfo(CStackNode *node)
{
	printf("address of current node: %p\n", (void*)node);
	printf("contains: %s\n", node->data);
	printf("address of next node: %p\n\n", (void*)(node->below) );
}

//given a pointer to original node and pointer to pointer to the reversed node,
//reverses the order of the stack given pointer to node via destructive transfer
void S_Reverse(CStackNode *original, CStackNode **reversed)
{
	while(original != NULL)
	{
		char *tempData = S_Top(original);	
		
		//printf("data being inserted: %s\n", tempData);

		S_Push(tempData, reversed);
		S_Pop(&original);
	}
	
	//S_PrintStackDebug(*reversed);
	return;
}

/*main function for testing purposes only
//also shows usage
int main()
{
	CStackNode *top = NULL;
	char a[] = "PLS";

	S_Push(a, &top);
	S_PrintStack(top);

	S_Push("ME", &top);
	S_PrintStack(top);

	S_Push("HELP", &top);
	S_PrintStack(top);

	S_Push("AAAAA", &top);
	S_PrintStack(top);

	//S_Pop(&top);

	char *e = S_Top(top);
	printf( "value of topmost node: %s\n", e );

	//S_Push("1", &top);
	//S_Push("2", &top);
	//S_Push("3", &top);
	//S_Push("4", &top);

	printf("before reversing:\n"); S_PrintStackDebug(top);

	CStackNode *reversed = NULL;
	S_Reverse(top, &reversed);
	printf("\n\n");

	//if(reversed == NULL) { printf("warning: reversed is null\n"); }

	printf("after reversing:\n"); S_PrintStackDebug(reversed);

	//example of nondestructive iteration
	//CStackNode *node = NULL;
	//node = top;
	//while(node != NULL)
	//{
	//	//do stuff with data
	//	node = node->below;
	//}

	
	return 0;
}*/
