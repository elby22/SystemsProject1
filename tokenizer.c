/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */
struct TokenizerT_ {
  char *tokenString;
	int position;
};
typedef struct TokenizerT_ TokenizerT;

char *addToken(TokenizerT *tk, char *type, int p, int q);

char *keywords[] = {"if","auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
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
	Tokenizer->tokenString = malloc(sizeof(char) * strlen(ts) + 1);
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
  free(tk->tokenString);
  free(tk);
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
	char *string;
	int length = strlen(tk->tokenString);
	int octalCheck = 0;
	int floatCheck = 0;
	int flOne = 0;
	int flTwo = 0;
	int flThree = 0;
  char *type;
	while(p < length){
		if(isalpha(tk->tokenString[p])){
			while(isalnum(tk->tokenString[q])){
				q++;
      }
      type = "word";

      /*Extra credit - Checking for c keywords
      *"if" isn't working and I have no idea why. I'm getting some '`' char in gdb. wtf C.
      */
      string = malloc((q-p) * sizeof(char));
      for(i = p; i < q; i++){
        string[j] = tk->tokenString[i];
        j++;
      }
      
      for(i = 0; i < 32; i++){ /*32 keywords*/
        if(strcmp(string, keywords[i]) == 0){
          type = "c keyword";
          break;
        }
      }
      return addToken(tk, type, p, q);
		/*This section will handle all numbers starting with 0, including Hex, Float, Decimal, and Octal */
		}else if(tk->tokenString[p] == '0'){
			/*handles Hex*/
			if(tk->tokenString[p+1] != '\0' && (tk->tokenString[p+1] == 'x' || tk->tokenString[p+1] == 'X')){
				q = p+2;
				while(isxdigit(tk->tokenString[q])){
					q++;
				}
				
				type = "hexadecimal integer constant";
				return addToken(tk, type, p, q);
			/*handles decimal and octal*/
			}else{
				while(tk->tokenString[q] == '.' || isdigit(tk->tokenString[q])){
					if(tk->tokenString[q] == '8' || tk->tokenString[q] == '9'){   /*checks if decimal or octal*/
						octalCheck = 1;											  /*designates that this token is not Octal*/
					}
					if(tk->tokenString[q] == '.'){
						q++;
						floatCheck = 1;
						
						/*allows for checking for 'e' and 'E' by checking that there is a number
						after the '.'   also checks for malformed tokens*/
						if(isdigit(tk->tokenString[q])){
							q++;
							
							/*checks for numbers or 'e' or 'E' for float */
							while(tk->tokenString[q] == 'E' || tk->tokenString[q] == 'e' || isdigit(tk->tokenString[q])){
								
								/*once an 'e' or 'E' has been found, only checks for numbers*/
								if(tk->tokenString[q] == 'E' || tk->tokenString[q] == 'e'){
									flThree = 1;
									q++;
									while(isdigit(tk->tokenString[q])){
										q++;
									}
								}
								if(flThree == 1){
									break;
								}
								q++;
								
							}
						
						}else{
						/*malformed token*/
						}
					}
					if(floatCheck == 1){
						break;
					}
					q++;
				}
				if(floatCheck == 1){
					type = "floating-point constant";
					return addToken(tk, type, p, q);
				}else if(octalCheck == 0){
					type = "octal integer constant";
					return addToken(tk, type, p, q);
				}else{
					type = "decimal integer constant";
					return addToken(tk, type, p, q);
				}
			}
		/*Finds Float and Decimal tokens that don't start with 0. Still needs error checking but shouldn't be a big deal.
		I'll do error checking tomorrow after class */
		}else if(isdigit(tk->tokenString[p]) && tk->tokenString[p] != '0'){
			while(tk->tokenString[q] == '.' || isdigit(tk->tokenString[q])){
				
				/*checks for float*/
				if(tk->tokenString[q] == '.'){
					q++;
					floatCheck = 1;
					while(isdigit(tk->tokenString[q])){
						q++;
					}
				}
				if(floatCheck == 1){
					break;
				}
				q++;
			}
			
			if(floatCheck == 1){
				type = "floating-point constant";
			}else{
				type = "decimal integer constant";
			}
			return addToken(tk, type, p, q);
		/*EXTRA CREDIT - Check for tokes within double quotes*/
		}else if(tk->tokenString[p] == '"'){
		  q++;
		  while((tk->tokenString[q] != '"')){
				q++;
			}
			q++;
			type = "double-quoted";
			return addToken(tk, type, p, q);
		/*EXTRA CREDIT - Check for tokes within single quotes*/
		}else if(tk->tokenString[p] == '\''){
		  q++;
		  while((tk->tokenString[q] != '\'')){
				q++;
			}
			q++;
			type = "single-quoted";
			return addToken(tk, type, p, q);
			
/*Check for whitespace characters, skip over*/
		}else if(isspace(tk->tokenString[p])){
			q++;
			p = q;
		  tk->position = p;
			continue;
		/*Check for all C operators and anything that isn't returns 0*/
		}else{
		  switch(tk->tokenString[p]){
		    case '(':
		      type = "open parenthesis";
		      break;
		    case ')':
		      type = "close parenthesis";
		      break;
		    case '[':
		      type = "leftbrace";
		      break;
		    case ']':
		      type = "rightbrace";
		      break;
		    case '.':
		      type = "dot operator";
		      break;
		    case '!':
		      if(tk->tokenString[p+1] == '='){
		        q++;
		        type = "not equals operator";
		      }else{
		        type = "negation operator";
		      }
		      break;
		    case '~':
		      type = "tilde";
		      break;
		    case '+':
		    	if(tk->tokenString[p+1] == '+'){
		        q++;
		        type = "increment operator";
		      }else if(tk->tokenString[p+1] == '='){
		        q++;
		        type = "increment assignment operator";
		      }else{
		        type = "addition operator";
		      }
		      break;
		    case '-':
		      if(tk->tokenString[p+1] == '-'){
		        q++;
		        type = "decrement operator";
		      }else if(tk->tokenString[p+1] == '='){
		        q++;
		        type = "decrement assignment operator";
		      }else{
		        type = "subtraction operator";
		      }
		      break;
		    case '*':
		    	if(tk->tokenString[p+1] == '='){
		        q++;
		        type = "multiply assignment operator";
		      }else{
		        type = "multiply operator";
		      }
		      break;
		    case '/':
		    	if(tk->tokenString[p+1] == '='){
		        q++;
		        type = "division assignment operator";
		    	}else if(tk->tokenString[p+1] == '*'){ /*EXTRA CREDIT - Comments*/
		    	  q++;
		    	  q++;
		    	  while(tk->tokenString[q] != '*' && tk->tokenString[q+1] != '/'){
		    	    q++;
		    	  }
		    	  q++;
		    	  q++;
		    	  p = q;
		        tk->position = p;
			      continue;
		      }else{
		        type = "division operator";
		      }
		      break;
		    case '%':
		    	if(tk->tokenString[p+1] == '='){
		        q++;
		        type = "modulus assignment operator";
		      }else{
		        type = "modulus operator";
		      }
		      break;
		    case '<':
		    	if(tk->tokenString[p+1] == '<'){
		    	  if(tk->tokenString[p+2] == '='){
		    	    q++;
		    	    q++;
		          type = "left shift assignment operator";
		    	  }else{
		    	    q++;
		    	    type = "left shift operator";
		    	  }
		    	}else if(tk->tokenString[p+1] == '='){
		    	  q++;
		    	  type = "less or equal operator";
		      }else{
            type = "less than operator";
		      }
		      break;
		    case '>':
		    	if(tk->tokenString[p+1] == '>'){
		    	  if(tk->tokenString[p+2] == '='){
		    	    q++;
		    	    q++;
		          type = "right shift assignment operator";
		    	  }else{
		    	    q++;
		    	    type = "right shift operator";
		    	  }
		    	}else if(tk->tokenString[p+1] == '='){
		    	  q++;
		    	  type = "greater or equal operator";
		      }else{
            type = "greater than operator";
		      }
		      break;
		    case '&':
		    	if(tk->tokenString[p+1] == '&'){
	    	    q++;
	    	    type = "logical and operator";
		    	}else if(tk->tokenString[p+1] == '='){
		    	  q++;
	    	    type = "bitwise and assignment operator";
		      }else{
            type = "bitwise and operator";
		      }
		      break;
		    case '|':
		      if(tk->tokenString[p+1] == '|'){
	    	    q++;
	    	    type = "logical or operator";
		    	}else if(tk->tokenString[p+1] == '|'){
		    	  q++;
	    	    type = "bitwise or assignment operator";
		      }else{
            type = "bitwise or operator";
		      }
		      break;
		    case '^':
		      if(tk->tokenString[p+1] == '='){
		        q++;
		        type = "exclusive or assignment operator";
		      }else{
		        type = "exclusive or operator";
		      }
		      break;
		    case ',':
		      type = "comma operator";
		      break;
		    case '?':
		      type = "ternary operator";
		      break;
		    default:  /*Not Recognized*/
		      return 0;
		  }
		  q++;
		  return addToken(tk, type, p, q);
		}
		p = q;
		tk->position = p;
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

	while(TKGetNextToken(Tokenizer) != 0);
	TKDestroy(Tokenizer);
	return 0;
}

char *addToken(TokenizerT *tk, char *type, int p, int q){
  int i = 0;
  int j = 0;
  char *string;
  string = malloc(((q-p) + 2) * sizeof(char));

  /*
   *Copies the string into the token from the tokenString
   */
  for(i = p; i < q; i++){
    string[j] = tk->tokenString[i];
    j++;
  }
  string[j+1] = '\0';
  
  printf("%s \"%s\"\n", type, string);
  
  p = q;
  tk->position = p;
  return string;
}
