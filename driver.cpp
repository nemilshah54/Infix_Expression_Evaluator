#include "nshah213Proj5Token.h"

void printCommands();

void processExpression (Token inputToken, TokenReader *tr);

int DEBUG_MODE;

int main(int argc, char *argv[])
{
    /***************************************************************/
    /* Add code for checking command line arguments for debug mode */

     for (int i = 0; i<argc; i++)
	{
		if (argv[i][0] == '-'&&argv[i][1] == 'd')
		{
			DEBUG_MODE = TRUE;
		}

		else
		{
			DEBUG_MODE = FALSE;
		}

	}


    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr);
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  printf ("Quitting Program\n");
  return 0;
}

void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}


// PROCESS EXPRESSION FUNCTION. The entire algorithm to evaluate the expression resides here.
void processExpression(Token inputToken, TokenReader *tr)
{
	/**********************************************/
	/* Declare both stack head pointers here      */
	
	myClass oprStack;    // Stack containing stack of operators.
	myClass valStack;    // Stack containing stack of values.
	bool flag = true;   // Bool variable that helps to pass integer or character operators separately.

	int v1;         // First value for evaluation
	int v2;         // Second value for evaluation.
	int v3;         // Third value for evaluation.
	char op;        // Operation needed to evaluate v1 and v2.
	// int temp = 0;   // Error checking

	/* Loop until the expression reaches its End */
	while (inputToken.equalsType(EOLN) == false)  // While the current token is not the end of line token.
	{
		/* The expression contain a VALUE */
		if (inputToken.equalsType(VALUE))
		{
			/* make this a debugMode statement */
			if(DEBUG_MODE==TRUE)
			printf("Val: %d, ", inputToken.getValue());

			flag = true;
			valStack.push(inputToken.getValue(),flag);
			// add code to perform this operation here

		}

		/* The expression contains an OPERATOR */
		if (inputToken.equalsType(OPERATOR))
		{
			/*printf(" operator: %c ", inputToken.getOperator());
			if ((inputToken.getOperator() != '+') && (inputToken.getOperator() != '-') && (inputToken.getOperator() != '/') 
				&& (inputToken.getOperator() != '*') && (inputToken.getOperator() != '(') && (inputToken.getOperator() != ')'))
			{
				printf(" Invalid operation so expression can't be evalauted");
				temp = 1;
				break;
			}   */
			/* make this a debugMode statement */
			if (DEBUG_MODE == TRUE)
			printf("OP: %c, ", inputToken.getOperator());

			if (inputToken.getOperator() == '(')
			{
				flag = false;
				oprStack.push('(', flag);
			}

			if (inputToken.getOperator() == '+' || inputToken.getOperator() == '-')
			{
				while ((oprStack.isEmpty() != true) &&
					(oprStack.topOfStack() == '+' || oprStack.topOfStack() == '/' || oprStack.topOfStack() == '*' || oprStack.topOfStack() == '-'))
				{   
					// First popping the values and operator which are needed to be evaluate.
					op = oprStack.popOperator();
					if (DEBUG_MODE == TRUE)
					printf("\n\n STACK OPERATOR to be popped is: %c \n ", op );

					//valStack.popValue();

					v2 = valStack.topOfStack();
					if (DEBUG_MODE == TRUE)
					printf(" STACK VALUE V2 to be popped is: %d \n ", v2);   // Debug mode
					valStack.popValue();

					v1 = valStack.topOfStack();
					if (DEBUG_MODE == TRUE)
					printf(" STACK VALUE V1 to be popped is: %d \n", v1);    // Debug mode
					valStack.popValue();

					switch (op)
					{
					case '+':
						if (DEBUG_MODE == TRUE)
						printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
						v3 = v2 + v1;
						if (DEBUG_MODE == TRUE)
						printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
						flag = true;
						valStack.push(v3,flag);
						break;

					case '-':
						if (DEBUG_MODE == TRUE)
						printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
						v3 = v1 - v2;
						if (DEBUG_MODE == TRUE)
						printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
						flag = true;
						valStack.push(v3,flag);
						break;

					case '*':
						if (DEBUG_MODE == TRUE)
						printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
						v3 = v2*v1;
						if (DEBUG_MODE == TRUE)
						printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
						flag = true;
						valStack.push(v3,flag);
						break;

					case '/':
						if (DEBUG_MODE == TRUE)
						printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
						v3 = v1 / v2;
						if (DEBUG_MODE == TRUE)
						printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
						flag = true;
						valStack.push(v3, flag);
						break;

					}
				}

				flag = false;
				oprStack.push(inputToken.getOperator(),flag);

			}

			if (inputToken.getOperator() == '*' || inputToken.getOperator() == '/')
			{
				while ((oprStack.isEmpty() != true) &&
					(oprStack.topOfStack() == '*' || oprStack.topOfStack() == '/'))

				{
					// First popping the values and operator which are needed to be evaluate.
					op = oprStack.popOperator();
					if (DEBUG_MODE == TRUE)
						printf("\n\n STACK OPERATOR to be popped is: %c \n ", op);

					//valStack.popValue();

					v2 = valStack.topOfStack();
					if (DEBUG_MODE == TRUE)
						printf(" STACK VALUE V2 to be popped is: %d \n ", v2);   // Debug mode
					valStack.popValue();

					v1 = valStack.topOfStack();
					if (DEBUG_MODE == TRUE)
						printf(" STACK VALUE V1 to be popped is: %d \n", v1);    // Debug mode
					valStack.popValue();


					switch (op)
					{
					case '+':
						if (DEBUG_MODE == TRUE)
							printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
						v3 = v2 + v1;
						if (DEBUG_MODE == TRUE)
							printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
						flag = true;
						valStack.push(v3, flag);
						break;

					case '-':
						if (DEBUG_MODE == TRUE)
							printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
						v3 = v1 - v2;
						if (DEBUG_MODE == TRUE)
							printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
						flag = true;
						valStack.push(v3, flag);
						break;

					case '*':
						if (DEBUG_MODE == TRUE)
							printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
						v3 = v2*v1;
						if (DEBUG_MODE == TRUE)
							printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
						flag = true;
						valStack.push(v3, flag);
						break;

					case '/':
						if (DEBUG_MODE == TRUE)
							printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
						v3 = v1 / v2;
						if (DEBUG_MODE == TRUE)
							printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
						flag = true;
						valStack.push(v3, flag);
						break;


					}

				}
				flag = false;
				oprStack.push(inputToken.getOperator(),flag);
			}

			if (inputToken.getOperator() == ')')
			{
				while ((oprStack.isEmpty() != true) &&
					(oprStack.topOfStack() != '('))
				{
					// First popping the values and operator which are needed to be evaluate.
					op = oprStack.popOperator();
					if (DEBUG_MODE == TRUE)
						printf("\n\n STACK OPERATOR to be popped is: %c \n ", op);

					//valStack.popValue();

					v2 = valStack.topOfStack();
					if (DEBUG_MODE == TRUE)
						printf(" STACK VALUE V2 to be popped is: %d \n ", v2);   // Debug mode
					valStack.popValue();

					v1 = valStack.topOfStack();
					if (DEBUG_MODE == TRUE)
						printf(" STACK VALUE V1 to be popped is: %d \n", v1);    // Debug mode
					valStack.popValue();

					switch (op)
					{
					case '+':
						if (DEBUG_MODE == TRUE)
							printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
						v3 = v2 + v1;
						if (DEBUG_MODE == TRUE)
							printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
						flag = true;
						valStack.push(v3, flag);
						break;

					case '-':
						if (DEBUG_MODE == TRUE)
							printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
						v3 = v1 - v2;
						if (DEBUG_MODE == TRUE)
							printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
						flag = true;
						valStack.push(v3, flag);
						break;

					case '*':
						if (DEBUG_MODE == TRUE)
							printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
						v3 = v2*v1;
						if (DEBUG_MODE == TRUE)
							printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
						flag = true;
						valStack.push(v3, flag);
						break;

					case '/':
						if (DEBUG_MODE == TRUE)
							printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
						v3 = v1 / v2;
						if (DEBUG_MODE == TRUE)
							printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
						flag = true;
						valStack.push(v3, flag);
						break;

					}
				}

				if (oprStack.isEmpty() == true)
				{
					printf("Not a valid expression \n");
				}
				else
				{
					op=oprStack.popOperator();
					printf("\n\n STACK OPERATOR to be popped is: %c \n ", op);
				}

			}


		}
		// add code to perform this operation here

		/* get next token from input */
		inputToken = tr->getNextToken();
	}

	/* The expression has reached its end */

	// add code to perform this operation here


	while (oprStack.isEmpty() != true)
	{
		// First popping the values and operator which are needed to be evaluate.
		op = oprStack.popOperator();
		if (DEBUG_MODE == TRUE)
			printf("\n\n STACK OPERATOR to be popped is: %c \n ", op);

		//valStack.popValue();

		v2 = valStack.topOfStack();
		if (DEBUG_MODE == TRUE)
			printf(" STACK VALUE V2 to be popped is: %d \n ", v2);   // Debug mode
		valStack.popValue();

		v1 = valStack.topOfStack();
		if (DEBUG_MODE == TRUE)
			printf(" STACK VALUE V1 to be popped is: %d \n", v1);    // Debug mode
		valStack.popValue();

		switch (op)
		{
		case '+':
			if (DEBUG_MODE == TRUE)
				printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
			v3 = v2 + v1;
			if (DEBUG_MODE == TRUE)
				printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
			flag = true;
			valStack.push(v3, flag);
			break;

		case '-':
			if (DEBUG_MODE == TRUE)
				printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
			v3 = v1 - v2;
			if (DEBUG_MODE == TRUE)
				printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
			flag = true;
			valStack.push(v3, flag);
			break;

		case '*':
			if (DEBUG_MODE == TRUE)
				printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
			v3 = v2*v1;
			if (DEBUG_MODE == TRUE)
				printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
			flag = true;
			valStack.push(v3, flag);
			break;

		case '/':
			if (DEBUG_MODE == TRUE)
				printf(" Values that are to be evaluated: %d & %d \n", v2, v1);   // Debug mode
			v3 = v1 / v2;
			if (DEBUG_MODE == TRUE)
				printf("FINAL evaluation value to be pushed in value stack is %d \n\n ", v3);   // Debug mode
			flag = true;
			valStack.push(v3, flag);
			break;

		}


	}

	/*if (temp == 1)
	{
		printf(" Invalid input operator so the expression can't be evaluated.");
		//exit(0);
	}
	else 
	{
		//printf(" hello");
		 printf("\n FINAL EXPRESSION VALUE: %d", v3);
	}  */

	printf("\n FINAL EXPRESSION VALUE: %d", v3);

	// Making the stack empty so that it is ready to be used again.
	oprStack.makeEmpty();
	valStack.makeEmpty();
	
	
}
