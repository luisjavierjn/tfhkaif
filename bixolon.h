
#ifndef _BIXOLON_TRANSLATOR_H_
#define _BIXOLON_TRANSLATOR_H_

namespace Quorion {

class Bixolon
{
public:
    Bixolon();

    ~Bixolon();

	long ConfDatosDelCajero(char* trama_bx, char* trama_qp);

	long ConfNombresFormasDePagos(char* trama_bx, char* trama_qp);

	long ConfHora(char* trama_bx, char* trama_qp);

	long ConfFecha(char* trama_bx, char* trama_qp);

	long ConfDelIVA(char* trama_bx, char* trama_qp);
	
	long ConfDelIVAMemoriaFiscal(char* trama_bx, char* trama_qp);

	long ConfEncabezado(char* trama_bx, char* trama_qp);

	long ConfPieDeFactura(char* trama_bx, char* trama_qp);


	long CajeroInicio(char* trama_bx, char* trama_qp);

	long CajeroFin(char* trama_bx, char* trama_qp);

	long DatosDelCliente(char* trama_bx, char* trama_qp);

	long FactRegistroDeProducto(char* trama_bx, char* trama_qp);

	long FactDescripcionDeProducto(char* trama_bx, char* trama_qp);

	long FactCorreccion(char* trama_bx, char* trama_qp);

	long FactSubtotal(char* trama_bx, char* trama_qp);

	long FactRecargoODescuento(char* trama_bx, char* trama_qp);

	long FactAnulacionITEM(char* trama_bx, char* trama_qp);

	long FactAnulacionFactura(char* trama_bx, char* trama_qp);

	long FactPagoDirecto(char* trama_bx, char* trama_qp);

	long FactPagoParcial(char* trama_bx, char* trama_qp);

	long FactCodigoDeBarra(char* trama_bx, char* trama_qp);


	long NCRegistroProducto(char* trama_bx, char* trama_qp);

	long NCAnulacionITEM(char* trama_bx, char* trama_qp);

	long NCCierreDevolucion(char* trama_bx, char* trama_qp);


	long DNFTexto(char* trama_bx, char* trama_qp);

	long DNFAperturaGaveta(char* trama_bx, char* trama_qp);

	long DNF_PO_RA(char* trama_bx, char* trama_qp);

	long DNFFinalizarPORA(char* trama_bx, char* trama_qp);

	long DNFPrintValorConf(char* trama_bx, char* trama_qp);


	long DisplayMensaje(char* trama_bx, char* trama_qp);

	
	long Status(char* trama_bx, char* trama_qp);


	long ReporteX(char* trama_bx, char* trama_qp);

	long ReporteZ(char* trama_bx, char* trama_qp);

	long ReporteMFiscalFecha(char* trama_bx, char* trama_qp);

	long ReporteMFiscalNumero(char* trama_bx, char* trama_qp);

	long ReimpresionDeDocPorFecha(char* trama_bx, char* trama_qp);

	long ReimpresionDeDocPorNumero(char* trama_bx, char* trama_qp);

	long PrintEdoMemoriaAuditoria(char* trama_bx, char* trama_qp);
	
};

} // namespace Quorion

#endif // _BIXOLON_TRANSLATOR_H_