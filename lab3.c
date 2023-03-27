/* A lexical analyzer system for simple
arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();
/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
void expr(void);
void factor(void);
void term(void);
/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
/******************************************************/
/* main driver */
int main()
{
      /* Open the input data file and process its contents */
      if ((in_fp = fopen("test1.txt", "r")) == NULL)
            printf("ERROR - cannot open test1.txt \n");
      else
      {
            getChar();
            do
            {
                  expr();
            } while (nextToken != EOF);
      }

      if ((in_fp = fopen("test2.txt", "r")) == NULL)
            printf("ERROR - cannot open test2.txt \n");
      else
      {
            getChar();
            do
            {
                  expr();
            } while (nextToken != EOF);
      }

      if((in_fp = fopen("test3.txt", "r")) == NULL)
          printf("ERROR - cannot open test3.txt \n");
      else
      {
            getChar();
            do
            {
                  expr();
            } while (nextToken != EOF);
      }
}
/*****************************************************/
/* lookup - a function to lookup operators and parentheses
and return the token */
int lookup(char ch)
{
      switch (ch)
      {
      case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
      case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
            // YOUR CODE
      case '=':
            addChar();
            nextToken = ASSIGN_OP;
            break;
      case '+':
            addChar();
            nextToken = ADD_OP;
            break;
      case '-':
            addChar();
            nextToken = SUB_OP;
            break;
      case '*':
            addChar();
            nextToken = MULT_OP;
            break;
      case '/':
            addChar();
            nextToken = DIV_OP;
            break;
      }
      return nextToken;
}
/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar()
{
      if (lexLen <= 98)
      {
            // YOUR CODE
            lexeme[lexLen] = nextChar;
            lexLen++;
      }
      else
            printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of
input and determine its character class */
void getChar()
{
      if ((nextChar = getc(in_fp)) != EOF)
      {
            if (isalpha(nextChar))
                  charClass = LETTER;
            else if (isnumber(nextChar))
                  // YOUR CODE
                  charClass = DIGIT;
            else
                  // YOUR CODE;
                  charClass = UNKNOWN;
      }
      else
            charClass = EOF;
}
/*****************************************************/
/* getNonBlank - a function to call getChar until it
returns a non-whitespace character */
void getNonBlank()
{
      while (isspace(nextChar))
            getChar();
}
/*
*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
expressions */
int lex()
{
      lexLen = 0;
      getNonBlank();
      switch (charClass)
      {
      /* Parse identifiers */
      case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT)
            {
                  addChar();
                  getChar();
            }
            nextToken = IDENT;
            break;
      /* Parse integer literals */
      // YOUR CODE
      case DIGIT:
            do
            {
                  addChar();
                  getChar();
            } while (charClass == DIGIT);
            nextToken = INT_LIT;
            break;
      /* Parentheses and operators */
      case UNKNOWN:
            // YOUR CODE
            nextToken = lookup(nextChar);
            getChar();
            break;
      /* EOF */
      case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
      } /* End of switch */
      printf("Next token is: %d, Next lexeme is %s\n",
             nextToken, lexeme);
      while (lexLen >= 0)
      {
            lexeme[lexLen] = '\0';
            lexLen--;
      }

      return nextToken;
} /* End of function lex */

/* expr
Parses strings in the language generated by the rule:
<expr> -> <term> {(+ | -) <term>}
*/
void expr(void)
{
      printf("Enter <expr>\n");
      /* Parse the first term */
      term();
      /* As long as the next token is + or -, get
      the next token and parse the next term */
      // YOUR CODE
      while (nextToken == ADD_OP || nextToken == SUB_OP)
      {
            lex();
            term();
      }
      // Display exit message
      printf("Exit <expr>\n");
}

/* term
Parses strings in the language generated by the rule:
<term> -> <factor> {(* | /) <factor>}
*/
void term(void)
{
      printf("Enter <term>\n");
      /* Parse the first factor */
      // YOUR CODE
      factor();
      /* As long as the next token is * or /, get the
      next token and parse the next factor */
      // YOUR CODE
      while (nextToken == MULT_OP || nextToken == DIV_OP)
      {
            lex();
            factor();
      }
      // Display exit message
      printf("Exit <term>\n");
}

/* factor
Parses strings in the language generated by the rule:
<factor> -> id | int_constant | ( <expr> )
*/
void factor(void)
{
      printf("Enter <factor>\n");
      /* Determine which RHS: variable or constant*/
      // YOUR CODE
      if (nextToken == IDENT || nextToken == INT_LIT)
      {

            /* Get the next token */
            // YOUR CODE
            lex();
      }
      /* If the RHS is ( <expr> ), call lex to pass over the
      left parenthesis, call expr, and check for the right
      parenthesis (No right parenthesis  syntax error */
      // YOUR CODE
      else
      {
            if (nextToken == LEFT_PAREN)
            {
                  lex();
                  expr();
                  if (nextToken == RIGHT_PAREN)
                  {
                        lex();
                  }
                  else
                  {
                        error();
                  }
            }
      }
      /* It was not an id, an integer literal, or a left
      Parenthesis  syntax error */
      // YOUR CODE
      error();
      // Display exit message
      printf("Exit <factor>\n");
} // close the function

void error(void)
{
      printf("SYNTAX ERROR \n");
}