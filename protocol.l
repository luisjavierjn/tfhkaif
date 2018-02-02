/* scanner for a toy Pascal-like language */
     
%{
/* need this for the call to atof() below */
#include "StdAfx.h"
#include <stdio.h>
#include <math.h>
#include "protocol.h"
#include "bixolon.h"
#include "state_machines.h"

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

char* bxtext;
long* bxleng;
char* qprint;
long* qpleng;
Quorion::Bixolon bix;
//Quorion::Printer *cmds;
Quorion::SM_Inicial *smStart;

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

TKN_DIGIT							[[:digit:]]
TKN_ID								[[:alnum:][:space:][:graph:]'´']
/*TKN_ID								.*/

TKN_CONF_DATOS_DEL_CAJERO			PC{TKN_DIGIT}{7}{TKN_ID}{0,16}
TKN_CONF_NOMBRES_FORMAS_DE_PAGOS	PE{TKN_DIGIT}{2}{TKN_ID}{0,14}
TKN_CONF_HORA						PF{TKN_DIGIT}{6}
TKN_CONF_FECHA						PG{TKN_DIGIT}{6}
TKN_CONF_DEL_IVA					PT[0-2]{TKN_DIGIT}{4}[0-2]{TKN_DIGIT}{4}[0-2]{TKN_DIGIT}{4}
TKN_CONF_DEL_IVA_MEMORIA_FISCAL		Pt
TKN_CONF_ENCABEZADO					PH0[1-8]{TKN_ID}{0,40}
TKN_CONF_PIE_DE_FACTURA				PH9[1-8]{TKN_ID}{0,40}

TKN_CAJERO_INICIO					5{TKN_DIGIT}{5}
TKN_CAJERO_FIN						6
TKN_DATOS_CLIENTE					i{TKN_DIGIT}{2}{TKN_ID}{0,56}
TKN_FACT_REGISTRO_PRODUCTO			[!|"|#| ]{TKN_DIGIT}{18}{TKN_ID}{0,38}
TKN_FACT_DESCRIPCION_PRODUCTO		@{TKN_ID}{0,40}
TKN_FACT_CORRECCION					k
TKN_FACT_SUBTOTAL					3
TKN_FACT_RECARGO_O_DESCUENTO		p[+|-]{TKN_DIGIT}{4}
TKN_FACT_ANULACION_ITEM				[ |¡|¢|£]{TKN_DIGIT}{18}{TKN_ID}{0,40}
TKN_FACT_ANULACION_FACTURA			7
TKN_FACT_PAGO_DIRECTO				1{TKN_DIGIT}{2}
TKN_FACT_PAGO_PARCIAL				2{TKN_DIGIT}{14}
TKN_FACT_CODIGO_DE_BARRA			y{TKN_DIGIT}{12}

TKN_NC_REGISTRO_PRODUCTO			d[0-3|!|"|#| ]{TKN_DIGIT}{18}{TKN_ID}{0,40}
TKN_NC_ANULACION_ITEM				ä{TKN_DIGIT}{19}{TKN_ID}{0,40}
TKN_NC_CIERRE_DEVOLUCION			[f]{TKN_DIGIT}{14}

TKN_DNF_TEXTO						8[0-1][0|1|2|>|$]{TKN_ID}{0,40}
TKN_DNF_APERTURA_GAVETA				[0|w]
TKN_DNF_PO_RA						[9][0|1]{TKN_DIGIT}{14}
TKN_DNF_FINALIZAR_PO_RA				t
TKN_DNF_PRINT_VALOR_CONF			D

TKN_DISPLAY_MENSAJE					PI{TKN_ID}{0,50}

TKN_STATUS							S[1-5]

TKN_REPORTE_X						I0X
TKN_REPORTE_Z						I0Z
TKN_REPORTE_MFISCAL_FECHA			I2A{TKN_DIGIT}{12}
TKN_REPORTE_MFISCAL_NUMERO			I3A00{TKN_DIGIT}{4}00{TKN_DIGIT}{4}
TKN_REIMPRESION_DOC_POR_FECHA		R[f|c|n|z|r]{TKN_DIGIT}{14}
TKN_REIMPRESION_DOC_POR_NUMERO		R[F|C|N|Z|R]{TKN_DIGIT}{14}
TKN_PRINT_EDO_MEMORIA_AUDITORIA		E

TKN_OTRO_1							PJ{TKN_DIGIT}{4}
TKN_OTRO_2							A
TKN_OTRO_3							a
TKN_OTRO_4							b
TKN_OTRO_5							c[L|U]{TKN_ID}{0,20}
%%

{TKN_CONF_DATOS_DEL_CAJERO}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ConfDatosDelCajero(yytext, qprint);
			
			smStart->Check(Quorion::TKN_CONF_DATOS_DEL_CAJERO,yytext,yyleng);		
			}


{TKN_CONF_NOMBRES_FORMAS_DE_PAGOS}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ConfNombresFormasDePagos(yytext, qprint);
			smStart->Check(Quorion::TKN_CONF_NOMBRES_FORMAS_DE_PAGO,yytext,yyleng);	
			}

{TKN_CONF_HORA}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ConfHora(yytext, qprint);
			smStart->Check(Quorion::TKN_CONF_HORA,yytext,yyleng);
			}

{TKN_CONF_FECHA}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ConfFecha(yytext, qprint);
			smStart->Check(Quorion::TKN_CONF_FECHA,yytext,yyleng);
			}

{TKN_CONF_DEL_IVA}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ConfDelIVA(yytext, qprint);
			smStart->Check(Quorion::TKN_CONF_DEL_IVA,yytext,yyleng);	
			}

{TKN_CONF_DEL_IVA_MEMORIA_FISCAL}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ConfDelIVAMemoriaFiscal(yytext, qprint);
			smStart->Check(Quorion::TKN_CONF_DEL_IVA_MEMORIA_FISCAL,yytext,yyleng);	
			}

{TKN_CONF_ENCABEZADO}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ConfEncabezado(yytext, qprint);
			smStart->Check(Quorion::TKN_CONF_ENCABEZADO,yytext,yyleng);	
			}

{TKN_CONF_PIE_DE_FACTURA}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ConfPieDeFactura(yytext, qprint);
			smStart->Check(Quorion::TKN_CONF_PIE_DE_FACTURA,yytext,yyleng);	
			}


{TKN_CAJERO_INICIO}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.CajeroInicio(yytext, qprint);
			smStart->Check(Quorion::TKN_CAJERO_INICIO,yytext,yyleng);
			}

{TKN_CAJERO_FIN}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.CajeroFin(yytext, qprint);
			smStart->Check(Quorion::TKN_CAJERO_FIN,yytext,yyleng);
			}

{TKN_DATOS_CLIENTE}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.DatosDelCliente(yytext, qprint);
			smStart->Check(Quorion::TKN_DATOS_CLIENTE,yytext,yyleng);
			}

{TKN_FACT_REGISTRO_PRODUCTO}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.FactRegistroDeProducto(yytext, qprint);
			smStart->Check(Quorion::TKN_FACT_REGISTRO_PRODUCTO,yytext,yyleng);
			}

{TKN_FACT_DESCRIPCION_PRODUCTO}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.FactDescripcionDeProducto(yytext, qprint);
			smStart->Check(Quorion::TKN_FACT_DESCRIPCION_PRODUCTO,yytext,yyleng);
			}

{TKN_FACT_CORRECCION}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.FactCorreccion(yytext, qprint);
			smStart->Check(Quorion::TKN_FACT_CORRECCION,yytext,yyleng);
			}

{TKN_FACT_SUBTOTAL}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.FactSubtotal(yytext, qprint);
			smStart->Check(Quorion::TKN_FACT_SUBTOTAL,yytext,yyleng);
			}

{TKN_FACT_RECARGO_O_DESCUENTO}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.FactRecargoODescuento(yytext, qprint);
			smStart->Check(Quorion::TKN_FACT_RECARGO_O_DESCUENTO,yytext,yyleng);
			}

{TKN_FACT_ANULACION_ITEM}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.FactAnulacionITEM(yytext, qprint);
			smStart->Check(Quorion::TKN_FACT_ANULACION_ITEM,yytext,yyleng);
			}

{TKN_FACT_ANULACION_FACTURA}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.FactAnulacionFactura(yytext, qprint);
			smStart->Check(Quorion::TKN_FACT_ANULACION_FACTURA,yytext,yyleng);
			}

{TKN_FACT_PAGO_DIRECTO}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.FactPagoDirecto(yytext, qprint);
			smStart->Check(Quorion::TKN_FACT_PAGO_DIRECTO,yytext,yyleng);
			}

{TKN_FACT_PAGO_PARCIAL}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.FactPagoParcial(yytext, qprint);
			smStart->Check(Quorion::TKN_FACT_PAGO_PARCIAL,yytext,yyleng);
			}

{TKN_FACT_CODIGO_DE_BARRA}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.FactCodigoDeBarra(yytext, qprint);
			smStart->Check(Quorion::TKN_FACT_CODIGO_DE_BARRA,yytext,yyleng);
			}

{TKN_NC_REGISTRO_PRODUCTO}	{			
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			/* Se coloco los caracteres [!|"|#| ] ya que el sistema adm. 
			   VALERY lo utiliza como comando para identificar el tipo de tasa del producto
			*/
			*qpleng = bix.NCRegistroProducto(yytext, qprint);
			smStart->Check(Quorion::TKN_NC_REGISTRO_PRODUCTO,yytext,yyleng);
			}

{TKN_NC_ANULACION_ITEM}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.NCAnulacionITEM(yytext, qprint);
			smStart->Check(Quorion::TKN_NC_ANULACION_ITEM,yytext,yyleng);
			}

{TKN_NC_CIERRE_DEVOLUCION}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.NCCierreDevolucion(yytext, qprint);
			smStart->Check(Quorion::TKN_NC_CIERRE_DEVOLUCION,yytext,yyleng);
			}

{TKN_DNF_TEXTO}		{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//						
			*qpleng = bix.DNFTexto(yytext, qprint);
			smStart->Check(Quorion::TKN_DNF_TEXTO,yytext,yyleng);
			}

{TKN_DNF_APERTURA_GAVETA}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.DNFAperturaGaveta(yytext, qprint);
			smStart->Check(Quorion::TKN_DNF_APERTURA_GAVETA,yytext,yyleng);
			}

{TKN_DNF_PO_RA}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.DNF_PO_RA(yytext, qprint);
			smStart->Check(Quorion::TKN_DNF_PO_RA,yytext,yyleng);
			}

{TKN_DNF_FINALIZAR_PO_RA}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.DNFFinalizarPORA(yytext, qprint);
			smStart->Check(Quorion::TKN_DNF_FINALIZAR_PO_RA,yytext,yyleng);
			}

{TKN_DNF_PRINT_VALOR_CONF}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.DNFPrintValorConf(yytext, qprint);
			smStart->Check(Quorion::TKN_DNF_PRINT_VALOR_CONF,yytext,yyleng);
			}


{TKN_DISPLAY_MENSAJE}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.DisplayMensaje(yytext, qprint);
			smStart->Check(Quorion::TKN_DISPLAY_MENSAJE,yytext,yyleng);
			}

{TKN_STATUS}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.Status(yytext, qprint);
			smStart->Check(Quorion::TKN_STATUS,yytext,yyleng);
			}


{TKN_REPORTE_X}		{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ReporteX(yytext, qprint);
			smStart->Check(Quorion::TKN_REPORTE_X,yytext,yyleng);
			}

{TKN_REPORTE_Z}		{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ReporteZ(yytext, qprint);
			smStart->Check(Quorion::TKN_REPORTE_Z,yytext,yyleng);
			}

{TKN_REPORTE_MFISCAL_FECHA}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ReporteMFiscalFecha(yytext, qprint);
			smStart->Check(Quorion::TKN_REPORTE_MFISCAL_FECHA,yytext,yyleng);
			}

{TKN_REPORTE_MFISCAL_NUMERO}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ReporteMFiscalNumero(yytext, qprint);
			smStart->Check(Quorion::TKN_REPORTE_MFISCAL_NUMERO,yytext,yyleng);
			}

{TKN_REIMPRESION_DOC_POR_NUMERO}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ReimpresionDeDocPorNumero(yytext, qprint);
			smStart->Check(Quorion::TKN_REIMPRESION_DOC_POR_NUMERO,yytext,yyleng);
			}

{TKN_REIMPRESION_DOC_POR_FECHA}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.ReimpresionDeDocPorFecha(yytext, qprint);
			smStart->Check(Quorion::TKN_REIMPRESION_DOC_POR_FECHA,yytext,yyleng);
			}

{TKN_PRINT_EDO_MEMORIA_AUDITORIA}	{
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//
			*qpleng = bix.PrintEdoMemoriaAuditoria(yytext, qprint);
			smStart->Check(Quorion::TKN_PRINT_EDO_MEMORIA_AUDITORIA,yytext,yyleng);
			}

{TKN_OTRO_1}	{
			smStart->Check(Quorion::TKN_OTRO_1,yytext,yyleng);
			}

{TKN_OTRO_2}	{
			smStart->Check(Quorion::TKN_OTRO_2,yytext,yyleng);
			}

{TKN_OTRO_3}	{
			smStart->Check(Quorion::TKN_OTRO_3,yytext,yyleng);
			}

{TKN_OTRO_4}	{
			smStart->Check(Quorion::TKN_OTRO_4,yytext,yyleng);
			}			

{TKN_OTRO_5}	{
			smStart->Check(Quorion::TKN_OTRO_5,yytext,yyleng);
			}
				     
.           {
			*bxleng = yyleng;
			strncpy(bxtext, yytext, yyleng);
			//						
			printf( "Caracter No Reconocido: %s\n", yytext );
			}

%%

int Bixolonwrap()
{	
	return 1;
}

namespace Quorion {

	Protocol::Protocol(Printer *sm_print,::istream* in,
				::ostream* out)
			: BixolonFlexLexer(in, out)
	{
		//cmds = sm_print;
		//_printer = cmds;
		_printer = sm_print;
		smStart = new Quorion::SM_Inicial(sm_print);
		_smStart = smStart;

		_bxtext = (char*)malloc(1024*sizeof(char));
		memset(_bxtext, 0, 1024);
		bxtext = _bxtext;

		bxleng = &_bxleng;
		_bxleng = 0;

		_qprint = (char*)malloc(1024*sizeof(char));
		memset(_qprint, 0, 1024);
		qprint = _qprint;

		qpleng = &_qpleng;
		_qpleng = 0;
		//printf("Protocol\n");
	}

	Protocol::~Protocol()
	{
		free(_bxtext);
		free(_qprint);
		free(_smStart);
		//printf("free Protocol\n");
	}

	void Protocol::set_debug(bool b)
	{
		yy_flex_debug = b;
	}

	char* Protocol::YYText()
	{
		return _bxtext;
	}

	long Protocol::YYLeng()
	{
		return _bxleng;
	}

	char* Protocol::QPrint()
	{
		return _qprint;
	}

	long Protocol::QPLeng()
	{
		return _qpleng;
	}

	int Protocol::yywrap()
	{
		return 1;
	}

	int Protocol::QError()
	{
		return _printer->fncGetQError();
	}

	int Protocol::BStatus()
	{
		return _printer->fncGetBStatus();
	}
}
/*
int main(int argc, char** argv)
{	
	//++argv, --argc;  // skip over program name
	//if ( argc > 0 )
	//	yyin = fopen( argv[0], "r" );
	//else
	//	yyin = stdin;     
	//yylex();
	
	//yyFlexLexer Lexer;
	//Lexer.yylex();
	return 0;
}
*/
