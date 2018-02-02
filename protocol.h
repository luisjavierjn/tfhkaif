#ifndef __FLEX_LEXER_H
#define yyFlexLexer BixolonFlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif

#ifndef _PROTOCOL_SCANNER_H_
#define _PROTOCOL_SCANNER_H_

#include "printer.h"
#include "state_machines.h"

namespace Quorion {

/** Scanner is a derived class to add some extra function to the scanner
 * class. Flex itself creates a class named yyFlexLexer, which is renamed using
 * macros to ExampleFlexLexer. However we change the context of the generated
 * yylex() function to be contained within the Scanner class. This is required
 * because the yylex() defined in ExampleFlexLexer has no parameters. */
class Protocol : public BixolonFlexLexer
{
public:
    /** Create a new scanner object. The streams arg_yyin and arg_yyout default
     * to cin and cout, but that assignment is only made when initializing in
     * yylex(). */
    Protocol(Printer *sm_print,::istream* arg_yyin = 0,
		::ostream* arg_yyout = 0);

    /** Required for virtual functions */
    virtual ~Protocol();

    /** Enable debug output (via arg_yyout) if compiled into the scanner. */
    void set_debug(bool b);

	char* YYText();

	long YYLeng();

	int yywrap();

	char* QPrint();

	long QPLeng();

	int QError();

	int BStatus();

private:
	char* _bxtext;
	long _bxleng;
	char* _qprint;
	long _qpleng;
	Printer *_printer;
	SM_Inicial *_smStart;
};

} // namespace Quorion

#endif // _PROTOCOL_SCANNER_H_