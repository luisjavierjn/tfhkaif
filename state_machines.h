
#ifndef _STATE_MACHINES_TRANSLATOR_H_
#define _STATE_MACHINES_TRANSLATOR_H_

#include "estados.h"
#include "printer.h"

namespace Quorion {


// Configuración Datos del Cajero
	class SM_Conf_Datos_Cajero
	{
	public:
		SM_Conf_Datos_Cajero();

		~SM_Conf_Datos_Cajero();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void ConfDatosCajero();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char *_buffer;
		char s1[1024];
		int i;
		int error;
	};

// Configuración Nombres de las Formas de Pago
	class SM_Conf_Nombres_Formas_De_Pago
	{
	public:
		SM_Conf_Nombres_Formas_De_Pago();

		~SM_Conf_Nombres_Formas_De_Pago();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void ConfNombresFormasPago();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char *_buffer;
		char s1[1024];
		char s2[1024];
		int error;
	};

// Configuración Hora
	class SM_Conf_Hora
	{
	public:
		SM_Conf_Hora();

		~SM_Conf_Hora();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void ConfHora();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		char s2[1024];
		char hora[1024];
		char fecha[1024];
		int len;
		int error;
	};

// Configuración Fecha
	class SM_Conf_Fecha
	{
	public:
		SM_Conf_Fecha();

		~SM_Conf_Fecha();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void ConfFecha();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		char s2[1024];
		char fecha[1024];
		char hora[1024];
		int len;
		int error;
	};

// Configuración del IVA
	class SM_Conf_del_IVA
	{
	public:
		SM_Conf_del_IVA();

		~SM_Conf_del_IVA();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void ConfIVA();
		void ConfIVAMemoriaFiscal();				
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		int error;
		char Tasa1[1024];
		char Tasa2[1024];
		char Tasa3[1024];
		char archivo[1024];
		
	};

// Configuración Encabezado
	class SM_Conf_Encabezado
	{
	public:
		SM_Conf_Encabezado();

		~SM_Conf_Encabezado();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void ConfEncabezado();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		int cont;
		int error;
	};

// Configuración Pie de Factura
	class SM_Conf_Pie_de_Factura
	{
	public:
		SM_Conf_Pie_de_Factura();

		~SM_Conf_Pie_de_Factura();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void ConfPieFactura();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		int cont;	
		int error;
	};

// Cajero Inicio
	class SM_Cajero_Inicio
	{
	public:
		SM_Cajero_Inicio();

		~SM_Cajero_Inicio();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void CajeroInicio();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		int error;
	};

// Cajero Fin
	class SM_Cajero_Fin
	{
	public:
		SM_Cajero_Fin();

		~SM_Cajero_Fin();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void CajeroFin();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
	};


// Factura
	class SM_Factura
	{
	public:
		SM_Factura();

		~SM_Factura();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

		void vari(int variable1, int variable2, char * descripcion);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void FactRegistroProducto();
		void FactDescripcionProducto();
		void FactCorreccion();
		void FactSubtotal();
		void FactRecargoODescuento();
		void FactCodigoBarra();
		void FactAnulacionITEM();
		void FactAnulacionFactura();
		void FactPagoDirecto();
		void FactPagoParcial();
		void FactStatus();
		void GenerarFactura();

		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		char s2[1024];
		char s3[1024];
		char s4[1024];
		int _vari1;
		int _vari2;

		// Registro
		char _x[1024];
		char _item[1024];
		int item;		
		int subtotal;
		int x;
		int y;
		int cont;
		int len_des;
		int cant;
		char * pch1;
		// Descripcion
		char descripcion[1024];
		char letra[5];
		// Recargo o Descuento
		char variable[4];
		char porcentaje[10];
		int error;
		char linea[30];
		int i;
		// Pago Parcial
		char BIG[10];
		char IVAG[10];
		char BIR[10];
		char IVAR[10];
		char BIA[10];
		char IVAA[10];
		char Exento[10];
		char cmd[10];
		char * pch;
		int _BIG;
		int _IVAG;
		int _BIR;
		int _IVAR;
		int _BIA;
		int _IVAA;
		int _Exento;
		int resto;
		
	};
	
// Nota de Credito
	class SM_Nota_de_Credito
	{
	public:
		SM_Nota_de_Credito();

		~SM_Nota_de_Credito();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

		void vari(int variable1, int variable2, char * descripcion);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void NCRegistroProducto();
		void NCDescripcionProducto();
		void NCSubtotal();
		void NCRecargoODescuento();
		void NCAnulacionITEM();
		void NCCierreDevolucion();
		void GenerarNotaCredito();

		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		char s2[1024];
		char _x[1024];
		char _item[1024];
		char descripcion[1024];
		int _vari;
		int _vari2;
		int x;
		int y;
		int item;
		int subtotal;
		int error;
		// Descripcion
		int len_des;
		int cont;
		int i;
		char linea[30];
		char letra[5];
		// Recargo o Descuento
		char variable[4];
		char porcentaje[10];
	};

// Datos de Cliente
	class SM_Datos_Cliente
	{
	public:
		SM_Datos_Cliente();

		~SM_Datos_Cliente();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

		void vari(int variable);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void DatosCliente(Accion param);
		void SMFactura();
		void SMNotaCredito();
		void SMDescripcionProducto();
		void EstadoInvalido();	

		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		char s2[1024];
		char * s3;
		char * s4;
		char * pch;
		char Serial[12];
		char cmd[10];
		char linea[200];
		char _linea[200];
		char cantidad[10];
		char encabezado[30];
		char comparar[30];
		char comparar1[30];
		int ii;
		int ii1;
		int _vari1;
		int _vari2;
		int error;
		int cont;
		int cont1;
		int bandera;
		int bandera1;
		int len;
		int cant1; int cant_1;
		int cant2; int cant_2;
		int cant3; int cant_3;
		int cant4; int cant_4;
		int cant5; int cant_5;
		int cant6; int cant_6;
		int cant7; int cant_7;
		int cant8; int cant_8;
		int cant9; int cant_9;
		
		char dato1[30]; char dato_1[30];
		char dato2[30]; char dato_2[30];
		char dato3[30]; char dato_3[30];
		char dato4[30]; char dato_4[30];
		char dato5[30]; char dato_5[30];
		char dato6[30]; char dato_6[30];
		char dato7[30]; char dato_7[30];
		char dato8[30]; char dato_8[30];
		char dato9[30]; char dato_9[30];

		char linea_NC[300];
		char linea_F[300];
		char datosclienteF[1024];
		char datoscliente[1024];
		char datosclienteNC[1024];
		char NCdatoscliente[1024];
		int cantidadF;
		int cantidadNC;

		char variable1[50];
		char variable2[50];
		char variable3[50];

		char descripcion[1024];

		SM_Nota_de_Credito smnc;
		SM_Factura smf;	
	};

// DNF Texto
	class SM_DNF_Texto
	{
	public:
		SM_DNF_Texto();

		~SM_DNF_Texto();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void DNFTexto();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char *_buffer;
		char s1[1024];
		int cont;
		int error;
	};

// DNF Apertura de Gaveta
	class SM_DNF_Apertura_Gaveta
	{
	public:
		SM_DNF_Apertura_Gaveta();

		~SM_DNF_Apertura_Gaveta();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void DNFAperturaGaveta();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		int error;
	};

// DNF PO (Fondo de Caja)
	class SM_DNF_PO_RA
	{
	public:
		SM_DNF_PO_RA();

		~SM_DNF_PO_RA();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void DNF_PO_RA();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		char s2[1024];
		char s3[1024];
		char _x[1024];
		int x;
		int error;
	};

// DNF Imprimir Valor Conf
	class SM_DNF_Valor_Conf
	{
	public:
		SM_DNF_Valor_Conf();

		~SM_DNF_Valor_Conf();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void DNFValorConf();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
	};

// DNF Codigo Barra
	class SM_DNF_Codigo_Barra
	{
	public:
		SM_DNF_Codigo_Barra();

		~SM_DNF_Codigo_Barra();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void DNFCodigoBarra();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		int error;
	};

// Display Mensaje
	class SM_Display_Mensaje
	{
	public:
		SM_Display_Mensaje();

		~SM_Display_Mensaje();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void DisplayMensaje();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];	
		int error;
	};

// Status
	class SM_Status
	{
	public:
		SM_Status();

		~SM_Status();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void Status();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];	
		int error;
	};

// Reporte X
	class SM_Reporte_X
	{
	public:
		SM_Reporte_X();

		~SM_Reporte_X();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void ReporteX();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char *_buffer;
		char s1[1024];
		int error;
	};

// Reporte Z
	class SM_Reporte_Z
	{
	public:
		SM_Reporte_Z();

		~SM_Reporte_Z();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void ReporteZ();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		int error;
	};

// Reporte Memoria Fiscal por Fecha
	class SM_MFiscal_Fecha
	{
	public:
		SM_MFiscal_Fecha();

		~SM_MFiscal_Fecha();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void MFiscalFecha();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		char s2[1024];
		int error;
	};

// Reporte Memoria Fiscal por Numero
	class SM_MFiscal_Numero
	{
	public:
		SM_MFiscal_Numero();

		~SM_MFiscal_Numero();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void MFiscalNumero();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		char s2[1024];
		int int1;
		int error;
	};

// Reimpresión de Documentos por Fecha
	class SM_Reimpresion_Fecha
	{
	public:
		SM_Reimpresion_Fecha();

		~SM_Reimpresion_Fecha();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void ReimpresionDocFecha();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		char s2[1024];
		int error;
	};

// Reimpresión de Documentos por Numero
	class SM_Reimpresion_Numero
	{
	public:
		SM_Reimpresion_Numero();

		~SM_Reimpresion_Numero();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print, char * buffer);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void ReimpresionDocNumero();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
		char * _buffer;
		char s1[1024];
		char s2[1024];
		int int1;
		int error;
	};

// Impresión de Estado de Memoria de Auditoria
	class SM_Print_Edo_MAuditoria
	{
	public:
		SM_Print_Edo_MAuditoria();

		~SM_Print_Edo_MAuditoria();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print);

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void EstadoInvalido();
		void PrintEdoMAuditoria();
		
		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;
		Printer *_print;
	};

// Inicial
	class SM_Inicial
	{
	public:
		SM_Inicial(Printer *print);

		~SM_Inicial();

		Eventos Check(Eventos evt, const char* trama, long num);

		void set_printer(Printer *print);

		int vari;

	private:
		Estados T(Estados initial_state, Eventos evento); 

		Eventos Ejecutar(Estados state);

		// Funciones
		void Inicio();
		void Fin();
		void SMConfDatosCajero();
		void SMConfNombresFormasPago();
		void SMConfHora();
		void SMConfFecha();
		void SMConfIva();
		void SMConfEncabezado();
		void SMConfPieDeFactura();
		void SMCajeroInicio();
		void SMCajeroFin();
		void SMDatos_cliente();
		void SMFactura();
		void SMNotaCredito();
		void SMDNFTexto();
		void SMDNFAperturaGaveta();
		void SMDNFPoRa();
		void SMDNFValorConf();
		void SMDNFCodigoBarra();
		void SMDisplayMensaje();
		void SMStatus();
		void SMReporteX();
		void SMReporteZ();
		void SMMFiscalFecha();
		void SMMFiscalNumero();
		void SMReimpresionFecha();
		void SMReimpresionNumero();
		void SMPrintEdoMAuditoria();
		void EstadoInvalido();		

		SM_Conf_Datos_Cajero smconfC;
		SM_Conf_Nombres_Formas_De_Pago smconfFP;
		SM_Conf_Hora smhora;
		SM_Conf_Fecha smfecha;
		SM_Conf_del_IVA smiva;
		SM_Conf_Encabezado smenca;
		SM_Conf_Pie_de_Factura smpie;

		SM_Cajero_Inicio smcajeroI;
		SM_Cajero_Fin smcajeroF;
		SM_Datos_Cliente smdc;
		SM_Factura smfactura;
		SM_Nota_de_Credito smnotacredito;

		SM_DNF_Texto smdnftex;
		SM_DNF_Apertura_Gaveta smdnfaper;
		SM_DNF_PO_RA smdnfPORA;
		SM_DNF_Valor_Conf smdnfconf;
		SM_DNF_Codigo_Barra smdnfcodigo;

		SM_Display_Mensaje smdisplay;
		SM_Status smstatus;

		SM_Reporte_X smRX;
		SM_Reporte_Z smRZ;
		SM_MFiscal_Fecha smMFecha;
		SM_MFiscal_Numero smMFnum;
		SM_Reimpresion_Fecha smreimpreF;
		SM_Reimpresion_Numero smreimpreN;
		SM_Print_Edo_MAuditoria smEdoMA;
		

		Eventos Evento_Actual;
		// Estado en Proceso
		Estados Estado_Actual;	
		Estados Estado_Previo;

		const char* _trama;
		long _num;	
		Printer *_print;
		char *_buffer;
	};

} // namespace Quorion

#endif // _STATE_MACHINES_TRANSLATOR_H__