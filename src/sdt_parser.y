%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token NUM
%left '+' '-'
%left '*' '/'

%%
input : /* empty */
      | input line
      ;

line : '\n'
     | expr '\n' { printf("SDT Evaluated Result = %d\n", $1); }
     ;

expr : expr '+' expr   { $$ = $1 + $3; }
     | expr '-' expr   { $$ = $1 - $3; }
     | expr '*' expr   { $$ = $1 * $3; }
     | expr '/' expr   { $$ = $1 / $3; }
     | '(' expr ')'     { $$ = $2; }
     | NUM             { $$ = $1; }
     ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter arithmetic expressions for SDT Evaluation:\n");
    return yyparse();
}
