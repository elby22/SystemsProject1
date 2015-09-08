/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Token type. Essentially a linked list of tokens, the head of which is the tokenList of the TokenizerT.
 */
struct Token_ {
  char *type;
  char *string;
  struct Token_ *next;
};
typedef struct Token_ Token;

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */
struct TokenizerT_ {
    Token *tokenList;
    char *tokenString;
	int position;
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
    TokenizerT *Tokenizer = malloc(sizeof(TokenizerT));
	Tokenizer->tokenString = malloc(sizeof(char) * strlen(ts));
	Tokenizer->tokenList = 0;
	strcpy(Tokenizer->tokenString, ts);
	Tokenizer->position = 0;
	return Tokenizer;
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
	int p = tk->position;
	int q = p;
	int i = 0;
	int j = 0;
	int length = strlen(tk->tokenString);
	Token *token;
	if(p < length){
		if(isalpha(tk->tokenString[p])){
			printf("p: %d\n", p);	
			while(isalnum(tk->tokenString[q])){
				q++;
            }
      	  	printf("q: %d\n", q);
      /*
      * (q-p) + 1  for array size
      */
          token = malloc(sizeof(Token));	
          token->type = malloc(5);
          token->type = "word\0";
          token->string = malloc((q-p) + 1);
          /*
          *
          */ 	
          j = 0;
          for(i = p; i < q; i++){
              token->string[j] = tk->tokenString[i];
              j++;
          }
          token->string[j+1] = '\0';
          printf("token: %s\n", token->string);
          printf("type: %s\n", token->type);
		  token->next = tk->tokenList;
          tk->tokenList = token;
      }else if(isspace(tk->tokenString[p])){
          printf("spaceChar\n");
          q++;	
      }else{
          return 0;
      }
      p = q;
      tk->position = p;
	  return token->string;
	}
	return 0;
}

/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
	TokenizerT *Tokenizer = TKCreate(argv[1]);
    printf("Input: %s\n", Tokenizer->tokenString);
    
	while(TKGetNextToken(Tokenizer) != 0);
    printTokens(Tokenizer);
	return 0;
}

void printTokens(TokenizerT *tk){	
	/*Prints all tokens in the linked list */
	printf("Final output test: \n");
	Token *root = tk->tokenList;
	while(root != 0){
		printf("%s \"%s\"\n", root->type, root->string);
		root = root->next;		  
    }
}
