/* This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 * Date: 10/21/17
 *
 * Author: Pat Troy
 *
 */

/**************************************************************/
/*                                                            */
/*  The Code below this point should NOT need to be modified  */
/*  for this program.   If you feel you must modify the code  */
/*  below this point, you are probably trying to solve a      */
/*  more difficult problem that you are being asked to solve  */
/*                                                            */
/**************************************************************/


#include "nshah213Proj5Token.h"




  Token::Token()
  {
    type = ERROR;
    op = '$';
    val = -999;
  }

  // Initialize to a specific TokenType
  Token::Token (TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }

  // Set to a specific TokenType
  void Token::setToType(TokenType t)
  {
    type = t;
    op = '$';
    val = -999;
  }

  // Set to a OPERATOR TokenType with specific operator value
  void Token::setToOperator(char c)
  {
    type = OPERATOR;
    op = c;
    val = -999;
  }

  // Set to a VALUE TokenType with a specific numeric value
  void Token::setToValue(int v)
  {
    type = VALUE;
    op = '$';
    val = v;
  }

  // return true if the Current Token is of the given TokenType
  bool Token::equalsType(TokenType t)
  {
    if (type == t)
      return true;
    else
      return false;
  }

  // return true if the Current Token is of the OPERATOR TokenType
  //     and contains the given operator character
  bool Token::equalsOperator(char c)
  {
    if (type == OPERATOR && op == c)
      return true;
    else
      return false;
  }

  // Return the Operator for the current Token
  //   verify the current Token is of the OPERATOR TokenType
  char Token::getOperator ()
  {
    if (type == OPERATOR)
      return op;
    else
      return '$';   // using $ to indicate an error value
  }

  // Return the Value for the current Token
  //   verify the current token is of the value TokenType
  int Token::getValue()
  {
    if (type == VALUE)
      return val;
    else
      return -999;  // using -999 to indicate an error value
  }


  // initialize the TokenReader class to read from Standard Input
  TokenReader::TokenReader()
  {
    // set to read from Standard Input
    inputline[0] = '\0';
    pos = 0;
    needline = true;
  }

  // Force the next getNextToken to read in a line of input
  void TokenReader::clearToEoln()
  {
    needline = true;
  }

  // Return the next Token from the input line
  Token TokenReader::getNextToken()
  {
    char* endCheck;

    //printf ("getToken %d, %d, %s\n", pos, needline, inputline);

    // get a new line of input from user
    if (needline)
    {
      endCheck = fgets ( inputline, 300, stdin);

      if (endCheck == NULL )
      {
        printf ("Error in reading");
        Token t(EOFILE);
        return t;
      }

      for (int i = 0 ; i < strlen(inputline) ; i++)
          if ('\n' == inputline[i])
              inputline[i] = ' ';
      strcat (inputline , " ");    // add a space at end to help deal with digit calculation
      needline = false;
      pos = 0;
    }

    // skip over any white space characters in the beginning of the input
    while ( pos < strlen(inputline) && isspace(inputline[pos]) )
    {
      pos++;
    }

    // check for the end of the current line of input
    if (pos >= strlen(inputline))
    { // at end of line
      needline = true;
      Token t(EOLN);
      return t;
    }

    // Get the next character from the input line
    char ch = inputline[pos]; pos++;

    // check if 'q' or 'Q' was entered ==> QUIT Token
    if ( 'q' == ch || 'Q' == ch )
    {
      return Token (QUIT);
    }

    // check if "?" was entered ==> HELP Token
    if ( '?' == ch )
    {
      return Token (HELP);
    }

    // check for Operator values of: + - * / ( )  ==> OPERATOR Token
    if ( ('+' == ch) || ('-' == ch) || ('*' == ch) ||
      ('/' == ch) || ('(' == ch) || (')' == ch) )
    {
      Token t;
      t.setToOperator( ch );
      return t;
    }

    // check for a number  ==> VALUE Token
    if (isdigit(ch))
    {
      int number = int (ch) - int('0');  // subtract ascii value of ch from ascii value of '0'
      ch = inputline[pos]; pos++;
      while (isdigit(ch))
      {
        number = number * 10 + int (ch) - int('0');
        ch = inputline[pos]; pos++;
      }
      pos--; // since number calcuation check one character after the last digit
      Token t;
      t.setToValue( number );
      return t;
    }

    // Input in not valid if code get to this part ==> ERROR Token
    return Token (ERROR);
  }


 // Functions in public can be used anywhere outside the class and can be called by a dot operator.

	// First let us initialize by making constructor.

	// CONSTRUCTOR TO INTIALIZE.
	myClass::myClass()
	{
		size = 2;
		darr = new int[size];
		top = -1;
		posValue = 0;
		operation = '\0';
	}
// CHECK EMPTY FUNCTION
	bool myClass::isEmpty()
	{
		if (top == -1)
			return true;
		else
			return false;
	}

// PUSH FUNCTION. If the array is fulled, then the dynamic array is doubled the size inside.
	void myClass::push(int val, bool flag)
	{

		darr[top + 1] = val;

		if (flag == false)
		{
			//printf(" Number: %d\n", flag);
			printf(" The value pushed in the OPERATOR STACK is %c \n", (char)darr[top + 1]);
		}

		else
		{
			//printf(" Number: %d\n", flag);
			printf(" The value pushed in the VALUE STACK is %d \n", darr[top + 1]);
		}

		
		top = top + 1;

		// If size is equal to top, then grow the array by double.
		if (size == top)
		{
			int *temp;
			size = size + 2;
			temp = new int[size];

			for (int i = 0; i <= size; i++)
			{
				temp[i] = darr[i];
			}

			delete[] darr;
			darr = temp;

		}


	}

// TOP FUNCTION. It is to get the top value of either operator stack or value stack.

	int myClass::topOfStack()
	{
		if (isEmpty() == true)
		{
			printf(" Error because stack is empty.");
		}
		else 
		{
			return darr[top];
		}
		
	}

// POP FUNCTIONS. It returns the value to be popped from either value stack or operation stack.
	char myClass::popOperator()
	{
		posValue = darr[top];
		top--;
		return posValue;
	}

	int myClass::popValue()
	{
		operation = darr[top];
		top--;
		return operation;
	}

// Function to make the stack empty.
	void myClass::makeEmpty()
	{
		delete[] darr;
	}

