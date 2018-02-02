/* scanner for a toy Pascal-like language */
     
%{
/* need this for the call to atof() below */
#include "StdAfx.h"
#include <stdio.h>
#include <math.h>
#include "protocol.h"

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H
%}

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "ExampleFlexLexer" */
%option prefix="Bixolon"

/* the manual says "somewhat more optimized" */
%option batch

/* enable scanner to generate debug output. disable this for release
 * versions. */
%option debug

/* no support for include files is planned */
%option yywrap nounput 
     
DIGIT    [0-9]
ID       [a-z][a-z0-9]*
     
%%
     
{DIGIT}+    {
            printf( "An integer: %s (%d)\n", yytext,
                    atoi( yytext ) );
            }
     
{DIGIT}+"."{DIGIT}*        {
            printf( "A float: %s (%g)\n", yytext,
                    atof( yytext ) );
            }
     
if|then|begin|end|procedure|function        {
            printf( "A keyword: %s\n", yytext );
            }
     
{ID}        printf( "An identifier: %s\n", yytext );
     
"+"|"-"|"*"|"/"   printf( "An operator: %s\n", yytext );
     
"{"[\^{}}\n]*"}"     /* eat up one-line comments */
     
[ \t\n]+          /* eat up whitespace */
     
.           printf( "Unrecognized character: %s\n", yytext );
     
%%

int Bixolonwrap()
{
	return 1;
}
     
int main(int argc, char** argv)
{
	/*
	++argv, --argc;  // skip over program name
	if ( argc > 0 )
		yyin = fopen( argv[0], "r" );
	else
		yyin = stdin;
     
	yylex();
	*/
	yyFlexLexer Lexer;
	Lexer.yylex();
	return 0;
}
