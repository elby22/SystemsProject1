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
	int length = strlen(tk->tokenString);
	int octalCheck = 0;
  char *type;
  char *retVal;
	if(p < length){
		if(isalpha(tk->tokenString[p])){
			while(isalnum(tk->tokenString[q])){
				q++;
      }
      
      type = malloc(5);
      type = "word\0";
      addToken(tk, type, p, q);
		/*This section will handle all numbers starting with 0, including Hex, Float, Decimal, and Octal */
		}else if(tk->tokenString[p] == '0'){
			/*handles Hex*/
			if(tk->tokenString[p+1] != NULL && (tk->tokenString[p+1] == 'x' || tk->tokenString[p+1] == 'X')){
				q = p+2;
				while(isxdigit(tk->tokenString[q])){
					q++;
				}
				
				type = malloc(29);
				type = "hexadecimal integer constant\0";
        addToken(tk, type, p, q);
			/*handles decimal and octal*/
			}else{
				while(isdigit(tk->tokenString[q])){
					if(tk->tokenString[q] == '8' || tk->tokenString[q] == '9'){   /*checks if decimal or octal*/
						octalCheck = 1;											  /*designates that this token is not Octal*/
					}
					q++;
				}
			
				if(octalCheck == 0){
					type = malloc(23);
					type = "octal integer constant\0";
				}else{
					type = malloc(25);
					type = "decimal integer constant\0";
				}
				addToken(tk, type, p, q);
			}
		/*Finds Octal and Decimal tokens that don't start with 0. Still needs error checking but shouldn't be a big deal.
		I'll do error checking tomorrow after class */
		}else if(isdigit(tk->tokenString[p]) && tk->tokenString[p] != "0"){
			while(isdigit(tk->tokenString[q])){
				q++;
			}
			
			type = malloc(25);
			type = "decimal integer constant\0";
			addToken(tk, type, p, q);
			
		}else if(isspace(tk->tokenString[p])){
			q++;
		}else{
			return 0;
		}
		p = q;
		tk->position = p;
		/*return tk->tokenList->string;*/
		return "glarf";
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
	/*Prints all tokens in the linked list, backwards to fowards */
	printf("Final output test: \n");
	Token *root = tk->tokenList;
	while(root != 0){
		printf("%s \"%s\"\n", root->type, root->string);
		root = root->next;
  }
}

void addToken(TokenizerT *tk, char *type, int p, int q){
  int i = 0;
  int j = 0;
  
  Token *token;
  token = malloc(sizeof(Token));
  token->type = malloc(strlen(type));
  token->string = malloc((q-p) + 1);
  strcpy(token->type, type);
  
  /*
   *Copies the string into the token from the tokenString
   */
  for(i = p; i < q; i++){
    token->string[j] = tk->tokenString[i];
    j++;
  }
  token->string[j+1] = '\0';
  
  printf("%s \"%s\"\n", token->type, token->string);
  token->next = tk->tokenList;
  tk->tokenList = token;
}
