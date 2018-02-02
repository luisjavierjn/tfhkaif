// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__DC70816E_3899_46FA_AA6B_6E9690FE49E1__INCLUDED_)
#define AFX_STDAFX_H__DC70816E_3899_46FA_AA6B_6E9690FE49E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>

#ifndef __FLEX_LEXER_H
#define yyFlexLexer ExampleFlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif

// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__DC70816E_3899_46FA_AA6B_6E9690FE49E1__INCLUDED_)
