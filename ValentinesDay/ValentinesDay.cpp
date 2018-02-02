// ValentinesDay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "tfhkaif.h"
//#include <stdio.h>
#include <conio.h>	//getch
#include <iostream.h>
#include <iostream>
//#include <fstream.h>
//#include <sstream>
//#include <string.h>

typedef int (__stdcall * pICFUNC1)(BYTE *rec, BYTE *weft);									//SendCommand
typedef int (__stdcall * pICFUNC2)(WORD comPort, WORD baudRate);							//OpenComPort
typedef int (__stdcall * pICFUNC3)(void);													//CloseComPort
typedef int (__stdcall * pICFUNC4)(BYTE ip0, BYTE ip1, BYTE ip2, BYTE ip3, WORD reg = 0);	//OpenIPPort
typedef int (__stdcall * pICFUNC5)(void);													//CloseIPPort
typedef int (__stdcall * pICFUNC6)(char *);
//- Encapulado
//typedef bool (__stdcall * pICFUNB1)(char* lpPortName);	
//typedef bool (__stdcall * pICFUNB2)(void);
//typedef bool (__stdcall * pICFUNB3)(int* status, int* error, char* cmd);												//GetVersion
typedef bool (__stdcall * pICFUNB1)(char* lpPortName);									//OpenFpctrl	
typedef bool (__stdcall * pICFUNB2)(void);												//CloseFpctrl
typedef bool (__stdcall * pICFUNB3)(int* status, int* error, char* cmd);				//SendCmd
typedef bool (__stdcall * pICFUNB4)(void);												//CheckFprinter
typedef bool (__stdcall * pICFUNB5)(int* status, int* error);							//ReadFpStatus
typedef bool (__stdcall * pICFUNB6)(int* status, int* error, char* buffer);				//SendNCmd
typedef bool (__stdcall * pICFUNB7)(int* status, int* error, char* file);				//SendFileCmd
typedef bool (__stdcall * pICFUNB8)(int* status, int* error, char* cmd, char* file);	//UploadReportCmd
typedef bool (__stdcall * pICFUNB9)(int* status, int* error, char* cmd, char* file);	//UploadStatusCmd



int CallMyDLL(void) 
{ 
    /* get handle to dll */ 
   HINSTANCE hGetProcIDDLL = LoadLibrary(L"C:\\pvx\\dll\\quorion.dll"); 

   /* get pointer to the function in the dll*/ 
   FARPROC lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"GetVer"); 

   /* 
      Define the Function in the DLL for reuse. This is just prototyping the dll's function. 
      A mock of it. Use "stdcall" for maximum compatibility. 
   */ 
   typedef int (__stdcall * pICFUNC)(char *); 

   pICFUNC GetVersion = pICFUNC(lpfnGetProcessID); 

   char *ver = (char *)malloc(30 * sizeof(char));
   strcpy(ver, "");

   /* The actual call to the function contained in the dll */ 
   int intMyReturnVal = GetVersion(ver); 

   cout << ver << endl;

   /* Release the Dll */ 
   FreeLibrary(hGetProcIDDLL); 

   /* The return val from the dll */ 
    return intMyReturnVal; 
} 

int main(int argc, char* argv[])
{
   HINSTANCE hGetProcIDDLL = LoadLibrary(L"C:\\dll\\tfhkaif.dll"); 
   FARPROC lpfnGetProcessID = NULL;
   
   lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"SendCommand"); 
   pICFUNC1 SendCommand = pICFUNC1(lpfnGetProcessID);

   lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"OpenComPort"); 
   pICFUNC2 OpenComPort = pICFUNC2(lpfnGetProcessID);

   lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"CloseComPort"); 
   pICFUNC3 CloseComPort = pICFUNC3(lpfnGetProcessID);

   lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"OpenIPPort"); 
   pICFUNC4 OpenIPPort = pICFUNC4(lpfnGetProcessID);

   lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"CloseIPPort"); 
   pICFUNC5 CloseIPPort = pICFUNC5(lpfnGetProcessID);

   lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"GetVer"); 
   pICFUNC6 GetVer = pICFUNC6(lpfnGetProcessID);

   //- Encapsulado
   lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"OpenFpctrl"); 
   pICFUNB1 OpenFpctrl = pICFUNB1(lpfnGetProcessID);

   lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"CloseFpctrl"); 
   pICFUNB2 CloseFpctrl = pICFUNB2(lpfnGetProcessID);

   lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"SendCmd"); 
   pICFUNB3 SendCmd = pICFUNB3(lpfnGetProcessID);

	lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"CheckFprinter"); 
	pICFUNB4 CheckFprinter = pICFUNB4(lpfnGetProcessID);

	lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"ReadFpStatus"); 
	pICFUNB5 ReadFpStatus = pICFUNB5(lpfnGetProcessID);

	lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"SendNCmd"); 
	pICFUNB6 SendNCmd = pICFUNB6(lpfnGetProcessID);

	lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"SendFileCmd"); 
	pICFUNB7 SendFileCmd = pICFUNB7(lpfnGetProcessID);

	lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"UploadReportCmd"); 
	pICFUNB8 UploadReportCmd = pICFUNB8(lpfnGetProcessID);

	lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"UploadStatusCmd"); 
	pICFUNB9 UploadStatusCmd = pICFUNB9(lpfnGetProcessID);

   /*
	char *resps = (char*)malloc(256 * sizeof(char));	
	memset(resps, 0, 256);	
	int myname = HelloWorld("Luis Jimenez", resps);
	cout << "Hello World! "  << resps << endl;
	*/
	//-- Comunicación COM QPrint -------------------------------------------------//
	/*
	int bError = -1;
	int rxcount = 0;
	//BYTE rxArray[1024];
	//-
	BYTE rx = NULL;			
	BYTE rxTrama[1024];	
	
	char *val1 = (char *)malloc(100 * sizeof(char));
	strcpy(val1, "F1;1");	

	char *val2 = (char *)malloc(100 * sizeof(char));
	strcpy(val2, "F1;2");

	char *val3 = (char *)malloc(100 * sizeof(char));
	strcpy(val3, "F1;3;\"Hola Mundo\"");	

	int bOpen = OpenComPort(3,6);	
	cout << "OpenComPort: "  << bOpen << endl;

	memset(rxTrama, 0, 1024);
	bError = SendCommand(reinterpret_cast<unsigned char *>(val1), rxTrama);	
	
	//rxcount = WeftLength();	
	//if(!bError && rxcount > 0)
	//{
	//	int i=0;
	//	memset(rxArray, 0, 1024);
	//	while(ReadData(&rx) > -1)
	//		rxArray[i++] = rx;
	//}
	
	printf("trama: %d \n", bError);	
	printf("trama: %s \n", rxTrama);	

	memset(rxTrama, 0, 1024);
	bError = SendCommand(reinterpret_cast<unsigned char *>(val3), rxTrama);

	memset(rxTrama, 0, 1024);
	bError = SendCommand(reinterpret_cast<unsigned char *>(val2), rxTrama);

	int bClose = CloseComPort();
	cout << "CloseComPort: "  << bClose << endl;
	getch();
	return 0;
	*/
	//-- Comunicación LAN QPrint -------------------------------------------------//
	/*
	int bError = -1;
	int rxcount = 0;
	BYTE rxArray[1024];
	//-
	BYTE rx = NULL;			
	BYTE rxTrama[1024];	

	BYTE cmd[] = "F0";
	
	char *val1 = (char *)malloc(100 * sizeof(char));
	strcpy(val1, "F1;1");	

	char *val2 = (char *)malloc(100 * sizeof(char));
	strcpy(val2, "F1;2");

	char *val3 = (char *)malloc(100 * sizeof(char));
	strcpy(val3, "F1;3;\"Hola Mundo\"");	

	char *ver = (char *)malloc(30 * sizeof(char));
	strcpy(ver, "");
	
	//CallMyDLL();
	//getch();
	
	GetVer(ver);
	cout << ver << endl;
	
	int bOpen = OpenIPPort(192,168,0,10,1);	
	cout << "OpenIPPort: "  << bOpen << endl;

	memset(rxTrama, 0, 1024);
	bError = SendCommand(cmd, rxTrama);	
	
	//rxcount = WeftLength();	
	//if(!bError && rxcount > 0)
	//{
	//	int i=0;
	//	memset(rxArray, 0, 1024);
	//	while(ReadData(&rx) > -1)
	//		rxArray[i++] = rx;
	//}
	
	printf("trama: %s \n", rxTrama);	

	memset(rxTrama, 0, 1024);
	bError = SendCommand(reinterpret_cast<unsigned char *>(val1), rxTrama);

	memset(rxTrama, 0, 1024);
	bError = SendCommand(reinterpret_cast<unsigned char *>(val3), rxTrama);

	memset(rxTrama, 0, 1024);
	bError = SendCommand(reinterpret_cast<unsigned char *>(val2), rxTrama);

	int bClose = CloseIPPort();
	cout << "CloseIPPort: "  << bClose << endl;
	getch();
	return 0;
	*/
	//-- Bixolon ----------------------------------------------------------//
	
	int status = 0;
	int error = 0;
	char *cmd = (char *)malloc(100 * sizeof(char));

	//int bOpen = OpenComPort(3,6);	
	//cout << "OpenComPort: "  << bOpen << endl;

	bool bxOpen = OpenFpctrl("COM3");
	cout << "OpenFpctrl: "  << bxOpen << endl;
	//getch();

/*
//// CheckFprinter ////
	bool bxcheck = CheckFprinter();
	cout << "\nCheck: "  << bxcheck << endl;


	bxOpen = OpenFpctrl("COM3");
	cout << "OpenFpctrl: "  << bxOpen << endl;
*/  
/*
	memset(cmd,0,100);
	strcpy(cmd,"PC0112345Cajero");	//(CONFIGURACION) TKN_CONF_DATOS_DEL_CAJERO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"PE01Efectivo");			//(CONFIGURACION) TKN_CONF_NOMBRES_FORMAS_DE_PAGO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"PE05Check");			//(CONFIGURACION) TKN_CONF_NOMBRES_FORMAS_DE_PAGO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"PE04TARJ CREDITO");			//(CONFIGURACION) TKN_CONF_NOMBRES_FORMAS_DE_PAGO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"PE13Credit Card");			//(CONFIGURACION) TKN_CONF_NOMBRES_FORMAS_DE_PAGO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"PF154500");						//(CONFIGURACION) TKN_CONF_HORA
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"PG061012");						//(CONFIGURACION) TKN_CONF_FECHA
	SendCmd(&status, &error, cmd);
	
	memset(cmd,0,100);
	strcpy(cmd,"PT212002080022200");			//(CONFIGURACION) TKN_CONF_DEL_IVA
	SendCmd(&status, &error, cmd);


	memset(cmd,0,100);
//	strcpy(cmd,"Pt");							//(CONFIGURACION) TKN_CONF_DEL_IVA_MEMORIA_FISCAL
//	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"PH01Encabeza 01");		//(CONFIGURACION) TKN_CONF_ENCABEZADO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"PH02Encabeza 02");		//(CONFIGURACION) TKN_CONF_ENCABEZADO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"PH91HAY UN CAMINO");	//(CONFIGURACION) TKN_CONF_PIE_DE_FACTURA
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"PH92GRACIAS POR SU VISITA");	//(CONFIGURACION) TKN_CONF_PIE_DE_FACTURA
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"512345");									//CAJERO INICIO TKN_CAJERO_INICIO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"6");										//CAJERO FIN TKN_CAJERO_FIN
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"i01Emitido Por:N&M SUMINISTRO´S, C.A");		//DATO DE CLIENTE TKN_DATOS_CLIENTE
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"i01Raz/Soc.: GREGORI ANDERSON");			//DATO DE CLIENTE TKN_DATOS_CLIENTE
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"i02Raz/Soc.: GREGORI ANDERSON ARRIECHE GARCIA SILVA DE LOS ");				//DATO DE CLIENTE TKN_DATOS_CLIENTE
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"i03COJELONES");								//DATO DE CLIENTE TKN_DATOS_CLIENTE
	SendCmd(&status, &error, cmd);
	
	memset(cmd,0,100);
	strcpy(cmd,"i02Cedula/Rif: V-18421171");				//DATO DE CLIENTE TKN_DATOS_CLIENTE
	SendCmd(&status, &error, cmd);
	
	memset(cmd,0,100);
	strcpy(cmd,"i09Ser. Imp. Fac. Asc. Z1B8021957");		//DATO DE CLIENTE TKN_DATOS_CLIENTE
	SendCmd(&status, &error, cmd);
	*/

 	memset(cmd,0,100);	
	strcpy(cmd,"!000002132300002562Nombre Articulo 1");		//(FACTURA) TKN_FACT_REGISTRO_PRODUCTO
	SendCmd(&status, &error, cmd);
	
	memset(cmd,0,100);	
	strcpy(cmd,"!000003466700002731Nombre Articulo 2");		//(FACTURA) TKN_FACT_REGISTRO_PRODUCTO
	SendCmd(&status, &error, cmd);
		
	/*
 	memset(cmd,0,100);	
	strcpy(cmd,"!000002000000001000Nombre Articulo 1");		//(FACTURA) TKN_FACT_REGISTRO_PRODUCTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);	
	strcpy(cmd,"!000002000000001000Nombre Articulo 2");		//(FACTURA) TKN_FACT_REGISTRO_PRODUCTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"@OFERTA ESPECIAL OFERTA ESPECIAL OFERTA");	//(FACTURA) TKN_FACT_DESCRIPCION
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);	
	strcpy(cmd,"!000002000000001000");		//(FACTURA) TKN_FACT_REGISTRO_PRODUCTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"@COOPERATIVA LOS SINTECHOS DE SANTA ROSA");	//(FACTURA) TKN_FACT_DESCRIPCION
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"@DEL TUY BARQUISIMETO ESTADO LARA");	//(FACTURA) TKN_FACT_DESCRIPCION
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);	
	strcpy(cmd,"!000002000000001000");		//(FACTURA) TKN_FACT_REGISTRO_PRODUCTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"k");										//(FACTURA) TKN_FACT_CORRECCION
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);	
	strcpy(cmd,"!000004500000001000Nombre Articulo 4");		//(FACTURA) TKN_FACT_REGISTRO_PRODUCTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"p-1000");									//(FACTURA) TKN_FACT_RECARGO_O_DESCUENTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);	
	strcpy(cmd,"!000002500000001000Nombre Articulo 5");		//(FACTURA) TKN_FACT_REGISTRO_PRODUCTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"p+1000");									//(FACTURA) TKN_FACT_RECARGO_O_DESCUENTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);	
	strcpy(cmd,"!000011700000001000Nombre Articulo 6");		//(FACTURA) TKN_FACT_REGISTRO_PRODUCTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"¡000002000000001000Nombre Articulo 6");		//(FACTURA) TKN_FACT_ANULACION_ITEM
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"3");										//(FACTURA) TKN_FACT_SUBTOTAL
	SendCmd(&status, &error, cmd);
	
	memset(cmd,0,100);
	strcpy(cmd,"p+1000");									//(FACTURA) TKN_FACT_RECARGO_O_DESCUENTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"¡000003500000001000PLU 1");					//(FACTURA) TKN_FACT_ANULACION_ITEM
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"7");										//(FACTURA) TKN_FACT_ANULACION_FACTURA
	SendCmd(&status, &error, cmd);
*/
	memset(cmd,0,100);
	strcpy(cmd,"101");										//(FACTURA) TKN_FACT_PAGO_DIRECTO
	SendCmd(&status, &error, cmd);
/*
	memset(cmd,0,100);
	strcpy(cmd,"201000000050000");							//(FACTURA) TKN_FACT_PAGO_PARCIAL
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"205000000050000");							//(FACTURA) TKN_FACT_PAGO_PARCIAL
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"209000000017000");							//(FACTURA) TKN_FACT_PAGO_PARCIAL
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"y123456789012");							//(FACTURA) TKN_FACT_CODIGO_DE_BARRA
	SendCmd(&status, &error, cmd);
	
	memset(cmd,0,100);
	strcpy(cmd,"i01Razon Social:");				//DATO DE CLIENTE TKN_DATOS_CLIENTE
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"d1000001000000001000PLU 1");	//(NOTA DE CREDITO) TKN_NC_REGISTRO_PRODUCTO
	SendCmd(&status, &error, cmd);
	
	memset(cmd,0,100);
	strcpy(cmd,"ä1000001000000001000PLU 1");	//(NOTA DE CREDITO) TKN_NC_ANULACION_ITEM
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"d1000001000000001000PLU 1");	//(NOTA DE CREDITO) TKN_NC_REGISTRO_PRODUCTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"f01000000001080");				//(NOTA DE CREDITO) TKN_NC_CIERRE_DEVOLUCION
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"201000000005000");				//(NOTA DE CREDITO) TKN_NC_CIERRE_DEVOLUCION
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"0");											//(DNF) TKN_DNF_APERTURA_GAVETA
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"81$Prueba de documento No Fiscal Expandida");	//(DNF) TKN_DNF_TEXTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"802CORTE TOTAL (Z) NRO.: 3833");	//(DNF) TKN_DNF_TEXTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"81$Prueba de documento No Fiscal Expandida");	//(DNF) TKN_DNF_TEXTO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"0");											//(DNF) TKN_DNF_APERTURA_GAVETA
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"0");											//(DNF) TKN_DNF_APERTURA_GAVETA
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"0");											//(DNF) TKN_DNF_APERTURA_GAVETA
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"0");											//(DNF) TKN_DNF_APERTURA_GAVETA
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"9001000000010000");								//(DNF) TKN_DNF_PO_RA
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"t");											//(DNF) TKN_DNF_FINALIZAR_PO_RA
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"D");											//(DNF) TKN_DNF_PRINT_VALOR_CONF
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"PIMensaje en el display");		//(DISPLAY) TKN_DISPLAY_MENSAJE
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"S2");							//(STATUS) TKN_STATUS
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"I0X");					//(REPORTE) TKN_REPORTE_X
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"I0Z");					//(REPORTE) TKN_REPORTE_Z
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"I2A011012011012");		//(REPORTE) TKN_REPORTE_MFISCAL_FECHA
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"I3A000023000023");		//(REPORTE) TKN_REPORTE_MFISCAL_NUMERO
	SendCmd(&status, &error, cmd);

	memset(cmd,0,100);
	strcpy(cmd,"Rc01210030121003");		//(REIMPRESION) TKN_REIMPRESION_DOC_POR_FECHA	
	SendCmd(&status, &error, cmd);
	
	memset(cmd,0,100);
	strcpy(cmd,"RF00001180000118");		//(REIMPRESION) TKN_REIMPRESION_DOC_POR_NUMERO
	SendCmd(&status, &error, cmd);
	
	memset(cmd,0,100);
	strcpy(cmd,"E");					//(IMPRESION) TKN_PRINT_EDO_MEMORIA_AUDITORIA
	SendCmd(&status, &error, cmd); 
	
	memset(cmd,0,100);
	strcpy(cmd,"PJ0101");			
	SendCmd(&status, &error, cmd); 
*/
/*
//// CheckFprinter ////
	bool bxcheck = CheckFprinter();
	cout << "\nCheck: "  << bxcheck << endl;
*/
/*
//// SendNCmd ////
	FILE *origen = fopen("archivo.dat","r");
    char letra;
	char buffer[1024];
	memset(buffer,0,1024);

	do
	{
		letra=getc(origen);
		//printf( "%c",letra );
		strncat(buffer,&letra,1);		
	}	
	while (feof(origen)==0);
	//printf("%s\n",buffer);

	SendNCmd(&status, &error, buffer);
*/
/*
//// SendFileCmd ////

	char file[1024];
	memset(file,0,1024);
	strcpy(file, "QPrint\\RefInterna0000000042.dat");

	SendFileCmd(&status, &error, file);

	printf("Status: %i\n", status);
	printf("Error: %i\n", error);

	memset(file,0,1024);
	strcpy(file, "QPrint\\RefInterna0000000043.dat");

	SendFileCmd(&status, &error, file);

	printf("Status: %i\n", status);
	printf("Error: %i\n", error);
*/
/*
//// UploadReportCmd ////
	char file[1024];
	memset(file,0,1024);
//	strcpy(cmd,"U2A041112051112"); //Reporte Z
//	strcpy(file,"C:\\dll\\Bix_ReporteZ.txt");

	strcpy(cmd,"U0X"); //Reporte X
	strcpy(file,"C:\\dll\\Bix_ReporteX.txt");

 	bool bxUploadReportCmd = UploadReportCmd(&status, &error, cmd, file);
	cout << "UploadReportCmd: "  << bxUploadReportCmd << endl;
	printf("Status: %i\n", status);
	printf("Error: %i\n", error);
*/
/*
//// ReadFpStatus ////
	bool bxReadFpStatus = ReadFpStatus(&status, &error);
	cout << "ReadFpStatus: "  << bxReadFpStatus << endl;
	printf("Status: %i\n", status);
	printf("Error: %i\n", error);
*/

//// UploadStatusCmd ////
	char file[30];
	memset(file,0,30);
	strcpy(cmd,"S1");
	strcpy(file,"C:\\dll\\Status1.txt");
	bool bxUploadStatusCmd = UploadStatusCmd(&status, &error, cmd, file);
	cout << "UploadStatusCmd: "  << bxUploadStatusCmd << endl;
	printf("Error %i\n",error);
	printf("Status %i\n",status);


	bool bxClose = CloseFpctrl();
	cout << "CloseFpctrl: "  << bxClose << endl;	


	getch();
	return 0;	
}