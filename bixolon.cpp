#include "bixolon.h"
#include <stdio.h>
#include <string.h>

namespace Quorion {

	Bixolon::Bixolon() {}

	Bixolon::~Bixolon() {}

	long Bixolon::ConfDatosDelCajero(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "ConfDatosDelCajero: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::ConfNombresFormasDePagos(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "ConfNombresFormasDePagos: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::ConfHora(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "ConfHora: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}
	
	long Bixolon::ConfFecha(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "ConfFecha: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::ConfDelIVA(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "ConfDelIVA: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::ConfDelIVAMemoriaFiscal(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "ConfDelIVAMemoriaFiscal BIXOLON: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}
	
	long Bixolon::ConfEncabezado(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "ConfEncabezado: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::ConfPieDeFactura(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "ConfPieDeFactura: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}
	
	long Bixolon::CajeroInicio(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "\nCajeroInicio: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::CajeroFin(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "CajeroFin: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}
	
	long Bixolon::DatosDelCliente(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "DatosDelCliente: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::FactRegistroDeProducto(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Fact RegistroDeProducto: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::FactDescripcionDeProducto(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Fact DescripcionDeProducto: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::FactCorreccion(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Fact Correccion: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::FactSubtotal(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Fact Subtotal: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::FactRecargoODescuento(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Fact Recargo o Descuento: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::FactAnulacionITEM(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Fact AnulacionITEM: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

		long Bixolon::FactAnulacionFactura(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Fact AnulacionFactura: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::FactPagoDirecto(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Fact PagoDirecto: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}
	
	long Bixolon::FactPagoParcial(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Fact PagoParcial: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::FactCodigoDeBarra(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Fact CodigoDeBarra: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}


	long Bixolon::NCRegistroProducto(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "NCRegistroProducto: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::NCAnulacionITEM(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "NCAnulacionITEM: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::NCCierreDevolucion(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "NCCierreDevolucion: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}



	long Bixolon::DNFTexto(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "\nDNF_Texto: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::DNFAperturaGaveta(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "DNF_AperturaGaveta: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::DNF_PO_RA(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "DNF_PO_RA: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::DNFFinalizarPORA(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "DNF_FinalizarPORA: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::DNFPrintValorConf(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "DNF_PrintValorConf: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::DisplayMensaje(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "\nDisplayMensaje: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::Status(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "\nStatus: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::ReporteX(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, "F3;1;1");
	//	printf( "\nReporte X: %s\n", trama_qp );
		return strlen(trama_qp);
	}

	long Bixolon::ReporteZ(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, "F3;1");
	//	printf( "Reporte Z: %s\n", trama_qp );
		return strlen(trama_qp);
	}

	long Bixolon::ReporteMFiscalFecha(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Reporte MFiscalFecha: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}
	
	long Bixolon::ReporteMFiscalNumero(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Reporte MFiscalNumero: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::ReimpresionDeDocPorFecha(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Reimpresion DeDocPorFecha: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::ReimpresionDeDocPorNumero(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Reimpresion DeDocPorNumero: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

	long Bixolon::PrintEdoMemoriaAuditoria(char* trama_bx, char* trama_qp)
	{
		strcpy(trama_qp, trama_bx); //esto no es traducción aún
	//	printf( "Impresion EstadoMemoriaAuditoria: %s\n", trama_qp ); 
		return strlen(trama_qp);
	}

}