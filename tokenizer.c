/*
 * tokenizer.c
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>


struct Token_ {
  char *type;
  char *subString;
};
typedef struct Token_ Token;

struct Node_ {
  Token *token;
  struct Node_ *next;
};
typedef struct Node_ Node;

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */
struct TokenizerT_ {
    Node *root;
    char *tokenString;
};
typedef struct TokenizerT_ TokenizerT;

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
  int i = 0;
  int j = 0;
  Node *root = 0;
  while (p < length){
      if(isalpha(string[p])){
          printf("p: %d\n", p);
          while(isalnum(string[q])){
              q++;
          }
      	  printf("q: %d\n", q);
      /*
      * (q-p) + 1  for array size
      */
          Node *temp = malloc(sizeof(Node));
          temp->token = malloc(sizeof(Token));
          temp->token->type = malloc(5);
          temp->token->type = "word\0";
          temp->token->subString = malloc((q-p) + 1);
          /*temp->token->type = "Word";*/
          j = 0;
          for(i = p; i < q; i++){
              temp->token->subString[j] = string[i];
              j++;
          }
          temp->token->subString[j+1] = '\0';
          printf("token: %s\n", temp->token->subString);
          printf("type: %s\n", temp->token->type);
	  temp->next = root;
          root = temp;
      }else if(isspace(string[p])){
          printf("spaceChar\n");
          q++;	
      }
      p = q;
    }

  /*Prints all tokens in the linked list */
  printf("Final output test: \n");
  while(root != 0){
      printf("%s \"%s\"\n", root->token->type, root->token->subString);
      root = root->next;	  
  }
  return 0;
}
