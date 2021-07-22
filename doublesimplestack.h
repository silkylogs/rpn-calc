#include <stdio.h>
#include <stdlib.h>

#ifndef DSIMPLESTACK_H
#define DSIMPLESTACK_H

typedef struct DStackNode
{
	double data;
	struct DStackNode *below;
} DStackNode;

void DS_Push(double newData, DStackNode **top);
void DS_Pop(DStackNode **top);
double DS_Top(DStackNode *top);
void DS_PrintStack(DStackNode *top);

#endif