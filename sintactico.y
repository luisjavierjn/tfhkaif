%{
 
#include <stdio.h>
#include <math.h>
extern int yylex(void);
extern char *yytext;
void yyerror (char *s);
 
%}
 
%union
{
float real;
}
 
%start Calculadora
 
%token <real> TKN_NUM
%token TKN_ASIGN
%token TKN_PTOCOMA
%token TKN_MULT
%token TKN_DIV
%token TKN_MAS
%token TKN_MENOS
 
%token <real> TKN_ID
%type <real> Expresion
 
%left TKN_MAS TKN_MENOS
%left TKN_MULT TKN_DIV
 
%%
 
Calculadora: TKN_ID {printf("El valor de %s es:", yytext);}
TKN_ASIGN Expresion TKN_PTOCOMA{printf("%5.2f", $4);};
Expresion : TKN_NUM{$$=$1;}|
Expresion Expresion TKN_MAS {$$=$1+$2;}|
Expresion Expresion TKN_MENOS {$$=$1-$2;}|
Expresion Expresion TKN_MULT {$$=$1*$2;}|
Expresion Expresion TKN_DIV {$$=$1/$2;};
 
%%
 
void yyerror(char *s)
{
printf("Error %s", s);
}
 
int main()
{
yyparse();
return 0;
}
