//a program which evaluates equations in RPN (reverse polish notation)
//also includes a function to convert postfix notation to reverse polish notation (in a stacked format)
#include <stdio.h>
#include <math.h>
#include "rpnutils.h"
#define MAXSTRLEN 200

//returns 1 if string is a number (also accepts the decimal point)
int IsNumber(char *str)
{
	while(*str != '\0')
	{
		if( isdigit(*str) != 0 || *str == '.')
		{
			str++;
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

double Operator(char* op, double num1, double num2)
{
	if(strcmp(op, "+") == 0)
	{
		//printf("+ detected\n");
		return num1 + num2;
	}
	else if(strcmp(op, "-") == 0)
	{
		//printf("- detected\n");
		return num1 - num2;
	}
	else if(strcmp(op, "*") == 0)
	{
		//printf("* detected\n");
		return num1 * num2;
	}
	else if(strcmp(op, "/") == 0)
	{
		//printf("/ detected\n");
		return num1 / num2;
	}
	else if(strcmp(op, "^") == 0)
	{
		//printf("^ detected\n");
		//this will cause incorrect results if power inputs are flipped
		return pow(num2, num1);
	}
	else
	{
		printf("Error - unrecognized symbol %s detected in Operator()\n", op);
	}
}

//nondestructively evaluates a stack expression
double RpnEval(CStackNode *exprHead)
{
	CStackNode *ptr = exprHead;//traversing the original list
	DStackNode *numStack = NULL;//buffer
	double num1;
	double num2;

	while(ptr != NULL)
	{
		printf("Testing data in RpnEval(): %s\n", ptr->data);

		//ah, yes, elif ladders
		if(IsNumber(ptr->data) == 1)
		{
			printf("number detected\n");
			DS_Push(atof(ptr->data), &numStack);
		}
		else if(IsNumber(ptr->data) == 0)
		{
			printf("non number detected\n");
			//https://isaaccomputerscience.org/concepts/dsa_toc_rpn

			num1 = DS_Top(numStack);
			DS_Pop(&numStack);

			num2 = DS_Top(numStack);
			DS_Pop(&numStack);

			DS_Push(Operator(ptr->data, num1, num2), &numStack);
		}
		else
		{
			printf("Error - unrecognized symbol detected in RpnEval()\n");
			return 0.0;
		}
		printf("value(s) in numStack: "); DS_PrintStack( (DStackNode*)numStack );
		ptr = ptr->below;
	}

	return DS_Top(numStack);
}

//fuck it, i rewrote this shit from scratch
//given a pointer to a char string, and a pointer to pointer to the outstack, returns the reverse polish notation equivalent of said string
//for this algorithim to work, seperate tokens with spaces and always remember to USE THE FUCKING BRACKETS
void StringExprToRpn(char* exprStringp, CStackNode **outStack)
{
	//converting from a single string pointer to an array of string pointers for each token
	//why? see above
	int stringLength = strlen(exprStringp);
	char c[stringLength];
	char *exprStringArrp[stringLength];
	char *tempStrp = exprStringp;
	for(int i = 0; i < stringLength; i++)
	{
		c[i] = *tempStrp;
		tempStrp++;
	}
	char *token = strtok(c, " ");
	int tokenCount = 0;
	while(token != NULL && tokenCount < stringLength)
	{
		exprStringArrp[tokenCount++] = token;
		token = strtok(NULL, " ");
	}

	/*
	shunting yard algorithim, simplified:

	for all the elements in the array
		if element is a number, push it to outstack
		if element is a operand or a '(', push it to opstack
		if element is a ')', push the topmost element in outstack to opstack, then pop opstack (if opstack is not null)
		else show a syntax error

	return outstack
	*/

	//doing actual assignment
	CStackNode *opStack = NULL;
	for(int i = 0; i < tokenCount; i++)
	{
		char tempC = *exprStringArrp[i];
		//printf("index %d, testing character: %c\n", i, tempC);
		//todo: find out why inserting a "Y- Yamate kudasai, Onii-Chan~!" breaks this function
		//update: because there is a self imposed character cap, dumbass :betterthan:

		if(isdigit(tempC) || (tempC == '.') )
		{
			S_Push(&tempC, outStack);
		}
		else if (
			(tempC == '+') || 
			(tempC == '-') || 
			(tempC == '*') || 
			(tempC == '-') || 
			(tempC == '^') || 
			(tempC == '(') 
			)
		{
			S_Push(&tempC, &opStack);
		}
		else if(tempC == ')')
		{
			S_Push( S_Top(opStack), outStack );
			S_Pop(&opStack);
			if(opStack != NULL) { S_Pop(&opStack); }
		}
		else
		{
			printf("possible syntax error at character index %d\n", i);
		}

		/*debug
		printf("contents of outStack: "); S_PrintStack(*outStack);
		printf("contents of opStack: "); S_PrintStack(opStack);
		printf("\n");*/
	}
	//bonus case if there are extra symbols left in the opStack
	if(opStack != NULL)
	{
		//printf("Warning: extra signs still in opStack, transferring...\n");
		S_Reverse(opStack, outStack);//S_Reverse() also acts as a destructive transfer function
	}
	
	//this needs to be reversed because the RPNEval() function requires the output of this function to be reversed
	CStackNode *trueOut = NULL;
	S_Reverse(*outStack, &trueOut);
	//S_PrintStackDebug(trueOut);
	*outStack = trueOut;
	return;
}

/*
int main()
{
	//example of expression: 7 8 3 2 ^ * 4 + + [7+(8×(3^2)+4)] = 83
	CStackNode *exprHead = NULL;

	
	S_Push("+", &exprHead);//	^
	S_Push("+", &exprHead);//	|
	S_Push("4", &exprHead);//	|
	S_Push("*", &exprHead);//	|
	S_Push("^", &exprHead);//	|
	S_Push("2", &exprHead);//	|
	S_Push("3", &exprHead);//	|
	S_Push("8", &exprHead);//	|
	S_Push("7", &exprHead);//	|	reads down to up
	//S_PrintStack(exprHead);
	

	//uncommenting everything is a bad idea; in other words free the exprHead before reusing
	//StringExprToRpn("7 + ( ( 8 * ( 3 ^ 2 ) ) + 4 ) )", &exprHead);//passes
	//StringExprToRpn("1 + 1", &exprHead);//passes

	//this will not pass if you put the brackets around only numbers
	StringExprToRpn("( 3 ^ ( 2 * 6 ) ) + ( 4 * 6 ) - 4", &exprHead);

	//printf("RPN expression: "); S_PrintStack(exprHead);

	printf( "result of expression: %lf\n", RpnEval(exprHead) );

	return 0;
}*/
