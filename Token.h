/* This file contains the user interface code for the Infix Evaluation Project
 *  Project 5 for CS 211 for Fall 2017
 *
 * Date: 10/21/17
 *
 * Author: Nemil Shah
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

#include<stdio.h>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <stdlib.h>

// Enumarated Type specifying all of the Tokens
enum TokenType{
  ERROR, OPERATOR, VALUE, EOLN, QUIT, HELP, EOFILE
};

#define TRUE 1              // typical C boolean set-up  
#define FALSE 0

extern int DEBUG_MODE;   // Global variable.

class myClass
{
private:
	// Private data members will not allowed to be used anywhere other than class.

	int* darr;
	int size;
	int top;
	int posValue;
	char operation;
public:

// Functions in public can be used anywhere outside the class and can be called by a dot operator.

	// First let us initialize by making constructor.

	// CONSTRUCTOR TO INTIALIZE.
	myClass();

// CHECK EMPTY FUNCTION
	bool isEmpty();

// PUSH FUNCTION. If the array is fulled, then the dynamic array is doubled the size inside.
	void push(int val, bool flag);

// TOP FUNCTION. It is to get the top value of either operator stack or value stack.

	int topOfStack();

// POP FUNCTIONS. It returns the value to be popped from either value stack or operation stack.
	char popOperator();

	int popValue();

// Function to make the stack empty.
	void makeEmpty();
};

// Class to hold the Token information
class Token
{
  private:
    TokenType type;
    char      op;       // using '$' as undefined/error
    int       val;      // using -999 as undefined/error

  public:

  // Default to initialize to the ERROR TokenType
  Token();

  // Initialize to a specific TokenType
  Token (TokenType t);

  // Set to a specific TokenType
  void setToType(TokenType t);

  // Set to a OPERATOR TokenType with specific operator value
  void setToOperator(char c);

  // Set to a VALUE TokenType with a specific numeric value
  void setToValue(int v);

  // return true if the Current Token is of the given TokenType
  bool equalsType(TokenType t);

  // return true if the Current Token is of the OPERATOR TokenType
  //     and contains the given operator character
  bool equalsOperator(char c);

  // Return the Operator for the current Token
  //   verify the current Token is of the OPERATOR TokenType
  char getOperator ();

  // Return the Value for the current Token
  //   verify the current token is of the value TokenType
  int getValue();
};


class TokenReader
{
  private:
     char inputline[300];  // this assumes that all input lines are 300 characters or less in length
     bool needline;
     int pos;


  public:

  // initialize the TokenReader class to read from Standard Input
  TokenReader();

  // Force the next getNextToken to read in a line of input
  void clearToEoln();

  // Return the next Token from the input line
  Token getNextToken();
};

