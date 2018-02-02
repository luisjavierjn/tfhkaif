#include <iostream>
#include <fstream>
#include <stdio.h>
#include "state_machines.h"

namespace Quorion {

// Máquina de Estado Inicial
	SM_Inicial::SM_Inicial(Printer *print)
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
		_buffer = (char*)malloc(1024*sizeof(char));
		_print = print;
		
		smconfC.set_printer(print, _buffer);
		smconfFP.set_printer(print, _buffer);
		smhora.set_printer(print, _buffer);
		smfecha.set_printer(print, _buffer);
		smiva.set_printer(print, _buffer);
		smenca.set_printer(print, _buffer);
		smpie.set_printer(print, _buffer);

		smcajeroI.set_printer(print, _buffer);
		smcajeroF.set_printer(print);
		smdc.set_printer(print, _buffer);
		smfactura.set_printer(print, _buffer);
		smnotacredito.set_printer(print, _buffer);

		smdnftex.set_printer(print, _buffer);
		smdnfaper.set_printer(print, _buffer);
		smdnfPORA.set_printer(print, _buffer);
		smdnfconf.set_printer(print);
		smdnfcodigo.set_printer(print, _buffer);

		smdisplay.set_printer(print, _buffer);
		smstatus.set_printer(print, _buffer);

		smRX.set_printer(print, _buffer);
		smRZ.set_printer(print, _buffer);
		smMFecha.set_printer(print, _buffer);
		smMFnum.set_printer(print, _buffer);
		smreimpreF.set_printer(print, _buffer);
		smreimpreN.set_printer(print, _buffer);
		smEdoMA.set_printer(print);
	}

    SM_Inicial::~SM_Inicial()
	{
		//free(_buffer);
	}

	Eventos SM_Inicial::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;
		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Inicial::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 

		{
			case EDO_INICIO:
				if(evento == TKN_CONF_DATOS_DEL_CAJERO) return EDO_SM_CONF_DATOS_CAJERO;
				if(evento == TKN_CONF_NOMBRES_FORMAS_DE_PAGO) return EDO_SM_CONF_NOMBRES_FORMAS_DE_PAGO;
				if(evento == TKN_CONF_HORA) return EDO_SM_CONF_HORA;
				if(evento == TKN_CONF_FECHA) return EDO_SM_CONF_FECHA;
				if(evento == TKN_CONF_DEL_IVA) return EDO_SM_CONF_DEL_IVA;
				if(evento == TKN_CONF_ENCABEZADO) return EDO_SM_CONF_ENCABEZADO;
				if(evento == TKN_CONF_PIE_DE_FACTURA) return EDO_SM_CONF_PIE_DE_FACTURA;
				if(evento == TKN_CAJERO_INICIO) return EDO_SM_CAJERO_INICIO;
				if(evento == TKN_CAJERO_FIN) return EDO_SM_CAJERO_FIN;
				if(evento == TKN_DATOS_CLIENTE) return EDO_SM_DATOS_CLIENTE;
				if(evento == TKN_FACT_DESCRIPCION_PRODUCTO) return EDO_SM_FACTURA;
				if(evento == TKN_FACT_REGISTRO_PRODUCTO) return EDO_SM_FACTURA;
				if(evento == TKN_NC_REGISTRO_PRODUCTO) return EDO_SM_NOTA_DE_CREDITO;
				if(evento == TKN_DNF_TEXTO) return EDO_SM_DNF_TEXTO;
				if(evento == TKN_DNF_APERTURA_GAVETA) return EDO_SM_DNF_APERTURA_GAVETA;
				if(evento == TKN_DNF_PO_RA) return EDO_SM_DNF_PO_RA;
				if(evento == TKN_DNF_PRINT_VALOR_CONF) return EDO_SM_DNF_VALOR_CONF;
				if(evento == TKN_FACT_CODIGO_DE_BARRA) return EDO_SM_DNF_CODIGO_BARRA;
				if(evento == TKN_DISPLAY_MENSAJE) return EDO_SM_DISPLAY_MENSAJE;
				if(evento == TKN_STATUS) return EDO_SM_STATUS;
				if(evento == TKN_REPORTE_X) return EDO_SM_REPORTE_X;
				if(evento == TKN_REPORTE_Z) return EDO_SM_REPORTE_Z;
				if(evento == TKN_REPORTE_MFISCAL_FECHA) return EDO_SM_MFISCAL_FECHA;
				if(evento == TKN_REPORTE_MFISCAL_NUMERO) return EDO_SM_MFISCAL_NUMERO;
				if(evento == TKN_REIMPRESION_DOC_POR_FECHA) return EDO_SM_REIMPRESION_FECHA;
				if(evento == TKN_REIMPRESION_DOC_POR_NUMERO) return EDO_SM_REIMPRESION_NUMERO;
				if(evento == TKN_PRINT_EDO_MEMORIA_AUDITORIA) return EDO_SM_PRINT_EDO_MAUDITORIA;
				break;
			case EDO_SM_CONF_DATOS_CAJERO:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_CONF_DATOS_CAJERO;
				break;
			case EDO_SM_CONF_NOMBRES_FORMAS_DE_PAGO:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_CONF_NOMBRES_FORMAS_DE_PAGO;
				break;
			case EDO_SM_CONF_HORA:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_CONF_HORA;
				break;
			case EDO_SM_CONF_FECHA:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_CONF_FECHA;
				break;
			case EDO_SM_CONF_DEL_IVA:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_CONF_DEL_IVA;
				break;
			case EDO_SM_CONF_ENCABEZADO:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_CONF_ENCABEZADO;
				break;
			case EDO_SM_CONF_PIE_DE_FACTURA:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_CONF_PIE_DE_FACTURA;
				break;
			case EDO_SM_CAJERO_INICIO:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_CAJERO_INICIO;
				break;
			case EDO_SM_CAJERO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_CAJERO_FIN;
				break;
			case EDO_SM_DATOS_CLIENTE:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_DATOS_CLIENTE;
				break;
			case EDO_SM_FACTURA:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_FACTURA;
				break;
			case EDO_SM_NOTA_DE_CREDITO:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_NOTA_DE_CREDITO;
				break;
			case EDO_SM_DNF_TEXTO:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_DNF_TEXTO;
				break;
			case EDO_SM_DNF_APERTURA_GAVETA:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_DNF_APERTURA_GAVETA;
				break;
			case EDO_SM_DNF_PO_RA:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_DNF_PO_RA;
				break;
			case EDO_SM_DNF_VALOR_CONF:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_DNF_VALOR_CONF;
				break;
			case EDO_SM_DNF_CODIGO_BARRA:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_DNF_CODIGO_BARRA;
				break;
			case EDO_SM_DISPLAY_MENSAJE:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_DISPLAY_MENSAJE;
				break;
			case EDO_SM_STATUS:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_STATUS;
				break;
			case EDO_SM_REPORTE_X:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_REPORTE_X;
				break;
			case EDO_SM_REPORTE_Z:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_REPORTE_X;
				break;
			case EDO_SM_MFISCAL_FECHA:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_MFISCAL_FECHA;
				break;
			case EDO_SM_MFISCAL_NUMERO:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_MFISCAL_NUMERO;
				break;
			case EDO_SM_REIMPRESION_FECHA:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_REIMPRESION_FECHA;
				break;
			case EDO_SM_REIMPRESION_NUMERO:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_REIMPRESION_NUMERO;
				break;
			case EDO_SM_PRINT_EDO_MAUDITORIA:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_PRINT_EDO_MAUDITORIA;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Inicial::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_SM_CONF_DATOS_CAJERO: SMConfDatosCajero(); break;
			case EDO_SM_CONF_NOMBRES_FORMAS_DE_PAGO: SMConfNombresFormasPago(); break;
			case EDO_SM_CONF_HORA: SMConfHora(); break;
			case EDO_SM_CONF_FECHA: SMConfFecha(); break;
			case EDO_SM_CONF_DEL_IVA: SMConfIva(); break;
			case EDO_SM_CONF_ENCABEZADO: SMConfEncabezado(); break;
			case EDO_SM_CONF_PIE_DE_FACTURA: SMConfPieDeFactura(); break;
			case EDO_SM_CAJERO_INICIO: SMCajeroInicio(); break;
			case EDO_SM_CAJERO_FIN: SMCajeroFin(); break;
			case EDO_SM_DATOS_CLIENTE: SMDatos_cliente(); break;
			case EDO_SM_FACTURA: SMFactura(); break;
			case EDO_SM_NOTA_DE_CREDITO: SMNotaCredito(); break;
			case EDO_SM_DNF_TEXTO: SMDNFTexto(); break;
			case EDO_SM_DNF_APERTURA_GAVETA: SMDNFAperturaGaveta(); break;
			case EDO_SM_DNF_PO_RA: SMDNFPoRa(); break;
			case EDO_SM_DNF_VALOR_CONF: SMDNFValorConf(); break;
			case EDO_SM_DNF_CODIGO_BARRA: SMDNFCodigoBarra(); break;
			case EDO_SM_DISPLAY_MENSAJE: SMDisplayMensaje(); break;
			case EDO_SM_STATUS: SMStatus(); break;
			case EDO_SM_REPORTE_X: SMReporteX(); break;
			case EDO_SM_REPORTE_Z: SMReporteZ(); break;
			case EDO_SM_MFISCAL_FECHA: SMMFiscalFecha(); break;
			case EDO_SM_MFISCAL_NUMERO: SMMFiscalNumero(); break;
			case EDO_SM_REIMPRESION_FECHA: SMReimpresionFecha(); break;
			case EDO_SM_REIMPRESION_NUMERO: SMReimpresionNumero(); break;
			case EDO_SM_PRINT_EDO_MAUDITORIA: SMPrintEdoMAuditoria(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		
		return Evento_Actual;
	}

	void SM_Inicial::Inicio()
	{
		printf("\n");
		printf("Inicio SM_Inicial\n");
	}

	void SM_Inicial::SMConfDatosCajero()
	{
		if(smconfC.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMConfNombresFormasPago()
	{
		if(smconfFP.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMConfHora()
	{
		if(smhora.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMConfFecha()
	{
		if(smfecha.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMConfIva()
	{
		if(smiva.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMConfEncabezado()
	{
		Eventos evt = Evento_Actual;

		if(smenca.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
			Ejecutar(T(Estado_Actual,evt));
		}
	}

	void SM_Inicial::SMConfPieDeFactura()
	{
		Eventos evt = Evento_Actual;

		if(smpie.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
			Ejecutar(T(Estado_Actual,evt));
		}
	}

	void SM_Inicial::SMCajeroInicio()
	{
		if(smcajeroI.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMCajeroFin()
	{
		if(smcajeroF.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMDatos_cliente()
	{
		Eventos evt = Evento_Actual;

		if(smdc.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMFactura()
	{
		Eventos evt = Evento_Actual;

		if(smfactura.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMNotaCredito()
	{
		Eventos evt = Evento_Actual;

		if(smnotacredito.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMDNFTexto()
	{
		Eventos evt = Evento_Actual;

		if(smdnftex.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
			Ejecutar(T(Estado_Actual,evt));
		}
	}

	void SM_Inicial::SMDNFAperturaGaveta()
	{
		if(smdnfaper.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMDNFPoRa()
	{
		if(smdnfPORA.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}
	
	void SM_Inicial::SMDNFValorConf()
	{
		if(smdnfconf.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMDNFCodigoBarra()
	{
		if(smdnfcodigo.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMDisplayMensaje()
	{
		if(smdisplay.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMStatus()
	{
		if(smstatus.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMReporteX()
	{
		if(smRX.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMReporteZ()
	{
		if(smRZ.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMMFiscalFecha()
	{
		if(smMFecha.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMMFiscalNumero()
	{
		if(smMFnum.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}
	
	void SM_Inicial::SMReimpresionFecha()
	{
		if(smreimpreF.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}
	
	void SM_Inicial::SMReimpresionNumero()
	{
		if(smreimpreN.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Inicial::SMPrintEdoMAuditoria()
	{
		if(smEdoMA.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}	

	void SM_Inicial::Fin()
	{
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Inicial::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}
	
//CONFIGURACIÓN
	
// Conf Datos del Cajero
	SM_Conf_Datos_Cajero::SM_Conf_Datos_Cajero()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_Conf_Datos_Cajero::~SM_Conf_Datos_Cajero()
	{
	}

	void SM_Conf_Datos_Cajero::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_Conf_Datos_Cajero::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Conf_Datos_Cajero::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_CONF_DATOS_DEL_CAJERO) return EDO_CONF_DATOS_DEL_CAJERO;
				break;
			case EDO_CONF_DATOS_DEL_CAJERO:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Conf_Datos_Cajero::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_CONF_DATOS_DEL_CAJERO: ConfDatosCajero(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}

		return Evento_Actual;
	}

	void SM_Conf_Datos_Cajero::Inicio()
	{
		//printf("Inicio SM_Conf_Datos_Cajero\n");
	}

	void SM_Conf_Datos_Cajero::ConfDatosCajero()
	{
		printf("ConfDatosCajero\n");

		strcpy(s1,"");
		strcat(s1,"F2;8;");
		strncat(s1,&_trama[3],1);
		//strcat(s1,";");			Trama para Clave
		//strcat(s1,";1;\"");
		//strncat(s1,&_trama[4],5);
		strcat(s1,";;\"");
		strncat(s1,&_trama[9],(_num - 9));
		strcat(s1,"\";");
		
		printf(" QPrint, Datos de Cajero: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);	
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "ConfDatosCajero", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Conf_Datos_Cajero::Fin()
	{
		printf("Fin SM_Conf_Datos_Cajero\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Conf_Datos_Cajero::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Conf Nombres de Formas de Pago
	SM_Conf_Nombres_Formas_De_Pago::SM_Conf_Nombres_Formas_De_Pago()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_Conf_Nombres_Formas_De_Pago::~SM_Conf_Nombres_Formas_De_Pago()
	{
	}

	void SM_Conf_Nombres_Formas_De_Pago::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_Conf_Nombres_Formas_De_Pago::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Conf_Nombres_Formas_De_Pago::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_CONF_NOMBRES_FORMAS_DE_PAGO) return EDO_CONF_NOMBRES_FORMAS_DE_PAGO;
				break;
			case EDO_CONF_NOMBRES_FORMAS_DE_PAGO:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Conf_Nombres_Formas_De_Pago::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_CONF_NOMBRES_FORMAS_DE_PAGO: ConfNombresFormasPago(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Conf_Nombres_Formas_De_Pago::Inicio()
	{
		//printf("Inicio SM_Conf_Nombres_Formas_De_Pago\n");
	}

	void SM_Conf_Nombres_Formas_De_Pago::ConfNombresFormasPago()
	{
		printf("ConfNombresFormasPago\n");
		memset(s1,0,1024);
		memset(s2,0,1024);
		strcpy(s1, "F2;2;;");
		strncat(s2, &_trama[2], 2);
				
		if (strcmp(s2, "01") == 0) strcat(s1, "1;\"");
		if (strcmp(s2, "02") == 0) strcat(s1, "2;\""); 
		if (strcmp(s2, "03") == 0) strcat(s1, "3;\""); 
		if (strcmp(s2, "04") == 0) strcat(s1, "4;\""); 
/*
		if (strcmp(s2, "05") == 0) Ejecutar(T(Estado_Actual,EVT_NEUTRO));
		if (strcmp(s2, "06") == 0) Ejecutar(T(Estado_Actual,EVT_NEUTRO));
		if (strcmp(s2, "07") == 0) Ejecutar(T(Estado_Actual,EVT_NEUTRO)); 
		if (strcmp(s2, "08") == 0) Ejecutar(T(Estado_Actual,EVT_NEUTRO));
		if (strcmp(s2, "09") == 0) Ejecutar(T(Estado_Actual,EVT_NEUTRO));
		if (strcmp(s2, "10") == 0) Ejecutar(T(Estado_Actual,EVT_NEUTRO));
		if (strcmp(s2, "11") == 0) Ejecutar(T(Estado_Actual,EVT_NEUTRO)); 
		if (strcmp(s2, "12") == 0) Ejecutar(T(Estado_Actual,EVT_NEUTRO));
		if (strcmp(s2, "13") == 0) Ejecutar(T(Estado_Actual,EVT_NEUTRO)); 
		if (strcmp(s2, "14") == 0) Ejecutar(T(Estado_Actual,EVT_NEUTRO)); 
		if (strcmp(s2, "15") == 0) Ejecutar(T(Estado_Actual,EVT_NEUTRO));
		if (strcmp(s2, "16") == 0) Ejecutar(T(Estado_Actual,EVT_NEUTRO));
*/		
		if ((strcmp(s2, "01") == 0) || (strcmp(s2, "02") == 0) || (strcmp(s2, "03") == 0) || (strcmp(s2, "04") == 0))
		{
			printf("Adentro\n");
			strncat(s1, &_trama[4], (_num - 4));
			strcat(s1, "\""); 
			printf(" QPrint, Conf Forma de Pago: %s\n", s1);

			memset(_buffer,0,1024);
			error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
			printf("buffer: %s\n",_buffer);	

			if (error == 6) error = 0;
			_print->fncAnalyzeStatus(error, _buffer);
			_print->fncRegistrarLog(error, "ConfNombresFormasPago", s1);
		}

		printf("Afuera\n");

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Conf_Nombres_Formas_De_Pago::Fin()
	{
		printf("Fin SM_Conf_Nombres_Formas_De_Pago\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Conf_Nombres_Formas_De_Pago::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Conf Hora
	SM_Conf_Hora::SM_Conf_Hora()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_Conf_Hora::~SM_Conf_Hora()
	{
	}

	void SM_Conf_Hora::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_Conf_Hora::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Conf_Hora::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;
		
		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_CONF_HORA) return EDO_CONF_HORA;
				break;
			case EDO_CONF_HORA:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Conf_Hora::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_CONF_HORA: ConfHora(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Conf_Hora::Inicio()
	{
		//printf("Inicio SM_Conf_Hora\n");
	}

	void SM_Conf_Hora::ConfHora()
	{
		printf("ConfHora\n");

		memset(s1, 0, 1024);
		memset(s2, 0, 1024);
		memset(fecha, 0, 1024);
		memset(hora, 0, 1024);

		strcat(s1, "T");
		strncat(hora,&_trama[2],(_num - 2));
		strcat(s1, hora);

		strcpy(s2, "F0;1");
		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s2[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);	
		_print->fncRegistrarLog(error, "ConfHora", s1);
		
		len = strlen(_buffer);
		strcpy(fecha, "");
		strncat(fecha,&_buffer[len - 16],2);
		strncat(fecha,&_buffer[len - 13],2);
		strncat(fecha,&_buffer[len - 10],4);
		strcat(s1, fecha);

		printf(" QPrint, Configuracion Hora: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, "conf");
		_print->fncRegistrarLog(error, "ConfHora", s1);
	
		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Conf_Hora::Fin()
	{
		printf("Fin SM_Conf_Hora\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Conf_Hora::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}


// Conf Fecha
	SM_Conf_Fecha::SM_Conf_Fecha()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_Conf_Fecha::~SM_Conf_Fecha()
	{
	}

	void SM_Conf_Fecha::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_Conf_Fecha::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Conf_Fecha::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;
		
		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_CONF_FECHA) return EDO_CONF_FECHA;
				break;
			case EDO_CONF_FECHA:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Conf_Fecha::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_CONF_FECHA: ConfFecha(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Conf_Fecha::Inicio()
	{
		//printf("Inicio SM_Conf_Fecha\n");
	}

	void SM_Conf_Fecha::ConfFecha()
	{
		printf("ConfFecha\n");

		memset(s1, 0, 1024);
		memset(s2, 0, 1024);
		memset(fecha, 0, 1024);
		memset(hora, 0, 1024);

		//Status F0;1
		strcpy(s2, "F0;1");
		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s2[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("status: %s\n",_buffer);	
		//_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "ConfFecha", s1);
		
		len = strlen(_buffer);
		strcpy(hora, "");
		strncat(hora,&_buffer[len - 5],2);
		strncat(hora,&_buffer[len - 2],2);
		strcat(hora, "00");
		
		strcpy(s1, "");
		strcat(s1, "T");
		strcat(s1, hora);
		strncat(s1,&_trama[2],4);
		strcat(s1, "20");
		strncat(s1,&_trama[6],(_num - 6));

		printf(" QPrint, Configuracion Fecha: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, "conf");
		_print->fncRegistrarLog(error, "ConfFecha", s1);
	
		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Conf_Fecha::Fin()
	{
		printf("Fin SM_Conf_Fecha\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Conf_Fecha::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Conf Alícuotas de IVA
	SM_Conf_del_IVA::SM_Conf_del_IVA()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;		
	}

    SM_Conf_del_IVA::~SM_Conf_del_IVA()
	{
	}

	void SM_Conf_del_IVA::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_Conf_del_IVA::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Conf_del_IVA::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_CONF_DEL_IVA) return EDO_CONF_DEL_IVA;
				break;
			case EDO_CONF_DEL_IVA:
				if(evento == TKN_CONF_DEL_IVA) return EDO_CONF_DEL_IVA;
				if(evento == TKN_CONF_DEL_IVA_MEMORIA_FISCAL) return EDO_CONF_DEL_IVA_MEMORIA_FISCAL;
				if(evento == EVT_FIN_CONF_DEL_IVA) return EDO_FIN;
				break;
			case EDO_CONF_DEL_IVA_MEMORIA_FISCAL:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Conf_del_IVA::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_CONF_DEL_IVA: ConfIVA(); break;
			case EDO_CONF_DEL_IVA_MEMORIA_FISCAL: ConfIVAMemoriaFiscal(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Conf_del_IVA::Inicio()
	{
		//printf("Inicio SM_Conf_del_IVA\n");
	}

	void SM_Conf_del_IVA::ConfIVA()
	{
		printf("ConfIVA\n");

		memset(Tasa1,0,1024);
		memset(Tasa2,0,1024);
		memset(Tasa3,0,1024);
		memset(archivo,0,1024);

	//	strcpy(s1, "F4;4;\"4711\";\"");
		strcpy(s1, "F4;4;\"");
		strncat(Tasa1,&_trama[3],4);		//Tasa 1
		strcat(s1, Tasa1);
		strcat(s1, "\";\"");
		strncat(Tasa2,&_trama[8],4);		//Tasa 2
		strcat(s1, Tasa2);
		strcat(s1, "\";\"");
		strncat(Tasa3,&_trama[13],4);		//Tasa 3
		strcat(s1, Tasa3);
		strcat(s1, "\";\"0\";");

		printf(" QPrint, Configuracion IVA: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		printf("error: %i\n",error);
		_print->fncAnalyzeStatus(error, "conf");
		_print->fncRegistrarLog(error, "ConfIVA", s1);

		if (error == 0)
		{
			strcpy(archivo, "QPrint\\alicuotas.ini");
			FILE *destino = fopen(archivo,"w");
			fprintf(destino, "[Impuestos]\n%s	%s	%s\n", Tasa1, Tasa2, Tasa3);
			fclose(destino);
		}

		Ejecutar(T(Estado_Actual,EVT_FIN_CONF_DEL_IVA));
	}

	void SM_Conf_del_IVA::ConfIVAMemoriaFiscal()
	{
		printf("ConfIVAMemoriaFiscal\n");

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Conf_del_IVA::Fin()
	{
		printf("Fin SM_Conf_del_IVA\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Conf_del_IVA::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Conf Encabezado
	SM_Conf_Encabezado::SM_Conf_Encabezado()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
		cont = 0;
	}

    SM_Conf_Encabezado::~SM_Conf_Encabezado()
	{
	}

	void SM_Conf_Encabezado::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_Conf_Encabezado::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Conf_Encabezado::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_CONF_ENCABEZADO) return EDO_CONF_ENCABEZADO;
				break;
			case EDO_CONF_ENCABEZADO:
				if(evento == TKN_CONF_ENCABEZADO) return EDO_CONF_ENCABEZADO;
				else 
				{
					printf("QPrint, Conf Encabezado: U5;1\n");
					strcpy(s1, "U5;1");
					memset(_buffer,0,1024);
					error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
					printf("buffer: %s\n",_buffer);
					//_print->fncAnalyzeStatus(error, _buffer);
					_print->fncRegistrarLog(error, "ConfEncabezado", s1);
					cont = 0; 
				
					return EDO_FIN;
				}
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Conf_Encabezado::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_CONF_ENCABEZADO: ConfEncabezado(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Conf_Encabezado::Inicio()
	{
		printf("Inicio SM_Conf_Encabezado\n");
	}

	void SM_Conf_Encabezado::ConfEncabezado()
	{
		printf("ConfEncabezado\n");	
		
		if (cont == 0) 
		{
			printf("QPrint, Conf Encabezado: U5;1\n");
			strcpy(s1, "U5;1");
			memset(_buffer,0,1024);
			error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
			printf("buffer: %s\n",_buffer);
			printf("error: %i\n",error);
			//_print->fncAnalyzeStatus(error, _buffer);
			_print->fncRegistrarLog(error, "ConfEncabezado", s1);
			++cont;
		}
	
		strcpy(s1, "U8;");
		strncat(s1, &_trama[3], 1);
		strcat(s1, ";0;\"");
		strncat(s1, &_trama[4], (_num - 4));
		strcat(s1, "\"");
		printf(" QPrint, Conf Encabezado: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, "conf");
		_print->fncRegistrarLog(error, "ConfEncabezado", s1);
	}

	void SM_Conf_Encabezado::Fin()
	{
		printf("Fin SM_Conf_Encabezado\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Conf_Encabezado::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Conf Pie de Factura
	SM_Conf_Pie_de_Factura::SM_Conf_Pie_de_Factura()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
		cont = 0;
	}

    SM_Conf_Pie_de_Factura::~SM_Conf_Pie_de_Factura()
	{
	}

	void SM_Conf_Pie_de_Factura::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_Conf_Pie_de_Factura::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Conf_Pie_de_Factura::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_CONF_PIE_DE_FACTURA) return EDO_CONF_PIE_DE_FACTURA;
				break;
			case EDO_CONF_PIE_DE_FACTURA:
				if(evento == TKN_CONF_PIE_DE_FACTURA) return EDO_CONF_PIE_DE_FACTURA;
				else 				
				{
					printf("QPrint, Conf Pie de Factura: U5;1\n");
					strcpy(s1, "U5;1");
					memset(_buffer,0,1024);
					_print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
					printf("buffer: %s\n",_buffer);
					//_print->fncAnalyzeStatus(error, _buffer);
					_print->fncRegistrarLog(error, "ConfEncabezado", s1);
					cont = 0; 
				
					return EDO_FIN;
				}
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Conf_Pie_de_Factura::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_CONF_PIE_DE_FACTURA: ConfPieFactura(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Conf_Pie_de_Factura::Inicio()
	{
		//printf("Inicio SM_Conf_Pie_de_Factura\n");
	}

	void SM_Conf_Pie_de_Factura::ConfPieFactura()
	{
		printf("ConfPieFactura\n");

		if (cont == 0) 
		{
			printf("QPrint, Conf Pie de Factura: U5;1\n");
			strcpy(s1, "U5;1");
			memset(_buffer,0,1024);
			error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
			printf("buffer: %s\n",_buffer);
			//_print->fncAnalyzeStatus(error, "conf");
			_print->fncRegistrarLog(error, "ConfPieFactura", s1);
			++cont;
		}
	
		strcpy(s1, "");
		strcpy(s1, "U9;");
		strncat(s1, &_trama[3], 1);
		strcat(s1, ";0;\"");
		strncat(s1, &_trama[4], (_num - 4));
		strcat(s1, "\"");
		printf(" QPrint, Conf Pie de Factura: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, "conf");
		_print->fncRegistrarLog(error, "ConfPieFactura", s1);
	}

	void SM_Conf_Pie_de_Factura::Fin()
	{
		printf("Fin SM_Conf_Pie_de_Factura\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Conf_Pie_de_Factura::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Cajero Inicio
	SM_Cajero_Inicio::SM_Cajero_Inicio()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_Cajero_Inicio::~SM_Cajero_Inicio()
	{
	}

	void SM_Cajero_Inicio::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_Cajero_Inicio::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Cajero_Inicio::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_CAJERO_INICIO) return EDO_CAJERO_INICIO;
				break;
			case EDO_CAJERO_INICIO:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Cajero_Inicio::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_CAJERO_INICIO: CajeroInicio(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Cajero_Inicio::Inicio()
	{
		//printf("Inicio SM_Cajero_Inicio\n");
	}

	void SM_Cajero_Inicio::CajeroInicio()
	{
		printf("CajeroInicio\n");

		strcpy(s1, "F2;8;1;");
		strncat(s1, &_trama[1], (_num - 1));
		strcat(s1, ";");
		printf(" QPrint, Cajero Inicio: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "CajeroInicio", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Cajero_Inicio::Fin()
	{
		printf("Fin SM_Cajero_Inicio\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Cajero_Inicio::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Cajero Fin
	SM_Cajero_Fin::SM_Cajero_Fin()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_Cajero_Fin::~SM_Cajero_Fin()
	{
	}

	void SM_Cajero_Fin::set_printer(Printer *print)
	{
		_print = print;
	}

	Eventos SM_Cajero_Fin::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}
	
	Estados SM_Cajero_Fin::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_CAJERO_FIN) return EDO_CAJERO_FIN;
				break;
			case EDO_CAJERO_FIN:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Cajero_Fin::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_CAJERO_FIN: CajeroFin(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Cajero_Fin::Inicio()
	{
		//printf("Inicio SM_Cajero_Fin\n");
	}

	void SM_Cajero_Fin::CajeroFin()
	{
		printf("CajeroFin\n");

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Cajero_Fin::Fin()
	{
		printf("Fin SM_Cajero_Fin\n");

		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Cajero_Fin::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Datos Cliente
	SM_Datos_Cliente::SM_Datos_Cliente()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
		ii1 = 0;
		ii = 0;
		_vari1 = 0;
		_vari2 = 0;
		cont = 0;
		cont1 = 0;
		bandera = 1;
		bandera1 = 1;
		memset(datoscliente,0,1024);
		memset(datosclienteF,0,1024);
		memset(datosclienteNC,0,1024);
		memset(NCdatoscliente,0,1024);
		memset(s1,0,1024);
		memset(s2,0,1024);
		memset(comparar,0,30);
		memset(comparar1,0,30);
		memset(dato1, 0, 30); memset(dato_1, 0, 30);
		memset(dato2, 0, 30); memset(dato_2, 0, 30);
		memset(dato3, 0, 30); memset(dato_3, 0, 30);
		memset(dato4, 0, 30); memset(dato_4, 0, 30);
		memset(dato5, 0, 30); memset(dato_5, 0, 30);
		memset(dato6, 0, 30); memset(dato_6, 0, 30);
		memset(dato7, 0, 30); memset(dato_7, 0, 30);
		memset(dato8, 0, 30); memset(dato_8, 0, 30);
		memset(dato9, 0, 30); memset(dato_9, 0, 30);
		cant1 = 0; cant_1 = 0;
		cant2 = 0; cant_2 = 0;
		cant3 = 0; cant_3 = 0;
		cant4 = 0; cant_4 = 0;
		cant5 = 0; cant_5 = 0;
		cant6 = 0; cant_6 = 0;
		cant7 = 0; cant_7 = 0;
		cant8 = 0; cant_8 = 0;
		cant9 = 0; cant_9 = 0;
		memset(descripcion, 0, 1024);
	}

    SM_Datos_Cliente::~SM_Datos_Cliente()
	{
	}

	void SM_Datos_Cliente::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;

		smf.set_printer(_print, _buffer);
		smnc.set_printer(_print, _buffer);
	}

	Eventos SM_Datos_Cliente::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Datos_Cliente::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_DATOS_CLIENTE) return EDO_DATOS_CLIENTE;
				break;
			case EDO_DATOS_CLIENTE:
				if(evento == TKN_FACT_REGISTRO_PRODUCTO) { DatosCliente(ACC_OUT); return EDO_SM_FACTURA; }
				if(evento == TKN_NC_REGISTRO_PRODUCTO) { DatosCliente(ACC_OUT); return EDO_SM_NOTA_DE_CREDITO; }
				if(evento == TKN_FACT_DESCRIPCION_PRODUCTO) return EDO_DESCRIPCION_PRODUCTO;
				if(evento == TKN_DATOS_CLIENTE) return EDO_DATOS_CLIENTE;
				break;
			case EDO_SM_FACTURA:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_FACTURA;
				break;
			case EDO_SM_NOTA_DE_CREDITO:
				if(evento == EVT_FINALIZADO) return EDO_FIN;
				else return EDO_SM_NOTA_DE_CREDITO;
				break;
			case EDO_DESCRIPCION_PRODUCTO:
				if(evento == EVT_NEUTRO) return EDO_DATOS_CLIENTE;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Datos_Cliente::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_DATOS_CLIENTE: DatosCliente(ACC_IN); break;
			case EDO_SM_FACTURA: SMFactura(); break;
			case EDO_SM_NOTA_DE_CREDITO: SMNotaCredito(); break;
			case EDO_DESCRIPCION_PRODUCTO: SMDescripcionProducto(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Datos_Cliente::Inicio()
	{
	}

	void SM_Datos_Cliente::DatosCliente(Accion param)
	{
		switch(param)
		{
		case ACC_IN:
			{
				if (Evento_Actual == TKN_DATOS_CLIENTE)
				{
					++ii;
					++ii1;
					if (ii1 == 1)
					{
					//Obtener el Serial de la QPrint MF para ser reemplazado
						memset(_buffer,0,1024);
						memset(Serial,0,12);
						strcpy(cmd, "F0;3");
						_print->fncSendCommand(reinterpret_cast<BYTE*>(cmd), reinterpret_cast<BYTE*>(_buffer));
						pch = strtok (_buffer,"|");
						while (pch != NULL)
						{
							if(cont == 17) 
							{
								strcpy(Serial, pch);
								break;
							}
							++cont;
							pch = strtok (NULL, "|");
						}
					// Obtener datos de Configuracion de Encabezado de Datos de Cliente
						std::ifstream in("QPrint\\quorion.ini");
						while (in.good())	
						{
							in.getline(linea, 1024);
							strcpy(_linea, linea);
							int lenlinea = strlen(_linea);

							if ((strcmp(linea, "[EncabezadoFactura]") != 0) && (strcmp(linea, "[EncabezadoNotaCredito]") != 0) && (strcmp(linea, "") != 0))
							{
								pch = strtok (linea,";");
								while (pch != NULL)
								{
									if(cont1 == 0)
									{
										memset(s1, 0, 1024);
										memset(s2, 0, 1024);
										strncat(s1, &pch[0], 11);
										strncat(s2, &pch[11], 1);
									}					
									if(cont1 == 1) { strcpy(cantidad, pch); break; }
									++cont1;
									pch = strtok (NULL, ";");
								}
								cont1 = 0;
								memset(encabezado, 0, 30);
								strncat(encabezado, &_linea[15], (lenlinea - 15));
								if (strcmp(s1, "EncabezadoF") == 0)
								{
									if (atoi(s2) == 1) { strcpy(dato1, encabezado); cant1 = atoi(cantidad); }
									else if (atoi(s2) == 2) { strcpy(dato2, encabezado); cant2 = atoi(cantidad); }
									else if (atoi(s2) == 3) { strcpy(dato3, encabezado); cant3 = atoi(cantidad); }
									else if (atoi(s2) == 4) { strcpy(dato4, encabezado); cant4 = atoi(cantidad); }
									else if (atoi(s2) == 5) { strcpy(dato5, encabezado); cant5 = atoi(cantidad); }
									else if (atoi(s2) == 6) { strcpy(dato6, encabezado); cant6 = atoi(cantidad); }
									else if (atoi(s2) == 7) { strcpy(dato7, encabezado); cant7 = atoi(cantidad); }	
									else if (atoi(s2) == 8) { strcpy(dato8, encabezado); cant8 = atoi(cantidad); }
									else if (atoi(s2) == 9) { strcpy(dato9, encabezado); cant9 = atoi(cantidad); }
								}
								else if (strcmp(s1, "EncabezadoN") == 0)
								{
									if (atoi(s2) == 1) { memset(dato_1, 0, 30); strcpy(dato_1, encabezado); cant_1 = atoi(cantidad); }
									else if (atoi(s2) == 2) { memset(dato_2, 0, 30); strcpy(dato_2, encabezado); cant_2 = atoi(cantidad); }
									else if (atoi(s2) == 3) { memset(dato_3, 0, 30); strcpy(dato_3, encabezado); cant_3 = atoi(cantidad); }
									else if (atoi(s2) == 4) { memset(dato_4, 0, 30); strcpy(dato_4, encabezado); cant_4 = atoi(cantidad); }
									else if (atoi(s2) == 5) { memset(dato_5, 0, 30); strcpy(dato_5, encabezado); cant_5 = atoi(cantidad); }
									else if (atoi(s2) == 6) { memset(dato_6, 0, 30); strcpy(dato_6, encabezado); cant_6 = atoi(cantidad); }
									else if (atoi(s2) == 7) { memset(dato_7, 0, 30); strcpy(dato_7, encabezado); cant_7 = atoi(cantidad); }	
									else if (atoi(s2) == 8) { memset(dato_8, 0, 30); strcpy(dato_8, encabezado); cant_8 = atoi(cantidad); }
									else if (atoi(s2) == 9) { memset(dato_9, 0, 30); strcpy(dato_9, encabezado); cant_9 = atoi(cantidad); }
								}
							}
						}
						std::ifstream close();
					}
				
					memset(s2, 0, 1024);
					strncat(s2, &_trama[3], (_num - 3));

					if (bandera == 1) strcpy(comparar, dato1); 
					else if (bandera == 2) strcpy(comparar, dato2); 
					else if (bandera == 3) strcpy(comparar, dato3); 
					else if (bandera == 4) strcpy(comparar, dato4); 
					else if (bandera == 5) strcpy(comparar, dato5); 
					else if (bandera == 6) strcpy(comparar, dato6); 
					else if (bandera == 7) strcpy(comparar, dato7); 
					else if (bandera == 8) strcpy(comparar, dato8); 
					else if (bandera == 9) strcpy(comparar, dato9); 

					if (bandera1 == 1) strcpy(comparar1, dato_1);
					else if (bandera1 == 2) strcpy(comparar1, dato_2); 
					else if (bandera1 == 3) strcpy(comparar1, dato_3); 
					else if (bandera1 == 4) strcpy(comparar1, dato_4); 
					else if (bandera1 == 5) strcpy(comparar1, dato_5); 
					else if (bandera1 == 6) strcpy(comparar1, dato_6); 
					else if (bandera1 == 7) strcpy(comparar1, dato_7); 
					else if (bandera1 == 8) strcpy(comparar1, dato_8); 
					else if (bandera1 == 9) strcpy(comparar1, dato_9); 
					
					s3 = strstr(s2, comparar);
					s4 = strstr(s2, comparar1);
				// Factura
					if (s3 != NULL)
					{
						if (bandera > 1) strcat(datosclienteF, "|");
						strcat(datosclienteF, s2);
						++bandera;
					} 
					else strcat(datosclienteF, s2);
				// Nota de Credito
					if (s4 != NULL)
					{
						if (bandera1 > 1) strcat(datosclienteNC, "|");
						strcat(datosclienteNC, s2);
						++bandera1;
					} 
					else strcat(datosclienteNC, s2);

					s3 = strstr(datosclienteF, "Z1B");
					if (s3 != NULL)
					{
						strncpy (s3, Serial,10);
					}
					s4 = strstr(datosclienteNC, "Z1B");
					if (s4 != NULL)
					{
						strncpy (s4, Serial,10);
					}
				}
			} break;
		case ACC_OUT:
			{
				if (Evento_Actual == TKN_FACT_REGISTRO_PRODUCTO)
				{
					bandera = 1;
					bandera1 = 1;
					memset(comparar, 0, 30);
					memset(comparar1, 0, 30);
					memset(datosclienteNC,0,1024);
					memset(datoscliente,0,1024);
					strcpy(datoscliente, "F2;1;0;3;");
					strcpy(s2, "Factura");

					cont = 1;
					cantidadF = 0;
					pch = strtok (datosclienteF,"|");
					while (pch != NULL)
					{
						if (cont == 1) cantidadF = cant1;
						else if (cont == 2) cantidadF = cant2;
						else if (cont == 3) cantidadF = cant3;
						else if (cont == 4) cantidadF = cant4;
						else if (cont == 5) cantidadF = cant5;
						else if (cont == 6) cantidadF = cant6;
						else if (cont == 7) cantidadF = cant7;
						else if (cont == 8) cantidadF = cant8;
						else if (cont == 9) cantidadF = cant9;

						memset(linea_F, 0, 300);
						strcpy(linea_F, pch);
						len = strlen(linea_F);
						if ((len > 40) && (len <= 80))
						{
							memset(variable1, 0, 50); strcat(variable1, "\""); strncat(variable1, &linea_F[0], 40); strcat(variable1, "\"");
							memset(variable2, 0, 50); strcat(variable2, "\""); strncat(variable2, &linea_F[40], (len - 40)); strcat(variable2, "\"");
							if (cantidadF == 1) { strcat(datoscliente, variable1); strcat(datoscliente, ";"); }
							else if (cantidadF >= 2) { strcat(datoscliente, variable1); strcat(datoscliente, ";"); strcat(datoscliente, variable2); strcat(datoscliente, ";");}

						}
						else if ((len > 80) && (len <= 120))
						{
							memset(variable1, 0, 50); strcat(variable1, "\""); strncat(variable1, &linea_F[0], 40); strcat(variable1, "\"");
							memset(variable2, 0, 50); strcat(variable2, "\""); strncat(variable2, &linea_F[40], 40); strcat(variable2, "\"");
							memset(variable3, 0, 50); strcat(variable3, "\""); strncat(variable3, &linea_F[80], (len - 80)); strcat(variable3, "\"");
							if (cantidadF == 1) { strcat(datoscliente, variable1); strcat(datoscliente, ";"); }
							else if (cantidadF == 2) { strcat(datoscliente, variable1); strcat(datoscliente, ";"); strcat(datoscliente, variable2); strcat(datoscliente, ";");}
							else if (cantidadF == 3) { strcat(datoscliente, variable1); strcat(datoscliente, ";"); strcat(datoscliente, variable2); strcat(datoscliente, ";"); strcat(datoscliente, variable3); strcat(datoscliente, ";");}
						}
						else if ((len > 0) && (len <= 40))
						{
							strcat(datoscliente, "\"");
							strncat(datoscliente, &linea_F[0], len);
							strcat(datoscliente, "\";");
						}

						memset(variable1, 0, 50);
						memset(variable2, 0, 50);
						memset(variable3, 0, 50);
						++cont;
						pch = strtok (NULL, "|");
					}

					strcpy(s1, datoscliente);
					printf("Datos de Cliente Factura\n%s\n", datoscliente);
			
					memset(_buffer,0,1024);
					error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
					printf("buffer: %s error: %i\n",_buffer, error);
					_print->fncAnalyzeStatus(error, _buffer);
					_print->fncRegistrarLog(error, "DatoDeCliente Fact", s1);
				
					_vari1 = 1;
/*					if (Evento_Actual == TKN_FACT_REGISTRO_PRODUCTO) _vari2 = 0;
					else if (Evento_Actual == TKN_FACT_DESCRIPCION_PRODUCTO) _vari2 = 1;
*/
					smf.vari(_vari1, _vari2, descripcion);
					memset(datoscliente,0,1024);
					memset(datosclienteF,0,1024);
					memset(s1,0,1024);
					ii = 0;
				}

				else if (Evento_Actual == TKN_NC_REGISTRO_PRODUCTO)
				{
					bandera = 1;
					bandera1 = 1;
					memset(comparar, 0, 30);
					memset(comparar1, 0, 30);
					memset(datosclienteF,0,1024);
					memset(NCdatoscliente,0,1024);
					strcpy(NCdatoscliente, "F2;12;0;3;");
				
					cont = 1;
					cantidadNC = 0;
					pch = strtok (datosclienteNC,"|");
					while (pch != NULL)
					{
						if (cont == 1) cantidadNC = cant_1;
						else if (cont == 2) cantidadNC = cant_2;
						else if (cont == 3) cantidadNC = cant_3;
						else if (cont == 4) cantidadNC = cant_4;
						else if (cont == 5) cantidadNC = cant_5;
						else if (cont == 6) cantidadNC = cant_6;
						else if (cont == 7) cantidadNC = cant_7;
						else if (cont == 8) cantidadNC = cant_8;
						else if (cont == 9) cantidadNC = cant_9;

						memset(linea_NC, 0, 300);
						strcpy(linea_NC, pch);
						len = strlen(linea_NC);
						if ((len > 40) && (len <= 80))
						{
							memset(variable1, 0, 50); strcat(variable1, "\""); strncat(variable1, &linea_NC[0], 40); strcat(variable1, "\"");
							memset(variable2, 0, 50); strcat(variable2, "\""); strncat(variable2, &linea_NC[40], (len - 40)); strcat(variable2, "\"");
							if (cantidadNC == 1) { strcat(NCdatoscliente, variable1); strcat(NCdatoscliente, ";"); }
							else if (cantidadNC >= 2) { strcat(NCdatoscliente, variable1); strcat(NCdatoscliente, ";"); strcat(NCdatoscliente, variable2); strcat(NCdatoscliente, ";");}

						}
						else if ((len > 80) && (len <= 120))
						{
							memset(variable1, 0, 50); strcat(variable1, "\""); strncat(variable1, &linea_NC[0], 40); strcat(variable1, "\"");
							memset(variable2, 0, 50); strcat(variable2, "\""); strncat(variable2, &linea_NC[40], 40); strcat(variable2, "\"");
							memset(variable3, 0, 50); strcat(variable3, "\""); strncat(variable3, &linea_NC[80], (len - 80)); strcat(variable3, "\"");
							if (cantidadNC == 1) { strcat(NCdatoscliente, variable1); strcat(NCdatoscliente, ";"); }
							else if (cantidadNC == 2) { strcat(NCdatoscliente, variable1); strcat(NCdatoscliente, ";"); strcat(NCdatoscliente, variable2); strcat(NCdatoscliente, ";");}
							else if (cantidadNC == 3) { strcat(NCdatoscliente, variable1); strcat(NCdatoscliente, ";"); strcat(NCdatoscliente, variable2); strcat(NCdatoscliente, ";"); strcat(NCdatoscliente, variable3); strcat(NCdatoscliente, ";");}
						}
						else if ((len > 0) && (len <= 40))
						{
							strcat(NCdatoscliente, "\"");
							strncat(NCdatoscliente, &linea_NC[0], len);
							strcat(NCdatoscliente, "\";");
						}

						memset(variable1, 0, 50);
						memset(variable2, 0, 50);
						memset(variable3, 0, 50);
						++cont;
						pch = strtok (NULL, "|");
					}

					if (ii == 1) strcat(NCdatoscliente, ";;;;");
					if (ii == 2) strcat(NCdatoscliente, " ;;;");
					if (ii == 3) strcat(NCdatoscliente, " ;;");
					if (ii == 4) strcat(NCdatoscliente, " ;");

					printf("Datos de Cliente Nota de Credito\n%s\n", NCdatoscliente);
					memset(s1, 0, 1024);
					strcpy(s1, NCdatoscliente);
								
					memset(_buffer,0,1024);
					error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
					printf("buffer: %s\n",_buffer);
					_print->fncAnalyzeStatus(error, _buffer);
					_print->fncRegistrarLog(error, "DatoDeCliente NC", s1);

					memset(NCdatoscliente,0,1024);
					memset(datosclienteNC,0,1024);
					_vari1 = 1;
					smnc.vari(_vari1, _vari2, descripcion);
					memset(s1,0,1024);
					ii = 0;
				}
			} break;
		}
	}

	void SM_Datos_Cliente::SMFactura()
	{
		printf("SMFactura\n");

		if(smf.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Datos_Cliente::SMNotaCredito()
	{
		printf("SMNotaCredito\n");

		if(smnc.Check(Evento_Actual, _trama, _num) == EVT_FINALIZADO)
		{
			Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
		}
	}

	void SM_Datos_Cliente::SMDescripcionProducto()
	{
		printf("SMDescripcionProducto\n");

		memset(s1,0,1024);
		strncat(s1, &_trama[1], (_num - 1));
		strcat(descripcion, s1);
		strcat(descripcion, "\n");
		memset(s1,0,1024);
		_vari2 = 1;
		
		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Datos_Cliente::Fin()
	{
		printf("Fin SM_Datos_Cliente\n");
		memset(descripcion, 0, 1024);

		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Datos_Cliente::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}


// FACTURA

	SM_Factura::SM_Factura()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
		subtotal = 0;
		item = 0;
		y = 0;
		strcpy(variable, "");
		_vari1 = 0;
		_vari2 = 0;
		memset(descripcion, 0, 1024);
	}

    SM_Factura::~SM_Factura()
	{
	}

	void SM_Factura::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	void SM_Factura::vari(int variable1, int variable2, char * _descripcion)
	{
		_vari1 = variable1;
		_vari2 = variable2;
		strcpy(descripcion, _descripcion);
	}

	Eventos SM_Factura::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Factura::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_FACT_REGISTRO_PRODUCTO) return EDO_FACT_REGISTRO_PRODUCTO;
				if(evento == TKN_FACT_DESCRIPCION_PRODUCTO) return EDO_FACT_DESCRIPCION_PRODUCTO;
				break;
			case EDO_FACT_REGISTRO_PRODUCTO:
				if(evento == TKN_FACT_REGISTRO_PRODUCTO) return EDO_FACT_REGISTRO_PRODUCTO;
				if(evento == TKN_FACT_DESCRIPCION_PRODUCTO) return EDO_FACT_DESCRIPCION_PRODUCTO;
				if(evento == TKN_FACT_CORRECCION) return EDO_FACT_CORRECCION;
				if(evento == TKN_FACT_SUBTOTAL) return EDO_FACT_SUBTOTAL;
				if(evento == TKN_FACT_RECARGO_O_DESCUENTO) return EDO_FACT_RECARGO_O_DESCUENTO;
				if(evento == TKN_FACT_ANULACION_ITEM) return EDO_FACT_ANULACION_ITEM;
				if(evento == TKN_FACT_ANULACION_FACTURA) return EDO_FACT_ANULACION_FACTURA;
				if(evento == TKN_FACT_PAGO_DIRECTO) return EDO_FACT_PAGO_DIRECTO;
				if(evento == TKN_FACT_PAGO_PARCIAL) return EDO_FACT_PAGO_PARCIAL;
				if(evento == TKN_FACT_CODIGO_DE_BARRA) return EDO_FACT_CODIGO_DE_BARRA;
				break;
			case EDO_FACT_DESCRIPCION_PRODUCTO:
				if(evento == EVT_NEUTRO) return EDO_FACT_REGISTRO_PRODUCTO;
				break;
			case EDO_FACT_CORRECCION:
				if(evento == EVT_NEUTRO) return EDO_FACT_REGISTRO_PRODUCTO;
				break;
			case EDO_FACT_SUBTOTAL:
				if(evento == EVT_NEUTRO) return EDO_FACT_REGISTRO_PRODUCTO;
				break;
			case EDO_FACT_RECARGO_O_DESCUENTO:
				if(evento == EVT_NEUTRO) return EDO_FACT_REGISTRO_PRODUCTO;
				break;
			case EDO_FACT_ANULACION_ITEM:
				if(evento == EVT_NEUTRO) return EDO_FACT_REGISTRO_PRODUCTO;
				break;
			case EDO_FACT_ANULACION_FACTURA:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FACT_PAGO_DIRECTO:
				if(evento == EVT_NEUTRO) return EDO_GENERAR_FACTURA;
				break;
			case EDO_FACT_PAGO_PARCIAL:
				if(evento == TKN_FACT_PAGO_PARCIAL) return EDO_FACT_PAGO_PARCIAL;
				if(evento == EVT_MONTO_TOTAL_ALCANZADO) return EDO_GENERAR_FACTURA;
				break;
			case EDO_FACT_CODIGO_DE_BARRA:
				if(evento == EVT_NEUTRO) return EDO_FACT_REGISTRO_PRODUCTO;
				break;
			case EDO_GENERAR_FACTURA:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Factura::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_FACT_REGISTRO_PRODUCTO: FactRegistroProducto(); break;
			case EDO_FACT_DESCRIPCION_PRODUCTO: FactDescripcionProducto(); break;
			case EDO_FACT_CORRECCION: FactCorreccion(); break;
			case EDO_FACT_SUBTOTAL: FactSubtotal(); break;
			case EDO_FACT_RECARGO_O_DESCUENTO: FactRecargoODescuento(); break;
			case EDO_FACT_ANULACION_ITEM: FactAnulacionITEM(); break;
			case EDO_FACT_ANULACION_FACTURA: FactAnulacionFactura(); break;
			case EDO_FACT_PAGO_DIRECTO: FactPagoDirecto(); break;
			case EDO_FACT_PAGO_PARCIAL: FactPagoParcial(); break;
			case EDO_FACT_CODIGO_DE_BARRA: FactCodigoBarra(); break;
			case EDO_GENERAR_FACTURA: GenerarFactura(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}

		return Evento_Actual;
	}

	void SM_Factura::Inicio()
	{
		//printf("Inicio SM_Factura\n");
	}

	void SM_Factura::FactDescripcionProducto()
	{
		memset(s1,0,1024);
		strncat(s1, &_trama[1], (_num - 1));
		strcat(descripcion, s1);
		strcat(descripcion, "\n");
		memset(s1,0,1024);
		_vari2 = 1;
		
		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Factura::FactRegistroProducto()
	{
		if(Evento_Actual == TKN_FACT_REGISTRO_PRODUCTO)
		{
			if (_vari1 == 0)
			{
				strcpy(s1, "F2;1");

				memset(_buffer,0,1024);
				error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
				printf("buffer: %s error %i\n",_buffer, error);
				_print->fncAnalyzeStatus(error, _buffer);
				_print->fncRegistrarLog(error, "FactRegistroProducto", s1);
				printf("Inicio de Documento fiscal %s\n", s1);
		
				_vari1 = 1;
			}
			memset(s2, 0, 1024); x = 0;
			
			memset(s1, 0, 1024);
			strcpy(s1, "F2;3;\"");
			memset(s3, 0, 1024);
			if (_num > 19) strncat(s3, &_trama[19], (_num - 19));
			if (strcmp(s3, "") == 0) strcpy(s3, "Articulo");
			strcat(s1, s3);
			strcat(s1, "\";");
			
			strncat(s2, &_trama[1], 10);
			item = atoi (s2);
			itoa (item, _item, 10);
			strcat(s1, _item);
			
			memset(s2, 0, 1024);
			strncat(s2, &_trama[0], 1);
			if (strcmp(s2, "!") == 0) strcat(s1, ";1;");
			if (strcmp(s2, "\"") == 0) strcat(s1, ";2;");
			if (strcmp(s2, "#") == 0) strcat(s1, ";3;");
			if (strcmp(s2, " ") == 0) strcat(s1, ";4;");
			
			memset(s2, 0, 1024);
			strncat(s2, &_trama[11], 5);
			x = atoi (s2);
			itoa (x, _x, 10);
			strcat(s1, _x);

			memset(s4, 0, 1024);
			strncat(s4, &_trama[16], 3);
			strcat(s1, ".");
			strcat(s1, s4);

			printf(" QPrint FACT Registro de Producto: %s\n", s1);

			// Enviar comando de Registro de Producto
			memset(_buffer,0,1024);
			error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
			printf("buffer: %s error %i\n",_buffer, error);
			_print->fncAnalyzeStatus(error, _buffer);
			_print->fncRegistrarLog(error, "FactRegistroProducto", s1);
		
		// Enviar comando de Descripcion de Producto
			if (_vari2 == 1)
			{
				len_des = strlen(descripcion);

				cont = 0;
				memset(linea, 0, 30);
				for(i=0; i<=len_des; i++)
				{
					++cont;
					memset(letra, 0, 5);
					strncat(letra,&descripcion[i],1);
					if (strcmp(letra, "\n") != 0) 
					{
						strncat(linea,&descripcion[i],1);
					}
					
					if ((cont == 25) || (strcmp(letra, "\n") == 0))
					{
						memset(s1, 0, 1024);
						strcat(s1, "U4000;1;\"");
						strcat(s1, linea);
						strcat(s1, "\";");

						memset(_buffer,0,1024);
						error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
						printf("buffer: %s error: %i\n",_buffer, error);
						//_print->fncAnalyzeStatus(error, _buffer);
						_print->fncRegistrarLog(error, "FactDescripcionProducto", s1);

						memset(s1, 0, 1024);
						strcpy(s1, "U5;4001;");

						memset(_buffer,0,1024);
						error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
						printf("buffer: %s error %i\n",_buffer, error);
						//_print->fncAnalyzeStatus(error, _buffer);
						_print->fncRegistrarLog(error, "FactDescripcionProducto", s1);

						cont = 0;
						memset(linea, 0, 30);
					}
				}
			}
			_vari2 = 0;
			memset(descripcion, 0, 1024);
			strcpy(variable, "I");
		} 
	}

	void SM_Factura::FactCorreccion()
	{
		//printf("FactCorreccion\n");

		strcpy(s1, "F2;5;1");
		printf(" QPrint FACT Correccion: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "FactCorreccion", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Factura::FactSubtotal()
	{
		//printf("FactSubtotal\n");

		strcpy(variable, "S");
		strcpy(s1, "F2;4");
		printf(" QPrint FACT Subtotal: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "FactSubtotal", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Factura::FactRecargoODescuento()
	{
		//printf("FactRecargoODescuento\n");

		memset(s1, 0, 1024); 
		strncat(s1, &_trama[2], (_num - 2));	
		strcpy(porcentaje, s1);

		memset(s1, 0, 1024);
		strncat(s1, &_trama[1], 1);
		
		if(strcmp(s1, "+") == 0)
		{
			if (strcmp(variable, "I") == 0)
			{
				strcpy(s1, "F2;6;;2;;");
				strcat(s1, porcentaje);
				strcat(s1, ";;246");
			}
			if (strcmp(variable, "S") == 0)
			{
				strcpy(s1, "F2;6;;2;;");
				strcat(s1, porcentaje);
				strcat(s1, ";;2567");
			}	
		}

		if(strcmp(s1, "-") == 0)
		{
			if (strcmp(variable, "I") == 0)
			{
				strcpy(s1, "F2;6;;1;;");
				strcat(s1, porcentaje);
				strcat(s1, ";;46");
			}
			if (strcmp(variable, "S") == 0)
			{
				strcpy(s1, "F2;6;;1;;");
				strcat(s1, porcentaje);
				strcat(s1, ";;567");
			}
		}

		printf(" QPrint Recargo o Descuento: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "FactRecargoODescuento", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Factura::FactAnulacionITEM()
	{
		//printf("FactAnulacionITEM\n");

		strcpy(s1, "F2;5;2;");
		printf(" QPrint Anulacion por ITEM: %s\n", s1);
		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);	
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "FactAnulacionITEM", s1);
		
		strcpy(s1, "F2;3;\"");
		strncat(s1, &_trama[19], (_num - 19));
		strcat(s1, "\";");
		
		memset(s2, 0, 1024);
		strncat(s2, &_trama[1], 10);
		item = atoi (s2);
		itoa (item, _item, 10);
		strcat(s1, _item);

		memset(s2, 0, 1024);
		strncat(s2, &_trama[0], 1);
		if (strcmp(s2, "¡") == 0) strcat(s1, ";1;");
		if (strcmp(s2, "¢") == 0) strcat(s1, ";2;");
		if (strcmp(s2, "£") == 0) strcat(s1, ";3;");
		if (strcmp(s2, " ") == 0) strcat(s1, ";4;");

		memset(s2, 0, 1024);
		strncat(s2, &_trama[11], 5);
		x = atoi (s2);
		itoa (x, _x, 10);
		strcat(s1, _x);

		printf(" QPrint Anulacion de ITEM: %s\n", s1);
		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "FactAnulacionITEM", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Factura::FactAnulacionFactura()
	{
		//printf("FactAnulacionFactura\n");

		strcpy(s1, "F2;5;4;");
		printf(" QPrint Anulacion de Factura: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "FactAnulacionFactura", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Factura::FactPagoDirecto()
	{
		//printf("FactPagoDirecto\n");

		memset(s2, 0, 1024);
		strncat(s2, &_trama[1], (_num - 1));

		if (strcmp(s2, "01") == 0) strcpy(s1, "F2;2;;1;"); 
		else if (strcmp(s2, "02") == 0) strcpy(s1, "F2;2;;2;"); 
		else if (strcmp(s2, "03") == 0) strcpy(s1, "F2;2;;3;"); 
		else if (strcmp(s2, "04") == 0) strcpy(s1, "F2;2;;4;"); 
		else if (strcmp(s2, "05") == 0) strcpy(s1, "F2;2;;1;"); 
		else if (strcmp(s2, "06") == 0) strcpy(s1, "F2;2;;1;"); 
		else if (strcmp(s2, "07") == 0) strcpy(s1, "F2;2;;1;"); 
		else if (strcmp(s2, "08") == 0) strcpy(s1, "F2;2;;1;"); 
		else if (strcmp(s2, "09") == 0) strcpy(s1, "F2;2;;1;"); 
		else if (strcmp(s2, "10") == 0) strcpy(s1, "F2;2;;1;"); 
		else if (strcmp(s2, "11") == 0) strcpy(s1, "F2;2;;1;"); 
		else if (strcmp(s2, "12") == 0) strcpy(s1, "F2;2;;1;"); 
		else if (strcmp(s2, "13") == 0) strcpy(s1, "F2;2;;1;"); 
		else if (strcmp(s2, "14") == 0) strcpy(s1, "F2;2;;1;"); 
		else if (strcmp(s2, "15") == 0) strcpy(s1, "F2;2;;1;"); 
		else if (strcmp(s2, "16") == 0) strcpy(s1, "F2;2;;1;"); 

		printf(" QPrint Forma de Pago Directa: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "FactPagoDirecto", s1);
	
		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Factura::FactPagoParcial()
	{
		//printf("FactPagoParcial\n");

		memset(s2,0,1024); 
		memset(s1,0,1024); 
		memset(_x,0,1024);
		x = 0;
		strncat(s2, &_trama[3], (_num - 3));
		x = atoi (s2);
		itoa (x, _x, 10);
		strcpy(s1, "F2;2;");
		strcat(s1, _x);

		memset(s2,0,1024); 
		strncat(s2, &_trama[1], 2);

		if (strcmp(s2, "01") == 0) strcat(s1, ";1;"); 
		else if (strcmp(s2, "02") == 0) strcat(s1, ";2;"); 
		else if (strcmp(s2, "03") == 0) strcat(s1, ";3;"); 
		else if (strcmp(s2, "04") == 0) strcat(s1, ";4;"); 
		else if (strcmp(s2, "05") == 0) strcat(s1, ";1;"); 
		else if (strcmp(s2, "06") == 0) strcat(s1, ";1;"); 
		else if (strcmp(s2, "07") == 0) strcat(s1, ";1;"); 
		else if (strcmp(s2, "08") == 0) strcat(s1, ";1;"); 
		else if (strcmp(s2, "09") == 0) strcat(s1, ";1;"); 
		else if (strcmp(s2, "10") == 0) strcat(s1, ";1;"); 
		else if (strcmp(s2, "11") == 0) strcat(s1, ";1;"); 
		else if (strcmp(s2, "12") == 0) strcat(s1, ";1;"); 
		else if (strcmp(s2, "13") == 0) strcat(s1, ";1;"); 
		else if (strcmp(s2, "14") == 0) strcat(s1, ";1;"); 
		else if (strcmp(s2, "15") == 0) strcat(s1, ";1;"); 
		else if (strcmp(s2, "16") == 0) strcat(s1, ";1;"); 

		printf(" QPrint Forma de Pago Parcial: %s\n", s1);
		
		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s Error %i\n",_buffer, error);
		try
		{
			_print->fncAnalyzeStatus(error, _buffer);
		}
		catch(...)
		{
			printf("_print->fncAnalyzeStatus\n");
		}
		try
		{
			_print->fncRegistrarLog(error, "FactPagoParcial", s1);
		}
		catch(...)
		{
			printf("_print->fncRegistrarLog\n");
		}

		memset(s2,0,1024);
		y = y + x;

		
		cont = 0;
		strcpy(cmd, "F0;3");
		_print->fncSendCommand(reinterpret_cast<BYTE*>(&cmd[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s Error %i\n",_buffer, error);
		pch = strtok (_buffer,"|");
		while (pch != NULL)
		{
			if(cont == 26) {memset(BIG, 0, 10); strcpy(BIG, pch); printf("BIG %s\n", BIG);}
			if(cont == 27) {memset(IVAG, 0, 10); strcpy(IVAG, pch); printf("IVAG %s\n", IVAG);}
			if(cont == 28) {memset(BIR, 0, 10); strcpy(BIR, pch); printf("BIR %s\n", BIR);}
			if(cont == 29) {memset(IVAR, 0, 10); strcpy(IVAR, pch); printf("IVAR %s\n", IVAR);}
			if(cont == 30) {memset(BIA, 0, 10); strcpy(BIA, pch); printf("BIA %s\n", BIA);}
			if(cont == 31) {memset(IVAA, 0, 10); strcpy(IVAA, pch); printf("IVAA %s\n", IVAA);}
			if(cont == 32) {memset(Exento, 0, 10); strcpy(Exento, pch); printf("Exento %s\n", Exento);}
			++cont;
			pch = strtok (NULL, "|");
		}

		_BIG = atoi (BIG);
		_IVAG = atoi (IVAG);
		_BIR = atoi (BIR);
		_IVAR = atoi (IVAR);
		_BIA = atoi (BIA);
		_IVAA = atoi (IVAA);
		_Exento = atoi (Exento);

		subtotal = _BIG + _IVAG + _BIR + _IVAR + _BIA + _IVAA + _Exento;
		resto = subtotal - y;

		if ((y >= subtotal) || (resto <= 5))
		{
			if ((resto > 1) && (resto <= 5))
			{
				strcpy(s1, "F2;2;;1;");
				memset(_buffer,0,1024);
				error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
				printf("buffer: %s\n",_buffer);
			}

			y = 0;
			subtotal = 0;
			Ejecutar(T(Estado_Actual,EVT_MONTO_TOTAL_ALCANZADO));
		}
	}

	void SM_Factura::FactCodigoBarra()
	{
		//printf("FactCodigoBarra\n");
		
		strcpy(s1, "F1;7;");
		strncat(s1, &_trama[1], (_num - 1));
		printf(" QPrint Codigo de Barra: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "FactCodigoBarra", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Factura::GenerarFactura()
	{
		//printf("GenerarFactura\n");

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Factura::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

	void SM_Factura::Fin()
	{
		subtotal = 0;
		item = 0;
		x = 0;
		y = 0;
		memset(variable, 0, 4);
		memset(porcentaje, 0, 10);
		error = 0;
		memset(linea, 0, 1024);
		memset(descripcion, 0, 1024);
		i = 0;
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

// NOTA DE CREDITO
	
	SM_Nota_de_Credito::SM_Nota_de_Credito()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
		_vari = 0;
		subtotal = 0;
		y = 0;
	}

    SM_Nota_de_Credito::~SM_Nota_de_Credito()
	{
	}

	void SM_Nota_de_Credito::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;		
	}

	void SM_Nota_de_Credito::vari(int variable1, int variable2, char * _descripcion)
	{
		_vari = variable1;
		_vari2 = variable2;
		strcpy(descripcion, _descripcion);
	}

	Eventos SM_Nota_de_Credito::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Nota_de_Credito::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_NC_REGISTRO_PRODUCTO) return EDO_NC_REGISTRO_PRODUCTO;
				break;
			case EDO_NC_REGISTRO_PRODUCTO:
				if(evento == TKN_NC_REGISTRO_PRODUCTO) return EDO_NC_REGISTRO_PRODUCTO;
				if(evento == TKN_NC_ANULACION_ITEM) return EDO_NC_ANULACION_ITEM;
				if(evento == TKN_NC_CIERRE_DEVOLUCION) return EDO_NC_CIERRE_DEVOLUCION;
				if(evento == TKN_FACT_DESCRIPCION_PRODUCTO) return EDO_NC_DESCRIPCION_PRODUCTO;
				if(evento == TKN_FACT_SUBTOTAL) return EDO_NC_SUBTOTAL;
				if(evento == TKN_FACT_RECARGO_O_DESCUENTO) return EDO_NC_RECARGO_O_DESCUENTO;
				break;
			case EDO_NC_DESCRIPCION_PRODUCTO:
				if(evento == EVT_NEUTRO) return EDO_NC_REGISTRO_PRODUCTO;
				break;
			case EDO_NC_SUBTOTAL:
				if(evento == EVT_NEUTRO) return EDO_NC_REGISTRO_PRODUCTO;
				break;
			case EDO_NC_RECARGO_O_DESCUENTO:
				if(evento == EVT_NEUTRO) return EDO_NC_REGISTRO_PRODUCTO;
				break;
			case EDO_NC_ANULACION_ITEM:
				if(evento == EVT_NEUTRO) return EDO_NC_REGISTRO_PRODUCTO;
				break;
			case EDO_NC_CIERRE_DEVOLUCION:
				if(evento == TKN_FACT_PAGO_PARCIAL) return EDO_NC_CIERRE_DEVOLUCION;
				if(evento == EVT_NC_FIN_CIERRE) return EDO_GENERAR_NOTA_CREDITO;
				break;
			case EDO_GENERAR_NOTA_CREDITO:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Nota_de_Credito::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_NC_REGISTRO_PRODUCTO: NCRegistroProducto(); break;
			case EDO_NC_DESCRIPCION_PRODUCTO: NCDescripcionProducto(); break;
			case EDO_NC_SUBTOTAL: NCSubtotal(); break;
			case EDO_NC_RECARGO_O_DESCUENTO: NCRecargoODescuento(); break;
			case EDO_NC_ANULACION_ITEM: NCAnulacionITEM(); break;
			case EDO_NC_CIERRE_DEVOLUCION: NCCierreDevolucion(); break;
			case EDO_GENERAR_NOTA_CREDITO: GenerarNotaCredito(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}

		return Evento_Actual;
	}

	void SM_Nota_de_Credito::Inicio()
	{
		printf("Inicio\n");
	}

	void SM_Nota_de_Credito::NCRegistroProducto()
	{
		if (Evento_Actual == TKN_NC_REGISTRO_PRODUCTO)
		{		
			printf("NCRegistroProducto\n");

			// Enviar comando de Descripcion de Producto
			

			memset(_x, 0, 1024);
			if (_vari == 0)
			{
				strcpy(s1, "F2;12;0;3;;;;;;");
				memset(_buffer,0,1024);
				error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
				printf("buffer: %s\n",_buffer);
				_print->fncAnalyzeStatus(error, _buffer);
				_print->fncRegistrarLog(error, "NCRegistroProducto", s1);
			
				_vari = 1;
				printf("Inicio de Documento fiscal %s\n", s1);
			}

			memset(s2, 0, 1024); x = 0;
			memset(s1, 0, 1024);
			strcpy(s1, "F2;3;\"");
			if (_num > 20)
			{
				strncat(s1, &_trama[20], (_num - 20));
			} else strcat(s1, "Articulo");
			strcat(s1, "\";");
			
			strncat(s2, &_trama[2], 10);
			x = atoi (s2);
			itoa (x, _x, 10);
			strcat(s1, _x);

			subtotal = subtotal + x;
			
			if (x > 0)
			{
				memset(s2, 0, 1024);
				strncat(s2, &_trama[1], 1);
				if ((strcmp(s2, "1") == 0) || (strcmp(s2, "!") == 0)) strcat(s1, ";1;");
				else if ((strcmp(s2, "2") == 0) || (strcmp(s2, "\"") == 0)) strcat(s1, ";2;");
				else if ((strcmp(s2, "3") == 0) || (strcmp(s2, "#") == 0)) strcat(s1, ";3;");
				else if ((strcmp(s2, "0") == 0) || (strcmp(s2, " ") == 0)) strcat(s1, ";4;");

				memset(s2, 0, 1024); x = 0;
				strncat(s2, &_trama[12], 5);
				x = atoi (s2);
				itoa (x, _x, 10);
				strcat(s1, _x);

				printf(" QPrint NC Registro de Producto: %s\n", s1);
				
				memset(_buffer,0,1024);
				error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
				printf("buffer: %s\n",_buffer);
				_print->fncAnalyzeStatus(error, _buffer);
				_print->fncRegistrarLog(error, "NCRegistroProducto", s1);
			}

			if (_vari2 == 1)
			{
				len_des = strlen(descripcion);

				cont = 0;
				memset(linea, 0, 30);
				for(i=0; i<=len_des; i++)
				{
					++cont;
					memset(letra, 0, 5);
					strncat(letra,&descripcion[i],1);
					if (strcmp(letra, "\n") != 0) 
					{
						strncat(linea,&descripcion[i],1);
					}
					
					if ((cont == 25) || (strcmp(letra, "\n") == 0))
					{
						memset(s1, 0, 1024);
						strcat(s1, "U4000;1;\"");
						strcat(s1, linea);
						strcat(s1, "\";");

						memset(_buffer,0,1024);
						error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
						printf("buffer: %s error: %i\n",_buffer, error);
						//_print->fncAnalyzeStatus(error, _buffer);
						_print->fncRegistrarLog(error, "FactDescripcionProducto", s1);

						memset(s1, 0, 1024);
						strcpy(s1, "U5;4001;");

						memset(_buffer,0,1024);
						error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
						printf("buffer: %s error %i\n",_buffer, error);
						//_print->fncAnalyzeStatus(error, _buffer);
						_print->fncRegistrarLog(error, "FactDescripcionProducto", s1);

						cont = 0;
						memset(linea, 0, 30);
					}
				}
			}
			_vari2 = 0;
			memset(descripcion, 0, 1024);
			strcpy(variable, "I");
		}
	} 

	void SM_Nota_de_Credito::NCDescripcionProducto()
	{
		memset(s1,0,1024);
		strncat(s1, &_trama[1], (_num - 1));
		strcat(descripcion, s1);
		strcat(descripcion, "\n");
		memset(s1,0,1024);
		_vari2 = 1;
		
		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Nota_de_Credito::NCSubtotal()
	{
		//printf("FactSubtotal\n");

		strcpy(variable, "S");
		strcpy(s1, "F2;4");
		printf(" QPrint FACT Subtotal: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "FactSubtotal", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Nota_de_Credito::NCRecargoODescuento()
	{
		memset(s1, 0, 1024);
		strncat(s1, &_trama[2], (_num - 2));	
		strcpy(porcentaje, s1);

		memset(s1, 0, 1024);
		strncat(s1, &_trama[1], 1);
		
		if(strcmp(s1, "+") == 0)
		{
			if (strcmp(variable, "I") == 0)
			{
				memset(s1, 0, 1024);
				strcpy(s1, "F2;6;;2;;");
				strcat(s1, porcentaje);
				strcat(s1, ";;246");
			}
			if (strcmp(variable, "S") == 0)
			{
				memset(s1, 0, 1024);
				strcpy(s1, "F2;6;;2;;");
				strcat(s1, porcentaje);
				strcat(s1, ";;2567");
			}	
		}

		if(strcmp(s1, "-") == 0)
		{
			if (strcmp(variable, "I") == 0)
			{
				memset(s1, 0, 1024);
				strcpy(s1, "F2;6;;1;;");
				strcat(s1, porcentaje);
				strcat(s1, ";;46");
			}
			if (strcmp(variable, "S") == 0)
			{
				memset(s1, 0, 1024);
				strcpy(s1, "F2;6;;1;;");
				strcat(s1, porcentaje);
				strcat(s1, ";;567");
			}
		}

		printf(" QPrint Recargo o Descuento: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "FactRecargoODescuento", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Nota_de_Credito::NCAnulacionITEM()
	{
		printf("NCAnulacionITEM\n");

		strcpy(s1, "F2;5;2;");
		printf(" QPrint NC Inicio Anulacion de Producto: %s\n", s1);
		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "NCAnulacionITEM", s1);
		
		memset(s1, 0, 1024);
		strcpy(s1, "F2;3;\"");
		strncat(s1, &_trama[20], (_num - 20));
		strcat(s1, "\";");
		
		memset(s2, 0, 1024);
		strncat(s2, &_trama[2], 10);
		item = atoi (s2);
		itoa (item, _item, 10);
		strcat(s1, _item);

		memset(s2, 0, 1024);
		strncat(s2, &_trama[1], 1);
		if (strcmp(s2, "1") == 0) strcat(s1, ";1;");
		if (strcmp(s2, "2") == 0) strcat(s1, ";2;");
		if (strcmp(s2, "3") == 0) strcat(s1, ";3;");
		if (strcmp(s2, "0") == 0) strcat(s1, ";4;");

		memset(s2, 0, 1024);
		strncat(s2, &_trama[12], 5);
		x = atoi (s2);
		itoa (x, _x, 10);
		strcat(s1, _x);

		printf(" QPrint NC Anulacion de Producto: %s\n", s1);
		
		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "NCAnulacionITEM", s1);
	
		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Nota_de_Credito::NCCierreDevolucion()
	{
		printf("NCCierreDevolucion\n");
		

		if(Evento_Actual == TKN_NC_CIERRE_DEVOLUCION)
		{
			strcpy(s1, "F2;13");
			printf(" QPrint NC Cierre de Devolucion 1 forma de pago: %s\n", s1);
			memset(_buffer,0,1024);
			error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
			printf("buffer: %s\n",_buffer);
			_print->fncAnalyzeStatus(error, _buffer);
			_print->fncRegistrarLog(error, "NCCierreDevolucion", s1);
		
			Ejecutar(T(Estado_Actual,EVT_NC_FIN_CIERRE));
		}

		if(Evento_Actual == TKN_FACT_PAGO_PARCIAL)
		{
			memset(s2,0,1024); x = 0; memset(s1,0,1024);
			strncat(s2, &_trama[3], (_num - 3));
			x = atoi (s2);
			itoa (x, _x, 10);
			strcpy(s1, "F2;13;0;");
			strcat(s1, _x);

			memset(s2, 0, 1024);
			strncat(s2, &_trama[1], 2);
		
			if (strcmp(s2, "01") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "02") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "03") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "04") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "05") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "06") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "07") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "08") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "09") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "10") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "11") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "12") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "13") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "14") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "15") == 0) strcat(s1, ";;;"); 
			if (strcmp(s2, "16") == 0) strcat(s1, ";;;"); 
		
			printf(" QPrint NC Forma de Pago Parcial: %s\n", s1);
		
			memset(_buffer,0,1024);
			error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
			printf("buffer: %s\n",_buffer);
			_print->fncAnalyzeStatus(error, _buffer);
			_print->fncRegistrarLog(error, "NCCierreDevolucion", s1);
		
			y = y + x;
			if (y >= subtotal) Ejecutar(T(Estado_Actual,EVT_NC_FIN_CIERRE));
		}
	}

	void SM_Nota_de_Credito::GenerarNotaCredito()
	{
		printf("GenerarNotaCredito\n");

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Nota_de_Credito::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

	void SM_Nota_de_Credito::Fin()
	{
		printf("Fin\n");

		subtotal = 0;
		item = 0;
		x = 0;
		y = 0;
		memset(variable, 0, 4);
		memset(porcentaje, 0, 10);

		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

//DOCUMENTOS NO FISCALES
	
// DNF Texto
	SM_DNF_Texto::SM_DNF_Texto()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_DNF_Texto::~SM_DNF_Texto()
	{
	}

	void SM_DNF_Texto::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
		cont = 0;
	}

	Eventos SM_DNF_Texto::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_DNF_Texto::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_DNF_TEXTO) return EDO_DNF_TEXTO;
				break;
			case EDO_DNF_TEXTO:
				if(evento == TKN_DNF_TEXTO) return EDO_DNF_TEXTO;
				else return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_DNF_Texto::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_DNF_TEXTO: DNFTexto(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_DNF_Texto::Inicio()
	{
		//printf("Inicio SM_DNF_Texto\n");
	}

	void SM_DNF_Texto::DNFTexto()
	{
		//printf("DNFTexto\n");
		if (cont == 0) 
		{
			strcpy(s1, "F1;1"); 
			printf("QPrint, Abrir DNF Texto : %s\n", s1); 
			++cont;

			memset(_buffer,0,1024);
			error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
			printf("buffer: %s\n",_buffer);
			_print->fncAnalyzeStatus(error, _buffer);
			_print->fncRegistrarLog(error, "DNFTexto", s1);
		}

		strcpy(s1, "F1;3;\"");
		strncat(s1, &_trama[3], (_num - 3));
		strcat(s1, "\"");
		printf(" QPrint, DNF Texto: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "DNFTexto", s1);		
	}

	void SM_DNF_Texto::Fin()
	{
		strcpy(s1, "F1;2"); 
		printf(" QPrint, Cerrar DNF Texto : %s\n", s1); 
		cont = 0;

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);	
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "DNFTexto", s1);

		printf("Fin SM_DNF_Texto\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_DNF_Texto::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// DNF Apertura de Gaveta
	SM_DNF_Apertura_Gaveta::SM_DNF_Apertura_Gaveta()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_DNF_Apertura_Gaveta::~SM_DNF_Apertura_Gaveta()
	{
	}

	void SM_DNF_Apertura_Gaveta::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_DNF_Apertura_Gaveta::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_DNF_Apertura_Gaveta::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;
		
		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_DNF_APERTURA_GAVETA) return EDO_DNF_APERTURA_GAVETA;
				break;
			case EDO_DNF_APERTURA_GAVETA:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_DNF_Apertura_Gaveta::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_DNF_APERTURA_GAVETA: DNFAperturaGaveta(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_DNF_Apertura_Gaveta::Inicio()
	{
		//printf("Inicio SM_DNF_Apertura_Gaveta\n");
	}

	void SM_DNF_Apertura_Gaveta::DNFAperturaGaveta()
	{
		printf("DNFAperturaGaveta\n");

		strcpy(s1, "F2;11;6;1;\"APERTURA DE GAVETA\";;;;");
		printf(" QPrint, DNF Apertura de Gaveta: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "DNFAperturaGaveta", s1);
		
		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_DNF_Apertura_Gaveta::Fin()
	{
		printf("Fin SM_DNF_Apertura_Gaveta\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_DNF_Apertura_Gaveta::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// DNF PO y RA
	SM_DNF_PO_RA::SM_DNF_PO_RA()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_DNF_PO_RA::~SM_DNF_PO_RA()
	{
	}

	void SM_DNF_PO_RA::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_DNF_PO_RA::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_DNF_PO_RA::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_DNF_PO_RA) return EDO_DNF_PO_RA;
				break;
			case EDO_DNF_PO_RA:
				if(evento == TKN_DNF_FINALIZAR_PO_RA) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_DNF_PO_RA::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_DNF_PO_RA: DNF_PO_RA(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_DNF_PO_RA::Inicio()
	{
		//printf("Inicio SM_DNF_PO_RA\n");
	}

	void SM_DNF_PO_RA::DNF_PO_RA()
	{
		printf("DNF_PO_RA\n");

		strcpy(s1, "F2;10;");
		strcpy(s3, ""); 
		strncat(s2, &_trama[4], (_num - 4));
		x = atoi (s2);
		itoa (x, _x, 10);
		strcat(s3, _x);
		strcpy(s2, "");
		
		strncat(s2, &_trama[1], 1);
		if (strcmp(s2, "0") == 0) {strcat(s1, "1;"); strcat(s1, s3); strcat(s1, ";\"Retiro de Caja\";;;;");}
		if (strcmp(s2, "1") == 0) {strcat(s1, "2;"); strcat(s1, s3); strcat(s1, ";\"Fondo de Caja\";;;;");}
	}

	void SM_DNF_PO_RA::Fin()
	{
		printf("Fin SM_DNF_PO_RA\n");

		printf(" QPrint, DNF PO RA: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);	
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "DNF_PO_RA", s1);
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_DNF_PO_RA::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// DNF Imprimir Valor de Conf
	SM_DNF_Valor_Conf::SM_DNF_Valor_Conf()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_DNF_Valor_Conf::~SM_DNF_Valor_Conf()
	{
	}

	void SM_DNF_Valor_Conf::set_printer(Printer *print)
	{
		_print = print;
	}

	Eventos SM_DNF_Valor_Conf::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_DNF_Valor_Conf::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_DNF_PRINT_VALOR_CONF) return EDO_DNF_PRINT_VALOR_CONF;
				break;
			case EDO_DNF_PRINT_VALOR_CONF:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_DNF_Valor_Conf::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_DNF_PRINT_VALOR_CONF: DNFValorConf(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_DNF_Valor_Conf::Inicio()
	{
		//printf("Inicio SM_DNF_Valor_Conf\n");
	}

	void SM_DNF_Valor_Conf::DNFValorConf()
	{
		printf("DNFValorConf\n");

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_DNF_Valor_Conf::Fin()
	{
		printf("Fin SM_DNF_Valor_Conf\n");

		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_DNF_Valor_Conf::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// DNF Codigo de Barra
	SM_DNF_Codigo_Barra::SM_DNF_Codigo_Barra()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_DNF_Codigo_Barra::~SM_DNF_Codigo_Barra()
	{
	}

	void SM_DNF_Codigo_Barra::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_DNF_Codigo_Barra::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_DNF_Codigo_Barra::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_FACT_CODIGO_DE_BARRA) return EDO_DNF_CODIGO_BARRA;
				break;
			case EDO_DNF_CODIGO_BARRA:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_DNF_Codigo_Barra::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_DNF_CODIGO_BARRA: DNFCodigoBarra(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_DNF_Codigo_Barra::Inicio()
	{
		//printf("Inicio SM_DNF_Codigo_Barra\n");
	}

	void SM_DNF_Codigo_Barra::DNFCodigoBarra()
	{
		printf("DNFCodigoBarra\n");

		strcpy(s1, "F1;1"); 
		printf("QPrint, Abrir DNF: %s\n", s1); 

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "DNFCodigoBarra", s1);

		strcpy(s1, "F1;7;");
		strncat(s1, &_trama[1], (_num - 1));
		printf(" QPrint Codigo de Barra: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "DNFCodigoBarra", s1);

		strcpy(s1, "F1;2"); 
		printf("QPrint, Cerrar DNF: %s\n", s1); 

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "DNFCodigoBarra", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_DNF_Codigo_Barra::Fin()
	{
		printf("Fin SM_DNF_Codigo_Barra\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_DNF_Codigo_Barra::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Display Mensaje
	SM_Display_Mensaje::SM_Display_Mensaje()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_Display_Mensaje::~SM_Display_Mensaje()
	{
	}

	void SM_Display_Mensaje::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_Display_Mensaje::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Display_Mensaje::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_DISPLAY_MENSAJE) return EDO_DISPLAY_MENSAJE;
				break;
			case EDO_DISPLAY_MENSAJE:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Display_Mensaje::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_DISPLAY_MENSAJE: DisplayMensaje(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Display_Mensaje::Inicio()
	{
		//printf("Inicio SM_Display_Mensaje\n");
	}

	void SM_Display_Mensaje::DisplayMensaje()
	{
		printf("DisplayMensaje\n");

		strcpy (s1, "F1;6;2;1;\"");
		strncat (s1, &_trama[2], (_num - 2));
		strcat (s1, "\"");
		printf(" QPrint, Display Mensaje: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "DisplayMensaje", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Display_Mensaje::Fin()
	{
		printf("Fin SM_Display_Mensaje\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Display_Mensaje::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Status
	SM_Status::SM_Status()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_Status::~SM_Status()
	{
	}

	void SM_Status::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_Status::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Status::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_STATUS) return EDO_STATUS;
				break;
			case EDO_STATUS:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Status::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_STATUS: Status(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Status::Inicio()
	{
		//printf("Inicio SM_Status\n");
	}

	void SM_Status::Status()
	{
		printf("Status\n");

		strcpy(s1, "F0;3");
		printf(" QPrint, Status: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "Status", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Status::Fin()
	{
		printf("Fin SM_Status\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Status::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Reporte X
	SM_Reporte_X::SM_Reporte_X()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_Reporte_X::~SM_Reporte_X()
	{
	}

	void SM_Reporte_X::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_Reporte_X::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Reporte_X::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_REPORTE_X) return EDO_REPORTE_X;
				break;
			case EDO_REPORTE_X:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Reporte_X::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_REPORTE_X: ReporteX(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Reporte_X::Inicio()
	{
		//printf("Inicio SM_Reporte_X\n");		
	} 

	void SM_Reporte_X::ReporteX()
	{
		printf("ReporteX\n");

		strcpy(s1, "F3;1;1");
		printf(" QPrint, ReporteX: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "ReporteX", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Reporte_X::Fin()
	{
		printf("Fin SM_Reporte_X\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Reporte_X::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Reporte Z
	SM_Reporte_Z::SM_Reporte_Z()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_Reporte_Z::~SM_Reporte_Z()
	{
	}

	void SM_Reporte_Z::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_Reporte_Z::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Reporte_Z::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_REPORTE_Z) return EDO_REPORTE_Z;
				break;
			case EDO_REPORTE_Z:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Reporte_Z::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_REPORTE_Z: ReporteZ(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Reporte_Z::Inicio()
	{
		//printf("Inicio SM_Reporte_Z\n");
	}

	void SM_Reporte_Z::ReporteZ()
	{
		printf("ReporteZ\n");
		
		strcpy(s1, "F3;1");
		printf(" QPrint, ReporteZ: %s\n", s1);

		memset(_buffer,0,100);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);	
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "ReporteZ", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Reporte_Z::Fin()
	{
		printf("Fin SM_Reporte_Z\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Reporte_Z::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Reporte Memoria Fiscal por Fecha
	SM_MFiscal_Fecha::SM_MFiscal_Fecha()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_MFiscal_Fecha::~SM_MFiscal_Fecha()
	{
	}

	void SM_MFiscal_Fecha::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_MFiscal_Fecha::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_MFiscal_Fecha::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_REPORTE_MFISCAL_FECHA) return EDO_REPORTE_MFISCAL_FECHA;
				break;
			case EDO_REPORTE_MFISCAL_FECHA:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_MFiscal_Fecha::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_REPORTE_MFISCAL_FECHA: MFiscalFecha(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_MFiscal_Fecha::Inicio()
	{
		//printf("Inicio SM_MFiscal_Fecha\n");
	}

	void SM_MFiscal_Fecha::MFiscalFecha()
	{
		printf("MFiscalFecha\n");

		strcpy(s1, "F3;2;20");
		strncat(s1, &_trama[7], 2); //Año
		strncat(s1, &_trama[5], 2); //Mes
		strncat(s1, &_trama[3], 2); //Día
		strcat(s1, ";20");
		strncat(s1, &_trama[13], 2); //Año
		strncat(s1, &_trama[11], 2); //Mes
		strncat(s1, &_trama[9], 2); //Día

		printf(" QPrint, Impresion de Memoria Fiscal por Fecha: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);	
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "MFiscalFecha", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_MFiscal_Fecha::Fin()
	{
		printf("Fin SM_MFiscal_Fecha\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_MFiscal_Fecha::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Reporte Memoria Fiscal por Numero
	SM_MFiscal_Numero::SM_MFiscal_Numero()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_MFiscal_Numero::~SM_MFiscal_Numero()
	{
	}

	void SM_MFiscal_Numero::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_MFiscal_Numero::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_MFiscal_Numero::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_REPORTE_MFISCAL_NUMERO) return EDO_REPORTE_MFISCAL_NUMERO;
				break;
			case EDO_REPORTE_MFISCAL_NUMERO:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_MFiscal_Numero::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_REPORTE_MFISCAL_NUMERO: MFiscalNumero(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_MFiscal_Numero::Inicio()
	{
		//printf("Inicio SM_MFiscal_Numero\n");
	}

	void SM_MFiscal_Numero::MFiscalNumero()
	{
		printf("MFiscalNumero\n");

		strcpy(s1, "F3;3;");
		strncat(s2, &_trama[5], 4);
		int1 = atoi(s2);
		itoa (int1, s2, 10);
		strcat(s1, s2);

		strcpy(s2, "");
		strncat(s2, &_trama[11], 4);
		int1 = atoi(s2);
		itoa (int1, s2, 10);
		strcat(s1, ";");
		strcat(s1, s2);

		printf(" QPrint, Impresion de Memoria Fiscal por Numero: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);	
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "MFiscalNumero", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_MFiscal_Numero::Fin()
	{
		printf("Fin SM_MFiscal_Numero\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_MFiscal_Numero::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Reimpresión de Documentos por Fecha
	SM_Reimpresion_Fecha::SM_Reimpresion_Fecha()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_Reimpresion_Fecha::~SM_Reimpresion_Fecha()
	{
	}

	void SM_Reimpresion_Fecha::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}

	Eventos SM_Reimpresion_Fecha::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Reimpresion_Fecha::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_REIMPRESION_DOC_POR_FECHA) return EDO_REIMPRESION_DOC_FECHA;
				break;
			case EDO_REIMPRESION_DOC_FECHA:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Reimpresion_Fecha::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_REIMPRESION_DOC_FECHA: ReimpresionDocFecha(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Reimpresion_Fecha::Inicio()
	{
		//printf("Inicio SM_Reimpresion_Fecha\n");
	}

	void SM_Reimpresion_Fecha::ReimpresionDocFecha()
	{
		printf("ReimpresionDocFecha\n");

		strcpy (s2, "");
		strncat(s2, &_trama[1], 1);

		
		if (strcmp(s2, "c") == 0) strcpy(s1, "F3;8;124;0;20");

		strcpy (s2, "");
		strncat(s2, &_trama[3], 6);
		strcat(s1, s2);
		strcat(s1, ";20");
		strcpy (s2, "");
		strncat(s2, &_trama[10], 6);
		strcat(s1, s2);

		printf(" QPrint, Impresion de Nota de Credito por Fecha: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		printf("buffer: %s\n",_buffer);	
		_print->fncAnalyzeStatus(error, _buffer);
		_print->fncRegistrarLog(error, "ReimpresionDocFecha", s1);

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Reimpresion_Fecha::Fin()
	{
		printf("Fin SM_Reimpresion_Fecha\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Reimpresion_Fecha::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Reimpresión de Documentos por Numero
	SM_Reimpresion_Numero::SM_Reimpresion_Numero()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_Reimpresion_Numero::~SM_Reimpresion_Numero()
	{
	}

	void SM_Reimpresion_Numero::set_printer(Printer *print, char * buffer)
	{
		_print = print;
		_buffer = buffer;
	}


	Eventos SM_Reimpresion_Numero::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Reimpresion_Numero::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_REIMPRESION_DOC_POR_NUMERO) return EDO_REIMPRESION_DOC_NUMERO;
				break;
			case EDO_REIMPRESION_DOC_NUMERO:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Reimpresion_Numero::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_REIMPRESION_DOC_NUMERO: ReimpresionDocNumero(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Reimpresion_Numero::Inicio()
	{
		//printf("Inicio SM_Reimpresion_Numero\n");
	}

	void SM_Reimpresion_Numero::ReimpresionDocNumero()
	{
		printf("ReimpresionDocNumero\n");

		strcpy (s2, "");
		strncat(s2, &_trama[1], 1);
		
		if (strcmp(s2, "F") == 0) strcpy(s1, "F3;7;140;0;");

		strcpy (s2, "");
		strncat(s2, &_trama[2], 7);
		int1 = atoi(s2);
		itoa (int1, s2, 10);
		strcat(s1, s2);
		
		strcat(s1, ";");
		strcpy (s2, "");
		strncat(s2, &_trama[9], 7);
		int1 = atoi(s2);
		itoa (int1, s2, 10);
		strcat(s1, s2);

		printf(" QPrint, Impresion de Factura por Numero: %s\n", s1);

		memset(_buffer,0,1024);
		error = _print->fncSendCommand(reinterpret_cast<BYTE*>(&s1[0]), reinterpret_cast<BYTE*>(_buffer));
		_print->fncRegistrarLog(error, "ReimpresionDocNumero", s1);
		_print->fncAnalyzeStatus(error, _buffer);
		printf("buffer: %s\n",_buffer);	

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Reimpresion_Numero::Fin()
	{
		printf("Fin SM_Reimpresion_Numero\n");
		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Reimpresion_Numero::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

// Impresión de Estado de Memoria de Auditoria
	SM_Print_Edo_MAuditoria::SM_Print_Edo_MAuditoria()
	{
		Estado_Actual = EDO_INICIO;
		Estado_Previo = EDO_INICIO;
	}

    SM_Print_Edo_MAuditoria::~SM_Print_Edo_MAuditoria()
	{
	}

	void SM_Print_Edo_MAuditoria::set_printer(Printer *print)
	{
		_print = print;
	}

	Eventos SM_Print_Edo_MAuditoria::Check(Eventos evt, const char* trama, long num)
	{
		_trama = trama;
		_num = num;

		return Ejecutar(T(Estado_Actual,evt));
	}	
	
	Estados SM_Print_Edo_MAuditoria::T(Estados initial_state, Eventos evento) 	
	{
		Evento_Actual = evento;

		switch(initial_state) 
		{
			case EDO_INICIO:
				if(evento == TKN_PRINT_EDO_MEMORIA_AUDITORIA) return EDO_PRINT_EDO_MEMORIA_AUDITORIA;
				break;
			case EDO_PRINT_EDO_MEMORIA_AUDITORIA:
				if(evento == EVT_NEUTRO) return EDO_FIN;
				break;
			case EDO_FIN:
				if(evento == EVT_FINALIZADO) return EDO_INICIO;
				break;
		}

		return EDO_INVALIDO;
	}

	Eventos SM_Print_Edo_MAuditoria::Ejecutar(Estados state)
	{
		if(state!=EDO_INVALIDO) 
		{
			Estado_Previo = Estado_Actual;
			Estado_Actual = state;
		}
		else Evento_Actual = EVT_ERROR;
    
		switch(state) 
		{
			case EDO_INICIO: Inicio(); break;
			case EDO_PRINT_EDO_MEMORIA_AUDITORIA: PrintEdoMAuditoria(); break;
			case EDO_FIN: Fin(); break;
			default: EstadoInvalido(); break; // NEUTRO
		}
		return Evento_Actual;
	}

	void SM_Print_Edo_MAuditoria::Inicio()
	{
		//printf("Inicio SM_Print_Edo_MAuditoria\n");
	}

	void SM_Print_Edo_MAuditoria::PrintEdoMAuditoria()
	{
		printf("PrintEdoMAuditoria\n");

		Ejecutar(T(Estado_Actual,EVT_NEUTRO));
	}

	void SM_Print_Edo_MAuditoria::Fin()
	{
		printf("Fin SM_Print_Edo_MAuditoria\n");

		Ejecutar(T(Estado_Actual,EVT_FINALIZADO));
	}

	void SM_Print_Edo_MAuditoria::EstadoInvalido()
	{
		printf("EstadoInvalido\n");
	}

}	// Namespace Quorion