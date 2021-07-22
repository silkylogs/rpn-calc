#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef SIMPLESTACK_H
#define SIMPLESTACK_H

#define MAXDIGITS 100

typedef struct CStackNode
{
	char data[MAXDIGITS];
	struct CStackNode *below;
} CStackNode;

void S_Push(char *newData, CStackNode **top);
void S_Pop(CStackNode **top);
char* S_Top(CStackNode *top);
void S_PrintStack(CStackNode *top);
void S_PrintStackDebug(CStackNode *top);
void S_NodeDebugInfo(CStackNode *node);
void S_Reverse(CStackNode *original, CStackNode **reversed);

#endif
