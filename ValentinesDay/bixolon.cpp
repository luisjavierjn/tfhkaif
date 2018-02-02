#include "bixolon.h"
#include <stdio.h>
#include <string.h>

namespace Quorion {

	Bixolon::Bixolon() {}

	Bixolon::~Bixolon() {}

	long Bixolon::TextoEnDocumentoNoFiscal(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, "comando qprint");
		printf( "Texto en Documento No Fiscal: %s\n", trama_qp );
		return strlen(trama_qp);
	}

	long Bixolon::ReporteX(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, "F3;1;1");
		printf( "Reporte X: %s\n", trama_qp );
		return strlen(trama_qp);
	}

	long Bixolon::ReporteZ(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, "F3;1");
		printf( "Reporte Z: %s\n", trama_qp );
		return strlen(trama_qp);
	}
}