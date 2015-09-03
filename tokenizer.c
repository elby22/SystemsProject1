/*
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
};
typedef struct TokenizerT_ TokenizerT;

struct Token_ {
  char type[32];
  char *subString;
};
typedef struct Token_ Token;

struct Node_ {
  Token token;
  struct Node_ *next;
};
typedef struct Node_ Node;
/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {

  return NULL;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {

  return NULL;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
  char *string = argv[1];
  
  printf("Input string: %s\n", string);
  
  int p = 0;
  int q = 0;
  int length = strlen(string);
  int i;
  int j;
  while (p < length){
    if(1){
    /* if(isLetter(string[p])){
        while(isWord(string[q])){ */
      while(q < length){
        q++;
      }
      
      /*
      * (q-p) + 1  for array size
      */
      Node *temp = malloc(sizeof(Node) + (q-p));
      /* temp->token.type = "word"; */
      
      j = 0;
      for(i = p; i < q-1; i++){
        temp->token.subString[j] = string[i];
        j++;
      }
      temp->token.subString[j+1] = '\0';
    }
    break;
  }
  return 0;
}