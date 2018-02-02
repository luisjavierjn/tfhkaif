// tfhkaif.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include "protocol.h"
#include "printer.h"

#include <stdio.h>
#include <string.h>
//#include <assert.h>
//#include <WTypes.h>
//#include <oleauto.h>
//#include <comutil.h>
//#include <tchar.h>
//#include <stdlib.h>
#include <assert.h>
#include <map>
#include <iostream>
//#include <sstream>
//#include <istream>
//#include <string>
//#include <iomanip>
//#include <strstream>
#include <fstream>

#include "char_array_buffer.hpp"
//#include "output_buffer.hpp"

//using namespace std;
using namespace Quorion;



//_bstr_t *bstrStart;
//WCHAR *wszBuff;
struct ltstr
{
  bool operator()(const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) < 0;
  }
};

struct ltint 
{
  bool operator() (const int& x, const int& y) const
  {
	return x < y;
  }
};
/*
typedef std::map<char*, char*, ltstr> mid; //Map ID
mid translator;
*/
typedef std::map<int, char*, ltint> mfits; //Map From Int To String
mfits errQprint;
mfits errBixolon;

typedef std::multimap<int, int, ltint> mmid; //MultiMap ID
mmid mapErrors;

Printer print;
Protocol Lexer(&print);

//// Inicializacion ////
int comPort = 0;
int var = 0;
char strPort[5];

// Variables DLL Seniat 16 //
char * identificadorMarca = (char *)malloc(10 * sizeof(char));
char * identificadorModelo = (char *)malloc(10 * sizeof(char));
char * puertoConexion = (char *)malloc(5 * sizeof(char)); 
char * nombreArchivoSalidaEnca = (char *)malloc(1024 * sizeof(char)); 
char * nombreArchivoSalidaMF = (char *)malloc(1024 * sizeof(char));
char * fechaDesde = (char *)malloc(12 * sizeof(char));
char * fechaHasta = (char *)malloc(12 * sizeof(char));
char * archivoErrores = (char *)malloc(100 * sizeof(char));
char * archivofuncion = (char *)malloc(100 * sizeof(char));
char * archivoAlicuotas = (char *)malloc(100 * sizeof(char));
char * tramaRIF = (char *)malloc(12 * sizeof(char));

char * archivodepruebaZ = (char *)malloc(100 * sizeof(char));
char * archivodepruebaS1 = (char *)malloc(100 * sizeof(char));

typedef bool (__stdcall * pICFUNSen1) (char *identificadorMarca, char *identificadorModelo, char *puertoConexion);											//verificarConexion
typedef bool (__stdcall * pICFUNSen2) (char *identificadorMarca, char *identificadorModelo, char *nombreArchivoSalida);										//obtenerEncabezado
typedef bool (__stdcall * pICFUNSen3) (char *identificadorMarca, char *identificadorModelo, char *fechaDesde, char *fechaHasta, char *nombreArchivoSalida); //leerMemoriaFiscal
typedef bool (__stdcall * pICFUNSen4) (char *identificadorMarca, char *identificadorModelo, char *fechaDesde, char *fechaHasta, char *nombreArchivoSalida);	//leerEJ

HINSTANCE hGetProcIDDLL;
FARPROC lpfnGetProcessID;
pICFUNSen1 verificarConexion;
pICFUNSen2 obtenerEncabezado;
pICFUNSen3 leerMemoriaFiscal;
pICFUNSen4 leerEJ;

void LoadSeniat()
{
	hGetProcIDDLL = LoadLibrary(L"QPrint\\dll\\QPrintS.dll"); 
	lpfnGetProcessID = NULL;

	lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"verificarConexion"); 
	verificarConexion = pICFUNSen1(lpfnGetProcessID);

	lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"obtenerEncabezado"); 
	obtenerEncabezado = pICFUNSen2(lpfnGetProcessID);

	lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"leerMemoriaFiscal"); 
	leerMemoriaFiscal = pICFUNSen3(lpfnGetProcessID);

	lpfnGetProcessID = GetProcAddress(HMODULE (hGetProcIDDLL),"leerEJ"); 
	leerEJ = pICFUNSen4(lpfnGetProcessID);

	memset(identificadorMarca,0,10);
	memset(identificadorModelo,0,10);
	memset(puertoConexion,0,5);
	memset(nombreArchivoSalidaEnca,0,1024);
	memset(nombreArchivoSalidaMF,0,1024);
	memset(fechaDesde,0,12);
	memset(fechaHasta,0,12);
	memset(archivoErrores,0,100);
	memset(archivofuncion,0,100);
	memset(archivoAlicuotas,0,100);
	memset(tramaRIF,0,12);

	memset(archivodepruebaZ,0,100);
	memset(archivodepruebaS1,0,100);

	// Marca QPrint MF "W"
	strcpy(identificadorMarca, "W");
	// Modelo QPrint MF = "6", CR20 = "4"
	strcpy(identificadorModelo, "6");
	// Puerto COM
	strcpy(puertoConexion, strPort);

	// Archivo de Alícuotas de IVA
	strcpy(archivoAlicuotas, "QPrint\\alicuotas.ini");

	// Archivo de Escritura de Encabezado de Seniat.dll
	strcpy(nombreArchivoSalidaEnca, "QPrint\\QP_Encabezado.txt");
	// Archivo de Escritura de Memoria Fiscal de Seniat.dll
	strcpy(nombreArchivoSalidaMF, "QPrint\\QP_MemoriaFiscal.txt");
	// Archivo de auditoria de errores generados por la QPrint
	strcpy(archivoErrores, "QPrint\\QPrint Errores Generado.txt");
	// Archivo de llamado a las funciones Bixolon
	strcpy(archivofuncion, "QPrint\\Bix_LlamadoAFunciones.txt");
	//remove(archivofuncion);
/*	FILE *Funcion = fopen(archivofuncion,"a+");
	fprintf(Funcion, "------------------------------\n");
	fclose(Funcion);
*/

	// Archivo de Prueba de Reporte Z
	strcpy(archivodepruebaZ, "QPrint\\QP_ReporteZ.txt");
	// Archivo de Prueba de Reporte S1
	strcpy(archivodepruebaS1, "QPrint\\QP_ReporteS1.txt");
	
	// Eliminar Archivo de Escritura de Tramas enviadas a QPrint
	//remove("QPrint\\QP_SendCmd.txt");
/*	FILE *Funcion1 = fopen("QPrint\\QP_SendCmd.txt","a+");
	fprintf(Funcion1, "------------------------------\n");
	fclose(Funcion1);
*/
}

void LoadDictionary()
{
	errQprint.insert(mfits::value_type(0, "NO ERROR"));
	errQprint.insert(mfits::value_type(1, "ENTRADA INVALIDA"));
	errQprint.insert(mfits::value_type(2, "TIEMPO INVALIDO"));
	errQprint.insert(mfits::value_type(3, "FECHA INVALIDA"));
	errQprint.insert(mfits::value_type(4, "ARTICULO INVALIDO"));
	errQprint.insert(mfits::value_type(5, "REPORTE DESCONOCIDO"));
	errQprint.insert(mfits::value_type(6, "FUNCION INVALIDA"));
	errQprint.insert(mfits::value_type(7, "TRANSBUF. LLENO"));
	errQprint.insert(mfits::value_type(8, "CONTINUA EN TRANSACCION"));
	errQprint.insert(mfits::value_type(9, "USUARIO EN DESCANSO"));
	errQprint.insert(mfits::value_type(10, "NO DEBAJO/MODO DE PAGO"));
	errQprint.insert(mfits::value_type(11, "SIGUE EN MODO DE PAGO"));
	errQprint.insert(mfits::value_type(12, "ERROR DE ESCANEO"));
	errQprint.insert(mfits::value_type(13, "SELECCIONAR CAJERO"));
	errQprint.insert(mfits::value_type(14, "SELECCIONAR VENDEDOR"));
	errQprint.insert(mfits::value_type(15, "ITEM NO VENDIDO"));
	errQprint.insert(mfits::value_type(16, "NO SE HA INTRODUCIDO PRECIO"));
	errQprint.insert(mfits::value_type(17, "NO ZERO PRECIO"));
	errQprint.insert(mfits::value_type(18, "GAVETA CERRADA"));
	errQprint.insert(mfits::value_type(19, "MANAGER REQUERIDO"));
	errQprint.insert(mfits::value_type(20, "ENTRADA A LO ALTO"));
	errQprint.insert(mfits::value_type(21, "DESCUENTO NO PERMITIDO"));
	errQprint.insert(mfits::value_type(22, "CORRECCION NO PERMITIDA"));
	errQprint.insert(mfits::value_type(23, "DESCUENTO YA HECHO"));
	errQprint.insert(mfits::value_type(24, "INTRODUZCA CANTIDAD"));
	errQprint.insert(mfits::value_type(25, "JORNADA LLENA"));
	errQprint.insert(mfits::value_type(28, "CAJERO ERRONEO"));
	errQprint.insert(mfits::value_type(30, "IMPRIMA FACTURA"));
	errQprint.insert(mfits::value_type(31, "TERMINO EL PAPEL DEL RECIBO"));
	errQprint.insert(mfits::value_type(32, "TERMINO DE PAPEL DE JORNADA"));
	errQprint.insert(mfits::value_type(33, "SLIP SIN PAPEL"));
	errQprint.insert(mfits::value_type(34, "ERROR DE REGISTRO"));
	errQprint.insert(mfits::value_type(35, "KP ERROR"));
	errQprint.insert(mfits::value_type(37, "FACTURA DE BUFFER LLENO"));
	errQprint.insert(mfits::value_type(39, "ARCHIVO PLU LLENO"));
	errQprint.insert(mfits::value_type(40, "ARCHIVE RE-INDEXADO PLU"));
	errQprint.insert(mfits::value_type(41, "COMM ERRROR DE TIEMPO DE SALIDA"));
	errQprint.insert(mfits::value_type(42, "VUELVA A INTENTAR MC #"));
	errQprint.insert(mfits::value_type(43, "ERROR DE RED"));
	errQprint.insert(mfits::value_type(44, "BALANCE SIGUE ABIERTA"));
	errQprint.insert(mfits::value_type(45, "INGRESAR CANTIDAD"));
	errQprint.insert(mfits::value_type(46, "AUN EN ESPERA"));
	errQprint.insert(mfits::value_type(47, "ERROR DE ESCALA"));
	errQprint.insert(mfits::value_type(48, "NO AUTORIZADO"));
	errQprint.insert(mfits::value_type(49, "SELECCIONE CODIMEN"));
	errQprint.insert(mfits::value_type(50, "NO MENOS, ADMITIDAS"));
	errQprint.insert(mfits::value_type(51, "EFT ERROR COMM"));
	errQprint.insert(mfits::value_type(52, "NO EFT ACEPTADO"));
	errQprint.insert(mfits::value_type(53, "SUBTOTAL PRIMERO"));
	errQprint.insert(mfits::value_type(54, "ESCRIBA COVERS"));
	errQprint.insert(mfits::value_type(55, "INGRESE EL NUMERO"));
	errQprint.insert(mfits::value_type(56, "RETIRE SLIP"));
	errQprint.insert(mfits::value_type(57, "DISPENSADOR ERROR"));
	errQprint.insert(mfits::value_type(58, "INGRESAR ERROR"));
	errQprint.insert(mfits::value_type(59, "PRIMERA DECLARACION"));
	errQprint.insert(mfits::value_type(60, "SOBRE EL LIMITE DE SALDO"));
	errQprint.insert(mfits::value_type(61, "SELECCIONE PESO TARE"));
	errQprint.insert(mfits::value_type(62, "MEMORIA USB NO ENCONTRADA"));
	errQprint.insert(mfits::value_type(63, "ARCHIVOS NO ENCONTRADOS"));
	errQprint.insert(mfits::value_type(64, "INICIACION REQUERIDA"));
	errQprint.insert(mfits::value_type(65, "ERROR DE ESCRITURA EN EJ"));
	errQprint.insert(mfits::value_type(66, "ERROR DE LECTURA EN EJ"));
	errQprint.insert(mfits::value_type(67, "TIME OUT FIRST"));
	errQprint.insert(mfits::value_type(68, "ORDEN MUY GRANDE"));
	errQprint.insert(mfits::value_type(69, "EL ARTICULO NO ESTA EN STOCK"));
	errQprint.insert(mfits::value_type(70, "SELECCIONE EL MODO EN NIVEL DE TECLADO"));
	errQprint.insert(mfits::value_type(71, "SISTEMA OCUPADO INTENTELO DE NUEVO"));
	errQprint.insert(mfits::value_type(72, "ARCHIVO DE CUPON COMPLETO"));
	errQprint.insert(mfits::value_type(73, "REPORTE DE MEMORIA DE AUDITORIA COMPLETO"));
	errQprint.insert(mfits::value_type(74, "ERROR DE IMPRESORA FISCAL"));
	errQprint.insert(mfits::value_type(75, "INGRESE EL CODIGO ED ARRENDAMIENTO"));
	errQprint.insert(mfits::value_type(129, "LA MEMORIA FISCAL ESTÁ LLENA"));
	errQprint.insert(mfits::value_type(130, "UNA GRABACIÓN DE FM INCORRECTA ES DETECTADA. LEYENDO LA GRABACIÓN O REGISTRO")); 
	errQprint.insert(mfits::value_type(131, "NO SE DETECTA EL MODULO FISCAL"));
	errQprint.insert(mfits::value_type(132, "UN REPORTE DIARIO Z ES REQUERIDO PARA CONTINUAR"));
	errQprint.insert(mfits::value_type(133, "UNA GRABACIÓN DE FM INCORRECTA ES DETECTADA. ESCRIBIENDO LA GRABACIÓN O REGISTRO"));
	errQprint.insert(mfits::value_type(134, "NO HAY MÁS NÚMERO DE IVA LIBRE DISPONIBLE"));
	errQprint.insert(mfits::value_type(135, "EL MÓDULO FISCAL NO ESTÁ BORRADO O LIMPIO. COMIENZO DE LA INICIALIZACIÓN"));
	errQprint.insert(mfits::value_type(136, "DEPARTAMENTO O PLU ASIGNADO SIN IVA O MÁS DE 1 IVA"));
	errQprint.insert(mfits::value_type(137, "NO HAY MÁS ESPACIO LIBRE DISPONIBLE PARA EL CAMBIO DE TASA DE IVA"));
	errQprint.insert(mfits::value_type(138, "NO HAY MÁS ESPACIO LIBRE DISPONIBLE PARA LOS CAMBIOS DE BORRADO DE RAM"));
	errQprint.insert(mfits::value_type(139, "EL TIEMPO PROGRAMADO IMPUTADO ES MÁS CERCANO QUE EL TIEMPO ALMACENADO EN EL MÓDULO FISCAL"));
	errQprint.insert(mfits::value_type(140, "LA FECHA PROGRAMADA IMPUTADA ES MÁS CERCANA QUE LA FECHA ALMACENADA EN EL MÓDULO FISCAL"));
	errQprint.insert(mfits::value_type(141, "NO SE UTILIZA AÚN"));
	errQprint.insert(mfits::value_type(142, "SE TRATA DE HACER UNA VENTA Y LA OPCIÓN1 DEPARTAMENTO. VENTA CERO NO PERMITIDA NO ESTÁ SELECCIONADA"));
	errQprint.insert(mfits::value_type(143, "NO SE UTILIZA AUN"));
	errQprint.insert(mfits::value_type(144, "NO ES VÁLIDA LA OPERACIÓN DE VENTA ANTES DE REALIZAR EL REPORTE DIARIA Z"));
	errQprint.insert(mfits::value_type(145, "NO HAY MÁS ESPACIO LIBRE DISPONIBLE PARA EL CONTADOR DE BLOQUEO DE IMPRESIÓN"));
	errQprint.insert(mfits::value_type(146, "TRATA DE PROGRAMAR TASAS DE IVA CON EL MISMO VALOR DE PORCENTAJE"));
	errQprint.insert(mfits::value_type(147, "SE TRATA DE CAMBIAR EL MÓDULO FISCAL POR OTRO IGUAL")); 
	errQprint.insert(mfits::value_type(148, "CORRUPCIÓN DE LA MEMORIA RAM ES DETECTADA"));
	errQprint.insert(mfits::value_type(149, "TRATA DE HACER UNA VENTA CON LA SUM TOTAL = 0,00"));
	errQprint.insert(mfits::value_type(150, "TRATA DE HACER UN DUMP DE LOS TOTALES DE LA MEMORIA FISCAL CON UN RANGO INVALIDO DEL CONTADOR Z DE FECHA"));
	errQprint.insert(mfits::value_type(151, "PROCEDIMIENTO ESPECIAL DE COMIENZO DIARIO"));
	errQprint.insert(mfits::value_type(152, "NO REPORTE DIARIO Z PERMITIDO SI ALGUIEN ABRE UNA MESA"));
	errQprint.insert(mfits::value_type(153, "ERROR EN PANTALLA"));
	errQprint.insert(mfits::value_type(154, "ES ALCANZADO EL MÁXIMO NÚMERO DE CAMBIOS DE PROPIETARIO"));
	errQprint.insert(mfits::value_type(155, "TASA DE IVA EN CERO NO ESTÁ PERMITIDO PROGRAMARLA"));
	errQprint.insert(mfits::value_type(156, "CLAVE INCORRECTA PARA ENTRAR EN EL MODO DE PROGRAMACION"));
	errQprint.insert(mfits::value_type(157, "APARECE SI EN MÁS DE 24H NO SE HA REALIZADO UN REPORTE DIARIO Z"));
	errQprint.insert(mfits::value_type(158, "DESCONEXIÓN DE IMPRESORA"));
	errQprint.insert(mfits::value_type(159, "REPORTE DIARIO Z YA REALIZADO EN EL MISMO DIA"));
	errQprint.insert(mfits::value_type(160, "RANGO DE TAX PRE PROGRAMADO"));
	errQprint.insert(mfits::value_type(161, "NO HAY FECHA PARA LA CONVERSION DE EURO PRE PROGRAMADA"));
	errQprint.insert(mfits::value_type(162, "ESTABLECIDO TIPO DE ECR EN 4"));
	errQprint.insert(mfits::value_type(163, "NO SE GUARDA EN FM"));
	errQprint.insert(mfits::value_type(164, "NO SE GUARDA EN FM"));
	errQprint.insert(mfits::value_type(165, "EXTERNA EJ NO SE PUEDE ESCRIBIR"));
	errQprint.insert(mfits::value_type(166,	"EXTERNA EJ NO SE PUEDE LEER"));
	errQprint.insert(mfits::value_type(167, "NO JUMPER CUANDO SE RECUPERA"));
	errQprint.insert(mfits::value_type(168, "NO SE BORRA LA EJ CUANDO SE INICIALIZA"));
	errQprint.insert(mfits::value_type(169, "NO_PERMITIDO"));
	errQprint.insert(mfits::value_type(170, "CONFIG USADA EN SISTEMA FM"));
	errQprint.insert(mfits::value_type(171, "CON FM CONECTADA LA EJ HA SIDO CAMBIADA POR OTRA"));
	errQprint.insert(mfits::value_type(172, "EJ ESTÁ LLENA"));
	errQprint.insert(mfits::value_type(173, "EJ NO ESTÁ ONLINE"));
	errQprint.insert(mfits::value_type(174, "EJ CASI LLENA"));
	errQprint.insert(mfits::value_type(175, "NO PERMITIDO, MODO NO FISCAL")); 
	errQprint.insert(mfits::value_type(176, "BATERIA MUY BAJA"));
	errQprint.insert(mfits::value_type(236, "IMPRIMIR REPORTE Z PARA CONTINUAR"));
	errQprint.insert(mfits::value_type(243, "NO PERMITIDO RETRASO"));
	////
	errBixolon.insert(mfits::value_type(0, "NO ERROR"));
	errBixolon.insert(mfits::value_type(1, "FIN DE ENTREGA DE PAPEL"));
	errBixolon.insert(mfits::value_type(2, "ERROR DE INDOLE MECANICO EN LA ENTREGA DE PAPEL"));
	errBixolon.insert(mfits::value_type(3, "FIN EN LA ENTREGA DE PAPEL Y ERROR MECANICO"));
	errBixolon.insert(mfits::value_type(80, "COMANDO INVALIDO/VALOR INVALIDO"));
	errBixolon.insert(mfits::value_type(84, "TASA INVALIDA"));
	errBixolon.insert(mfits::value_type(88, "NO HAY ASIGNADAS DIRECTIVAS"));
	errBixolon.insert(mfits::value_type(92, "COMANDO INVALIDO"));
	errBixolon.insert(mfits::value_type(96, "ERROR FISCAL"));
	errBixolon.insert(mfits::value_type(100, "ERROR DE LA MEMORIA FISCAL"));
	errBixolon.insert(mfits::value_type(108, "MEMORIA FISCAL LLENA"));
	errBixolon.insert(mfits::value_type(112, "BUFFER COMPLETO"));
	errBixolon.insert(mfits::value_type(128, "ERROR EN LA COMUNICACION"));
	errBixolon.insert(mfits::value_type(137, "NO HAY RESPUESTA"));
	errBixolon.insert(mfits::value_type(144, "ERROR LRC"));
	errBixolon.insert(mfits::value_type(145, "ERROR INTERNO API"));
	errBixolon.insert(mfits::value_type(153, "ERROR EN LA APERTURA DE ARCHIVO"));
	////
	mapErrors.insert(mmid::value_type(0, 0));
	mapErrors.insert(mmid::value_type(1, 80));
	mapErrors.insert(mmid::value_type(2, 80));
	mapErrors.insert(mmid::value_type(3, 80));
	mapErrors.insert(mmid::value_type(4, 80));
	mapErrors.insert(mmid::value_type(5, 92));
	mapErrors.insert(mmid::value_type(6, 92));
	mapErrors.insert(mmid::value_type(7, 112));
	mapErrors.insert(mmid::value_type(8, 5));	
	mapErrors.insert(mmid::value_type(9,92));
	mapErrors.insert(mmid::value_type(10,92));
	mapErrors.insert(mmid::value_type(11,92));
	mapErrors.insert(mmid::value_type(12,92));
	mapErrors.insert(mmid::value_type(13, 88));
	mapErrors.insert(mmid::value_type(14, 88));
	mapErrors.insert(mmid::value_type(15,92));
	mapErrors.insert(mmid::value_type(16,92));
	mapErrors.insert(mmid::value_type(17,92));
	mapErrors.insert(mmid::value_type(18,92));
	mapErrors.insert(mmid::value_type(19,92));
	mapErrors.insert(mmid::value_type(20,92));
	mapErrors.insert(mmid::value_type(21, 80));
	mapErrors.insert(mmid::value_type(22, 80));
	mapErrors.insert(mmid::value_type(23,92));
	mapErrors.insert(mmid::value_type(24,92));
	mapErrors.insert(mmid::value_type(25,92));
	mapErrors.insert(mmid::value_type(28,92));
	mapErrors.insert(mmid::value_type(30,92));
	mapErrors.insert(mmid::value_type(31, 2));
	mapErrors.insert(mmid::value_type(32, 2));
	mapErrors.insert(mmid::value_type(33,92));
	mapErrors.insert(mmid::value_type(34,92));
	mapErrors.insert(mmid::value_type(35,92));
	mapErrors.insert(mmid::value_type(37, 112));
	mapErrors.insert(mmid::value_type(39,92));
	mapErrors.insert(mmid::value_type(40,92));
	mapErrors.insert(mmid::value_type(41, 128));
	mapErrors.insert(mmid::value_type(42,92));
	mapErrors.insert(mmid::value_type(43, 128));
	mapErrors.insert(mmid::value_type(44,92));
	mapErrors.insert(mmid::value_type(45,92));
	mapErrors.insert(mmid::value_type(46,92));
	mapErrors.insert(mmid::value_type(47,92));
	mapErrors.insert(mmid::value_type(48, 92));
	mapErrors.insert(mmid::value_type(49,92));
	mapErrors.insert(mmid::value_type(50,92));
	mapErrors.insert(mmid::value_type(51,92));
	mapErrors.insert(mmid::value_type(52,92));
	mapErrors.insert(mmid::value_type(53,92));
	mapErrors.insert(mmid::value_type(54, 88));
	mapErrors.insert(mmid::value_type(55,92));
	mapErrors.insert(mmid::value_type(56,92));
	mapErrors.insert(mmid::value_type(57,92));
	mapErrors.insert(mmid::value_type(58,92));
	mapErrors.insert(mmid::value_type(59,92));
	mapErrors.insert(mmid::value_type(60, 96));
	mapErrors.insert(mmid::value_type(61,92));
	mapErrors.insert(mmid::value_type(62,92));
	mapErrors.insert(mmid::value_type(63,92));
	mapErrors.insert(mmid::value_type(64,92));
	mapErrors.insert(mmid::value_type(65, 89));
	mapErrors.insert(mmid::value_type(66, 89));
	mapErrors.insert(mmid::value_type(67,92));
	mapErrors.insert(mmid::value_type(68,92));
	mapErrors.insert(mmid::value_type(69,92));
	mapErrors.insert(mmid::value_type(70,92));
	mapErrors.insert(mmid::value_type(71, 137));
	mapErrors.insert(mmid::value_type(72,92));
	mapErrors.insert(mmid::value_type(73,92));
	mapErrors.insert(mmid::value_type(74, 96));
	mapErrors.insert(mmid::value_type(75,92));
	mapErrors.insert(mmid::value_type(129, 108));
	mapErrors.insert(mmid::value_type(130, 100)); 
	mapErrors.insert(mmid::value_type(131, 96));
	mapErrors.insert(mmid::value_type(132,92));
	mapErrors.insert(mmid::value_type(133, 100));
	mapErrors.insert(mmid::value_type(134,92));
	mapErrors.insert(mmid::value_type(135,92));
	mapErrors.insert(mmid::value_type(136,92));
	mapErrors.insert(mmid::value_type(137,92));
	mapErrors.insert(mmid::value_type(138,92));
	mapErrors.insert(mmid::value_type(139,92));
	mapErrors.insert(mmid::value_type(140,92));
	mapErrors.insert(mmid::value_type(141,92));
	mapErrors.insert(mmid::value_type(142,92));
	mapErrors.insert(mmid::value_type(143,92));
	mapErrors.insert(mmid::value_type(144,92));
	mapErrors.insert(mmid::value_type(145,92));
	mapErrors.insert(mmid::value_type(146,92));
	mapErrors.insert(mmid::value_type(147,92));
	mapErrors.insert(mmid::value_type(148,92));
	mapErrors.insert(mmid::value_type(149,92));
	mapErrors.insert(mmid::value_type(150,92));
	mapErrors.insert(mmid::value_type(151,92));
	mapErrors.insert(mmid::value_type(152,92));
	mapErrors.insert(mmid::value_type(153,92));
	mapErrors.insert(mmid::value_type(154,92));
	mapErrors.insert(mmid::value_type(155,92));
	mapErrors.insert(mmid::value_type(156,92));
	mapErrors.insert(mmid::value_type(157,92));
	mapErrors.insert(mmid::value_type(158,92));
	mapErrors.insert(mmid::value_type(159,92));
	mapErrors.insert(mmid::value_type(160,92));
	mapErrors.insert(mmid::value_type(161,92));
	mapErrors.insert(mmid::value_type(162,92));
	mapErrors.insert(mmid::value_type(163, 0));		//Error de QPrint sera 0 en Bix por ahora
	mapErrors.insert(mmid::value_type(164, 100));
	mapErrors.insert(mmid::value_type(165, 92));
	mapErrors.insert(mmid::value_type(166,92));
	mapErrors.insert(mmid::value_type(167,92));
	mapErrors.insert(mmid::value_type(168,92));
	mapErrors.insert(mmid::value_type(169,92));
	mapErrors.insert(mmid::value_type(170,92));
	mapErrors.insert(mmid::value_type(171,92));
	mapErrors.insert(mmid::value_type(172,92));
	mapErrors.insert(mmid::value_type(173,92));
	mapErrors.insert(mmid::value_type(174,92));
	mapErrors.insert(mmid::value_type(175, 2));
	mapErrors.insert(mmid::value_type(176,92));
	mapErrors.insert(mmid::value_type(236,92));
	mapErrors.insert(mmid::value_type(243, 80));
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH: // Code to run when the DLL is loaded			
			LoadDictionary();
			LoadSeniat();
			break;

        case DLL_PROCESS_DETACH: // Code to run when the DLL is freed
            break;

        case DLL_THREAD_ATTACH: // Code to run when a thread is created during the DLL's lifetime
            break;

        case DLL_THREAD_DETACH: // Code to run when a thread ends normally.
            break;
    }
    return TRUE;
}

__declspec(dllexport) int __stdcall GetVer(char* ver)
{	
	return print.fncGetVer(ver);
}

__declspec(dllexport) int __stdcall HelloWorld(char* name, char* resp)
{
	return print.fncHelloWorld(name,resp);	
}

__declspec(dllexport) int __stdcall SetComSettings(WORD comPort, WORD baudRate, WORD wordSize, WORD reg)
{
	return print.fncSetComSettings(comPort, baudRate, wordSize, reg);
}

__declspec(dllexport) int __stdcall SetIPSettings(BYTE ip0, BYTE ip1, BYTE ip2, BYTE ip3, WORD reg = 0)
{
	return print.fncSetIPSettings(ip0, ip1, ip2, ip3, reg);
}

__declspec(dllexport) int __stdcall GetComSettings(int index)
{
	return print.fncGetComSettings(index);
}

__declspec(dllexport) int __stdcall GetIPSettings(int index)
{
	return print.fncGetIPSettings(index);
}

void ShowRecord(int type, char *rec, int len)
{
	print.fncShowRecord(type, rec, len);
}

#if Q_NET == 1

int SetIPaddress(void)
{
	return print.fncSetIPaddress();
}

int OpenWinsock(void)
{
	return print.fncOpenWinsock();
}

void CloseWinsock(void)
{
	print.fncCloseWinsock();
}

#endif

//---------------------------------------------------------------------------
void ResetCommError(void)
{
	print.fncResetCommError();
}
//---------------------------------------------------------------------------

__declspec(dllexport) int __stdcall OpenPort(void)
{
	return print.fncOpenPort();
}

__declspec(dllexport) int __stdcall ClosePort(void) 
{
	return print.fncClosePort();
}

__declspec(dllexport) int __stdcall OpenComPort(WORD comPort, WORD baudRate)
{
	return print.fncOpenComPort(comPort, baudRate);
}

__declspec(dllexport) int __stdcall CloseComPort(void)
{
	return print.fncCloseComPort();
}

__declspec(dllexport) int __stdcall OpenIPPort(BYTE ip0, BYTE ip1, BYTE ip2, BYTE ip3, WORD reg = 0)
{
	return print.fncOpenIPPort(ip0, ip1, ip2, ip3, reg);
}

__declspec(dllexport) int __stdcall CloseIPPort(void)
{
	return print.fncCloseIPPort();
}

//---------------------------------------------------------------------------

/* tabel used for CRC-16 calcutlation according to 8005 Poly (x16+x15+x2+1) */
/*
WORD CRC_Table[] =
{
	0x0000, 0xCC01,	0xD801,	0x1400,	0xF001,	0x3C00,	0x2800,	0xE401,
	0xA001,	0x6C00,	0x7800,	0xB401,	0x5000,	0x9C01,	0x8801,	0x4400,
};
*/
WORD UpdateCrc(WORD crc, BYTE b)
{
	return print.fncUpdateCrc(crc, b);
}

WORD CalculateCrc(WORD crc, BYTE *p, WORD len)
{
	return print.fncCalculateCrc(crc, p, len);
}

//---------------------------------------------------------------------------

int Send232(BYTE ch)
{
	return print.fncSend232(ch);
}

int RxdData(void)
{
	return print.fncRxdData();
}

int TxdData(BYTE *p, WORD length)
{
	return print.fncTxdData(p, length);
}

//---------------------------------------------------------------------------
int SendRecord(BYTE *rec, int recsize, DWORD timeout)
/*
    rec points to rec which must be transmitted
    recsize is the size of he record to be transmitted
    return 1 when transmitted OK
*/
{
	return print.fncSendRecord(rec, recsize, timeout);
}

//---------------------------------------------------------------------------
int UploadData(BYTE *rec, WORD len)
{
	return print.fncUploadData(rec, len);
}

//---------------------------------------------------------------------------
__declspec(dllexport) int __stdcall SendCommand(BYTE *rec, BYTE *trama)
{
	return print.fncSendCommand(rec, trama);
}

__declspec(dllexport) int __stdcall ReadData(BYTE *rx)
{
	return print.fncReadData(rx);
}

_declspec(dllexport) int _stdcall WeftLength()
{
	return print.fncWeftLength();
}

//---------------------------------------------------------------------------
int DownloadData(BYTE *rec, WORD len)
{
	return print.fncDownloadData(rec, len);
}

/****************** Funciones de Bixolon *********************/

_declspec(dllexport) bool _stdcall OpenFpctrl(char* lpPortName)
{
	char * linea = (char *)malloc(100 * sizeof(char));
	memset(linea,0,100);
	char * cmd = (char *)malloc(10 * sizeof(char));
	memset(cmd,0,10);
	char * _buffer = (char *)malloc(1024 * sizeof(char));
	memset(_buffer,0,1024);
	char * pch;
	char * Campo17= (char *)malloc(20 * sizeof(char));
	memset(Campo17,0,20);
	int cont = 0;
	bool oe = 0;

	if(!strlen(lpPortName)) 
		return false;
	
	memset(strPort,0,5);
	strcpy(strPort, lpPortName);

	if(!strcmp(lpPortName,"COM1")) comPort = 1;
	if(!strcmp(lpPortName,"COM2")) comPort = 2;
	if(!strcmp(lpPortName,"COM3")) comPort = 3;
	if(!strcmp(lpPortName,"COM4")) comPort = 4;
	if(!strcmp(lpPortName,"COM5")) comPort = 5;
	if(!strcmp(lpPortName,"COM6")) comPort = 6;
	if(!strcmp(lpPortName,"COM7")) comPort = 7;
	if(!strcmp(lpPortName,"COM8")) comPort = 8;

	if(comPort == 0)
		return false;

	strcpy(puertoConexion, strPort);

	print.fncOpenComPort(comPort, 6);

	strcpy(cmd, "F0;1");
	print.fncSendCommand(reinterpret_cast<BYTE*>(cmd), reinterpret_cast<BYTE*>(_buffer));

	print.fncCloseComPort();

// Determinando si esta fiscalizada
	cont = 0;
	pch = strtok (_buffer,"|");
	while (pch != NULL)
	{
		if(cont == 17) { strcpy(Campo17, pch); break; }
		++cont;
		pch = strtok (NULL, "|");
	}

	if (strcmp(Campo17, "") == 0) strcpy(tramaRIF, "J-         ");		//Sin Nro de Serial
	else if (strcmp(tramaRIF, "") == 0) 
	{
		bool vc = verificarConexion(identificadorMarca, identificadorModelo, puertoConexion);
		if (vc)
		{
			oe = obtenerEncabezado(identificadorMarca, identificadorModelo, nombreArchivoSalidaEnca);
		}

		if (oe)
		{
			cont = 0;
			std::ifstream in1(nombreArchivoSalidaEnca);
			while (in1.good())
			{
				++cont;
				in1.getline(linea, 1024);
				if (cont == 2) break;
			}
			strncat(tramaRIF, &linea[0], 1); strcat(tramaRIF, "-"); strncat(tramaRIF, &linea[1], 9);
		} else return false;
	}

/*	FILE *Funcion = fopen(archivofuncion,"a+");
	fprintf(Funcion, "Función OpenFpctrl lpPortName: %s\n", lpPortName);
	fclose(Funcion);
*/
/*
	free(linea);
	free(cmd);
//	free(_buffer);
	free(Campo17);
*/
	return print.fncOpenComPort(comPort, 6) == 1 ? true : false;
}

_declspec(dllexport) bool _stdcall CloseFpctrl()
{
/*	
	FILE *Funcion = fopen(archivofuncion,"a+");
	fprintf(Funcion, "Función CloseFpctrl\n");
	fclose(Funcion);
*/

	return print.fncCloseComPort() == 1 ? true : false;
}


_declspec(dllexport) bool _stdcall CheckFprinter()
{
	strcpy(puertoConexion, strPort);

	CloseFpctrl();

	bool bxOpen = OpenFpctrl(puertoConexion);

/*	FILE *Funcion = fopen(archivofuncion,"a+");
	fprintf(Funcion, "\nFunción CheckFprinter = %i\n", bxOpen);
	fclose(Funcion);
*/
	return bxOpen;
}

_declspec(dllexport) bool _stdcall ReadFpStatus(LPINT status, LPINT error)
{
	char * cmd = (char *)malloc(10 * sizeof(char));
	memset(cmd,0,10);
	char * _buffer = (char *)malloc(1024 * sizeof(char));
	memset(_buffer,0,1024);
	char * Campo2 = (char *)malloc(10 * sizeof(char));
	memset(Campo2, 0, 10);
	char * Campo17= (char *)malloc(20 * sizeof(char));
	memset(Campo17, 0, 20);
	char * pch;
	int _errorqp = 0;
	int _errorbx = 0;
	int _status = 0;
	int cont = 0;
	int status1 = 0;
	int status2 = 0;
	int status3 = 0;
	bool retval = false;
	*status = 0;
	*error = 0;

	strcpy(cmd, "F0;1");
	_errorqp = print.fncSendCommand(reinterpret_cast<BYTE*>(cmd), reinterpret_cast<BYTE*>(_buffer));

	if (strcmp(_buffer, "") != 0)
	{
	// Determinando Error
		_errorbx = (mapErrors.find(_errorqp)->second);
		if (_errorbx < 0) _errorbx = 92;

		*error = _errorbx;

	// Determinando Status
		pch = strtok (_buffer,"|");
		while (pch != NULL)
		{
			if(cont == 2) strcpy(Campo2, pch);
			if(cont == 17) { strcpy(Campo17, pch); break; }
			++cont;
			pch = strtok (NULL, "|");
		}

		if (strcmp(Campo17, "") == 0) status1 = 1;		//Sin Nro de Serial
		else status1 = 2;								//Con Nro de Serial

		if (strcmp(Campo2, "R") == 0) status2 = 1;		//En Espera
		else if (strcmp(Campo2, "O") == 0) status2 = 2;	//Documento Fiscal
		else if (strcmp(Campo2, "N") == 0) status2 = 3;	//Documento No Fiscal
		else status2 = 0;

		if (_errorqp == 129) status3 = 1;				//EJ está llena
		if (_errorqp == 174) status3 = 2;				//EJ casi llena
		else status3 = 0;

		if (status1 == 1 && status2 == 1 && status3 == 0) _status = 1;			//Modo Prueba, Espera
		else if (status1 == 1 && status2 == 2 && status3 == 0) _status = 2;		//Modo Prueba, Doc. Fiscales
		else if (status1 == 1 && status2 == 3 && status3 == 0) _status = 3;		//Modo Prueba, DNF
		else if (status1 == 2 && status2 == 1 && status3 == 0) _status = 4;		//Modo Fiscal, Espera
		else if (status1 == 2 && status2 == 2 && status3 == 0) _status = 5;		//Modo Fiscal, Doc. Fiscales
		else if (status1 == 2 && status2 == 3 && status3 == 0) _status = 6;		//Modo Fiscal, DNF
		else if (status1 == 2 && status2 == 1 && status3 == 2) _status = 7;		//Modo Fiscal, Cercana Carga MF, Espera
		else if (status1 == 2 && status2 == 2 && status3 == 2) _status = 8;		//Modo Fiscal, Cercana Carga MF, Doc. Fiscales
		else if (status1 == 2 && status2 == 3 && status3 == 2) _status = 9;		//Modo Fiscal, Cercana Carga MF, DNF
		else if (status1 == 2 && status2 == 1 && status3 == 1) _status = 10;	//Modo Fiscal, Carga Completa MF, Espera
		else if (status1 == 2 && status2 == 2 && status3 == 1) _status = 11;	//Modo Fiscal, Carga Completa MF, Doc. Fiscales
		else if (status1 == 2 && status2 == 3 && status3 == 1) _status = 12;	//Modo Fiscal, Carga Completa MF, DNF
		else _status = 0;

		*status = _status;
		retval = true;
	} else retval = false;

/*	FILE *Funcion = fopen(archivofuncion,"a+");
	fprintf(Funcion, "Función ReadFpStatus Status: %i Error: %i ErrorQPrint: %i\n", *status, *error, _errorqp);
	fclose(Funcion);
*/
/*
	free(cmd);
//	free(_buffer);
	free(Campo2);
	free(Campo17);
*/
	return retval;
}

__declspec(dllexport) int __stdcall Translate(BYTE *cmdbx, BYTE *cmdqp, int* status, int* error)
{
	//Printer print;
	//Protocol Lexer(&print);
	const char text[] = "HolaMundo";
	
	//char_array_buffer ibuff(text); // -1 for \0
	char_array_buffer ibuff(reinterpret_cast<char*>(cmdbx)); // -1 for \0
	::istream in(reinterpret_cast<streambuf*>(&ibuff));
	/*
	output_buffer obuff(std::cout);		
	std::ostream out(&obuff);
	*/
	Lexer.yyrestart(&in);
	//Lexer.switch_streams(&in,&out);
	int rval = Lexer.yylex();
	/*
	cout << Lexer.YYText() << " " << Lexer.YYLeng() << endl;

	out << 	"this is a test. ";
	out << 	"we should see all sentences beginning with an initial capital letter. ";
	out << 	"the end.\n";
	out <<	std::flush;
	*/
	*status = Lexer.BStatus();
	*error = Lexer.QError();
	strcpy(reinterpret_cast<char*>(cmdqp), Lexer.QPrint());
	return Lexer.QPLeng();
}


_declspec(dllexport) bool _stdcall SendCmd(int* status, int* error, char* cmd)
{
/*	FILE *Funcion = fopen(archivofuncion,"a+");
	fprintf(Funcion, "Función SendCmd Comando: %s\n", cmd);
	fclose(Funcion);
*/

/*
	// Eliminando Archivo de auditoria de errores generados por la QPrint
	if (var == 0)
	{
		remove(archivoErrores);
		++var;
	}
*/

	*status = 0;
	*error = 0;
	int qp_error = 0;
	int bx_error = 0;
	bool retval = true;
	BYTE qprint_cmd[1024];
	BYTE trama[1024];
	memset(trama, 0, 1024);
	
	try
	{
		// envìo de comando
		//qprint_cmd = reinterpret_cast<BYTE*>(translator[cmd]);
		int len = Translate(reinterpret_cast<BYTE*>(cmd), qprint_cmd, status, &qp_error);
		//*error = SendCommand(qprint_cmd, trama);
		//if(*error != 0) retval = false;
		//printf("Len %i cmd %s qprint_cmd %s status %i, qp_error %i\n", len, qprint_cmd, status, &qp_error);
		
		// manejo de errores
		//printf("qp_error %i\n", qp_error);
		mmid::const_iterator iter;
		bx_error = (mapErrors.find(qp_error)->second);
		//printf("bx_error %i\n",bx_error);

		if (bx_error < 0)
		{
			bx_error = 92;
		}

		*error = bx_error;
	}
	catch(...)
	{
		*error = -1;
		//eturn false;
		retval = 0;
	}

/*	FILE *Funcion = fopen(archivofuncion,"a+");
	fprintf(Funcion, "Función SendCmd Status: %i Error: %i Comando: %s\n", *status, *error, cmd);
	fclose(Funcion);
*/

	return retval;
}

_declspec(dllexport) int _stdcall SendNCmd(LPINT status, LPINT error , LPCSTR buffer)
{
	char *_buffer = (char *)malloc(1024 * sizeof(char));
	memset(_buffer,0,1024);
	char *linea = (char *)malloc(200 * sizeof(char));
	memset(linea,0,200);
	char *letra = (char *)malloc(5 * sizeof(char));
	memset(letra,0,5);
	int len = 0;
	int i = 0;

	_buffer = (char*) buffer;
	len = strlen(_buffer);

	for(i=0; i<=len; i++)
	{
		memset(letra,0,5);
		strncat(letra, &_buffer[i], 1);
		if (strcmp(letra, "\n") == 0) 
		{
			SendCmd(status, error, linea);
			memset(linea,0,200);
		}
		if (i == len) 
		{
			SendCmd(status, error, linea);
			memset(linea,0,200);
		}
		if (strcmp(letra, "\n") != 0) 
		{
			strcat(linea, letra);
		}
	}

/*	FILE *Funcion = fopen(archivofuncion,"a+");
	fprintf(Funcion, "\nFunción SendNCmd Buffer: %s Status: %i Error: %i\n", buffer, *status, *error);
	fclose(Funcion);
*/
/*
	free(_buffer);
	free(linea);
	free(letra);
*/
	return 1;

}

_declspec(dllexport) int _stdcall SendFileCmd(LPINT status, LPINT error, LPCSTR file)
{
	char *linea = (char *)malloc(200 * sizeof(char));
	memset(linea,0,200);
	int cont = 0;

	std::ifstream in(file);
	while (in.good())
	{
		++cont;
		in.getline(linea, 200);
		if (strcmp(linea, "") != 0)
		{
			SendCmd(status, error, linea);
			memset(linea,0,200);
		}
	}

/*	FILE *Funcion = fopen(archivofuncion,"a+");
	fprintf(Funcion, "\nFunción SendFileCmd  File: %s Status: %i Error: %i\n",file, *status, *error);
	fclose(Funcion);
*/
/*
	free(linea);
*/
	return 1;
}

_declspec(dllexport) bool _stdcall UploadReportCmd(LPINT status, LPINT error, LPCSTR cmd, LPCSTR file)
{
	char * cmdQP = (char *)malloc(1024 * sizeof(char));
	memset(cmdQP,0,1024);
	char * bufferQP = (char *)malloc(1024 * sizeof(char));
	memset(bufferQP,0,1024);
	char * fechaQP = (char *)malloc(12 * sizeof(char));
	memset(fechaQP,0,12);
	char * tramaqp = (char *)malloc(1024 * sizeof(char));
	memset(tramaqp,0,1024);
	char * tramabix = (char *)malloc(1024 * sizeof(char));
	memset(tramabix,0,1024);
	char * letra = (char *)malloc(1024 * sizeof(char));
	memset(letra,0,1024);
	char * numero = (char *)malloc(1024 * sizeof(char));
	memset(numero,0,1024);
	char * numerofinal = (char *)malloc(1024 * sizeof(char));
	memset(numerofinal,0,1024);
	char * cmd1 = (char *)malloc(1024 * sizeof(char));
	memset(cmd1,0,1024);
	char * diaQP = (char *)malloc(4 * sizeof(char));
	memset(diaQP,0,4);
	char * mesQP = (char *)malloc(4 * sizeof(char));
	memset(mesQP,0,4);
	char * anoQP = (char *)malloc(6 * sizeof(char));
	memset(anoQP,0,6);
	char * Campo20 = (char *)malloc(10 * sizeof(char));
	memset(Campo20,0,10);
	char * Campo21 = (char *)malloc(10 * sizeof(char));
	memset(Campo21,0,10);
	char * Campo22 = (char *)malloc(10 * sizeof(char));
	memset(Campo22,0,10);
	char * linea = (char *)malloc(1024 * sizeof(char));
	memset(linea,0,1024);
	char * pch;
	int cont = 0;
	int cont1 = 0;
	int lenpch = 0;
	int lenumero = 0;
	int i = 0;
	bool retval;
	
	memset(fechaDesde,0,12);
	memset(fechaHasta,0,12);
	retval = false;
	strcpy(puertoConexion, strPort);
	strncat(cmd1, &cmd[0],3);
	remove(file);

/*	FILE *Funcion3 = fopen(archivofuncion,"a+");
	fprintf(Funcion3, "\nFunción UploadReportCmd Comando: %s File: %s\n", cmd, file);
	fclose(Funcion3);
*/

// REPORTE Z //
	if (strcmp(cmd1, "U0Z") == 0)
	{		
	// Determinar Fecha Actual

		strcpy(cmdQP, "F0;1");
		print.fncSendCommand(reinterpret_cast<BYTE*>(cmdQP), reinterpret_cast<BYTE*>(bufferQP));

		if (strcmp(bufferQP, "") != 0)
		{
			pch = strtok (bufferQP,"|");
			while (pch != NULL)
				{
					if (cont == 18) {strcpy(fechaQP, pch); break;}
					++cont;
					pch = strtok (NULL, "|");
				}
		}

		strcpy(fechaHasta, fechaQP);
		// Se determina la fecha desde del día anterior para sacar el Reporte Z
		strncat(diaQP, &fechaQP[0], 2);
		strncat(mesQP, &fechaQP[3], 2);
		strncat(anoQP, &fechaQP[6], 4);
		int dia = atoi(diaQP);
		int mes = atoi(mesQP);
		for(i=0; i<10 ; i++)
		{
			dia = dia - 1;
			if (dia < 1) 
			{
				dia = 30;
				mes = mes - 1;
				if (mes < 1) mes = 12;
			}
		}
		itoa(dia,diaQP,10);
		int lendia = strlen(diaQP);
		itoa(mes,mesQP,10);
		int lenmes = strlen(mesQP);
		memset(fechaQP,0,12);
		if (lendia == 1) strcat(fechaQP, "0");
		strcat(fechaQP, diaQP); strcat(fechaQP, "/");
		if (lenmes == 1) strcat(fechaQP, "0");
		strcat(fechaQP, mesQP); strcat(fechaQP, "/");
		strcat(fechaQP, anoQP);

		strcpy(fechaDesde, fechaQP);

	// Generar Reporte Memoria Fiscal QP con DLL Seniat
		CloseFpctrl();
		bool vc = verificarConexion(identificadorMarca, identificadorModelo, puertoConexion);
		//cout << "verificarConexion: "  << vc << endl;
		bool mf = leerMemoriaFiscal(identificadorMarca, identificadorModelo, fechaDesde, fechaHasta, nombreArchivoSalidaMF);
		//cout << "leerMemoriaFiscal: "  << mf << endl;
		bool bxOpen = OpenFpctrl(puertoConexion);
		//cout << "OpenFpctrl: "  << bxOpen << endl;

		cont = 0;
		std::ifstream in(nombreArchivoSalidaMF);
		while (in.good())	//Contando lineas del archivo obtenido por DLL Seniat
		{
			++cont;
			in.getline(linea, 1024);
		}

		if (cont < 3)		//Indica que el archivo "QP_MemoriaFiscal" esta sin información
		{
			*status = 0;
			*error = 137;
			return false;
		}

		std::ifstream in1(nombreArchivoSalidaMF);
		while (in1.good())
		{
			++cont1;
			in1.getline(linea, 1024);
			if (cont1 == (cont - 1)) 
			{
				strcat(tramaqp, linea);
				break;
				//printf("tramaqp %s\n", tramaqp);
			}
		}
		cont = 0;
		pch = strtok (tramaqp,"\t");
		while (cont < 18)
			{
			//Nro de Reporte Z
				if (cont == 0) strcat(tramabix, pch);
			//Fecha de Reporte Z
				if (cont == 1) 
				{
					strncat(tramabix, &pch[8],2); 
					strncat(tramabix, &pch[3],2); 
					strncat(tramabix, &pch[0],2);
				} 
			//Número de la última Factura
				else if (cont == 2) strcat(tramabix, pch);	
			//Fecha de la última factura
				else if (cont == 3) {strncat(tramabix, &pch[8],2); strncat(tramabix, &pch[3],2); strncat(tramabix, &pch[0],2);} 
			//Hora de la última factura
				else if (cont == 4) {strncat(tramabix, &pch[0],2); strncat(tramabix, &pch[3],2);}
			//Totales
				else if (cont > 4)
				{
					lenpch = strlen(pch);
					for(i=0; i<lenpch ; i++)				//Ventas Tasa General
					{
						strncpy(letra, &pch[i],1);
						if (strcmp(letra, ",") != 0)  
						{
							strcat(numero, letra);
						}	
					}
					lenumero = strlen(numero);
					if (lenumero == 3) {strcat(numerofinal, "0000000"); strcat(numerofinal, numero); memset(numero,0,1024);}
					if (lenumero == 4) {strcat(numerofinal, "000000"); strcat(numerofinal, numero); memset(numero,0,1024);}
					if (lenumero == 5) {strcat(numerofinal, "00000"); strcat(numerofinal, numero); memset(numero,0,1024);}
					if (lenumero == 6) {strcat(numerofinal, "0000"); strcat(numerofinal, numero); memset(numero,0,1024);}
					if (lenumero == 7) {strcat(numerofinal, "000"); strcat(numerofinal, numero); memset(numero,0,1024);}
					if (lenumero == 8) {strcat(numerofinal, "00"); strcat(numerofinal, numero); memset(numero,0,1024);}
					if (lenumero == 9) {strcat(numerofinal, "0"); strcat(numerofinal, numero); memset(numero,0,1024);}
					strcat(tramabix, numerofinal);
					memset(numerofinal,0,1024);
				}
				++cont;
				pch = strtok (NULL, "\t");
			}
		FILE *destino = fopen(file,"w");
		fprintf(destino, "%s\n", tramabix);
		fclose(destino);
		retval = true;
	}
// REPORTE X //
	else if (strcmp(cmd1, "U0X") == 0)
	{
		strcpy(cmdQP, "F0;3");
		print.fncSendCommand(reinterpret_cast<BYTE*>(cmdQP), reinterpret_cast<BYTE*>(bufferQP));

		pch = strtok (bufferQP,"|");
		while (pch != NULL)
			{
				if (cont == 20) strcpy(Campo20, pch);			//Última NC
				if (cont == 21) strcpy(Campo21, pch);			//Última Factura
				if (cont == 22) {strcpy(Campo22, pch); break;}	//Último Reporte Z
				++cont;
				pch = strtok (NULL, "|");
			}
		strcpy(tramabix, Campo22);
		strcat(tramabix, "000000");
		strcat(tramabix, Campo21);
		strcat(tramabix, "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
		strcat(tramabix, Campo20);
		retval = true;
		FILE *destino = fopen(file,"a");
		fprintf(destino, "%s\n", tramabix);
		fclose(destino);
	}
// REPORTE DE MEMORIA FISCAL POR FECHA //
	else if (strcmp(cmd1, "U2A") == 0) 
	{		
	// Determinar Fechas

		strncat(fechaDesde, &cmd[3],2);
		strcat(fechaDesde, "/");
		strncat(fechaDesde, &cmd[5],2);
		strcat(fechaDesde, "/20");
		strncat(fechaDesde, &cmd[7],2);

		strncat(fechaHasta, &cmd[9],2);
		strcat(fechaHasta, "/");
		strncat(fechaHasta, &cmd[11],2);
		strcat(fechaHasta, "/20");
		strncat(fechaHasta, &cmd[13],2);

	// Generar Reporte Fiscal QP con DLL Seniat
		CloseFpctrl();
	
		bool vc = verificarConexion(identificadorMarca, identificadorModelo, puertoConexion);
		cout << "verificarConexion: "  << vc << endl;
		bool mf = leerMemoriaFiscal(identificadorMarca, identificadorModelo, fechaDesde, fechaHasta, nombreArchivoSalidaMF);
		cout << "leerMemoriaFiscal: "  << mf << endl;
		bool bxOpen = OpenFpctrl(puertoConexion);
		cout << "OpenFpctrl: "  << bxOpen << endl;

		cont = 0;
		std::ifstream in(nombreArchivoSalidaMF);
		while (in.good())	//Contando lineas del archivo obtenido por DLL Seniat
		{
			++cont;
			in.getline(linea, 1024);
		}

		int cont2 = cont;

		std::ifstream in1(nombreArchivoSalidaMF);
		while (in1.good())
		{
			++cont1;
			in1.getline(linea, 1024);
			if ((cont1 > 1) && (cont1 < cont2))
			{
				strcat(tramaqp, linea);
				//printf("tramaqp %s\n", tramaqp);

				cont = 0;
				pch = strtok (tramaqp,"\t");
				while (cont < 18)
					{
					//Nro de Reporte Z
						if (cont == 0) strcat(tramabix, pch);
					//Fecha de Reporte Z
						if (cont == 1) {strncat(tramabix, &pch[8],2); strncat(tramabix, &pch[3],2); strncat(tramabix, &pch[0],2);} 
					//Número de la última Factura
						else if (cont == 2) strcat(tramabix, pch);	
					//Fecha de la última factura
						else if (cont == 3) {strncat(tramabix, &pch[8],2); strncat(tramabix, &pch[3],2); strncat(tramabix, &pch[0],2);} 
					//Hora de la última factura
						else if (cont == 4) {strncat(tramabix, &pch[0],2); strncat(tramabix, &pch[3],2);}
					//Totales
						else if (cont > 4)
						{
							lenpch = strlen(pch);
							for(i=0; i<lenpch ; i++)				//Ventas Tasa General
							{
								strncpy(letra, &pch[i],1);
								if (strcmp(letra, ",") != 0)  
								{
									strcat(numero, letra);
								}	
							}
							lenumero = strlen(numero);
							if (lenumero == 3) {strcat(numerofinal, "0000000"); strcat(numerofinal, numero); memset(numero,0,1024);}
							if (lenumero == 4) {strcat(numerofinal, "000000"); strcat(numerofinal, numero); memset(numero,0,1024);}
							if (lenumero == 5) {strcat(numerofinal, "00000"); strcat(numerofinal, numero); memset(numero,0,1024);}
							if (lenumero == 6) {strcat(numerofinal, "0000"); strcat(numerofinal, numero); memset(numero,0,1024);}
							if (lenumero == 7) {strcat(numerofinal, "000"); strcat(numerofinal, numero); memset(numero,0,1024);}
							if (lenumero == 8) {strcat(numerofinal, "00"); strcat(numerofinal, numero); memset(numero,0,1024);}
							if (lenumero == 9) {strcat(numerofinal, "0"); strcat(numerofinal, numero); memset(numero,0,1024);}
							strcat(tramabix, numerofinal);
							memset(numerofinal,0,1024);
						}
						++cont;
						pch = strtok (NULL, "\t");
					}
				//printf("tramabix= %s\n",tramabix);
				FILE *destino = fopen(file,"a");
				fprintf(destino, "%s\n", tramabix);
				fclose(destino);
/*
				/////////// Pruebas
				FILE *destino1 = fopen(archivodepruebaZ,"a");
				fprintf(destino1, "%s\n", tramabix);
				fclose(destino1);
*/
				memset(tramaqp,0,1024);
				memset(tramabix,0,1024);
				memset(tramaqp,0,1024);
				
				retval = true;
			}
		}
	}
// REPORTE DE MEMORIA FISCAL POR NUMERO //
	else if (strcmp(cmd1, "U3A") == 0)
	{		
		char * cmdNroZ = (char *)malloc(10 * sizeof(char));
		char * NroZ = (char *)malloc(10 * sizeof(char));
		memset(cmdNroZ,0,10);
		memset(NroZ,0,10);

		strncat(cmdNroZ, &cmd[11], 4);
	// Determinar Fecha Actual
		strcpy(cmdQP, "F0;1");
		print.fncSendCommand(reinterpret_cast<BYTE*>(cmdQP), reinterpret_cast<BYTE*>(bufferQP));

		pch = strtok (bufferQP,"|");
		while (pch != NULL)
			{
				if (cont == 18) {strcpy(fechaQP, pch); break;}
				++cont;
				pch = strtok (NULL, "|");
			}
		strcpy(fechaHasta, fechaQP);
		// Se determina la fecha desde 7 dias antes de la fecha actual para sacar el Reporte Z
		strncat(diaQP, &fechaQP[0], 2);
		strncat(mesQP, &fechaQP[3], 2);
		strncat(anoQP, &fechaQP[6], 4);
		int dia = atoi(diaQP);
		int mes = atoi(mesQP);
		int ano = atoi(anoQP);
		for(i=0; i<10 ; i++)
		{
			dia = dia - 1;
			if (dia < 1) 
			{
				dia = 30;
				mes = mes - 1;
				if (mes < 1) { mes = 12; ano = (ano - 1); }
			}
		}
		itoa(dia,diaQP,10);
		itoa(mes,mesQP,10);
		itoa(ano,anoQP,10);
		int lendia = strlen(diaQP);
		int lenmes = strlen(mesQP);
		memset(fechaQP,0,12);
		if (lendia == 1) strcat(fechaQP, "0");
		strcat(fechaQP, diaQP); strcat(fechaQP, "/");
		if (lenmes == 1) strcat(fechaQP, "0");
		strcat(fechaQP, mesQP); strcat(fechaQP, "/");
		strcat(fechaQP, anoQP);

		strcpy(fechaDesde, fechaQP);
		
		// Generar Reporte Memoria Fiscal QP con DLL Seniat
		CloseFpctrl();
		bool vc = verificarConexion(identificadorMarca, identificadorModelo, puertoConexion);
		//cout << "verificarConexion: "  << vc << endl;
		bool mf = leerMemoriaFiscal(identificadorMarca, identificadorModelo, fechaDesde, fechaHasta, nombreArchivoSalidaMF);
		//cout << "leerMemoriaFiscal: "  << mf << endl;
		bool bxOpen = OpenFpctrl(puertoConexion);
		//cout << "OpenFpctrl: "  << bxOpen << endl;

		cont = 0;
		std::ifstream in(nombreArchivoSalidaMF);
		while (in.good())	//Contando lineas del archivo obtenido por DLL Seniat
		{
			++cont;
			in.getline(linea, 1024);
		}

		if (cont < 3)		//Indica que el archivo "QP_MemoriaFiscal" esta sin información
		{
			*status = 0;
			*error = 137;
			return false;
		}

		std::ifstream in1(nombreArchivoSalidaMF);
		while (in1.good())
		{
			++cont1;
			in1.getline(linea, 1024);
			if ((cont1 > 1) && (cont1 < cont))
			{
				strcat(tramaqp, linea);
				pch = strtok (linea,"\t");
				memset(NroZ,0,10);
				strcat(NroZ, pch);
				if (strcmp(NroZ, cmdNroZ) == 0)
				{
					break;
				}
				memset(tramaqp,0,1024);
			}
		}

		if (strcmp(tramaqp, "") == 0)	//No existe el Nro Z
		{
			*status = 0;
			*error = 137;
			return false;
		}

		cont = 0;
		pch = strtok (tramaqp,"\t");
		while (pch != NULL)
			{
			//Nro de Reporte Z
				if (cont == 0) strcat(tramabix, pch);
			//Fecha de Reporte Z
				if (cont == 1) 
				{
					strncat(tramabix, &pch[8],2); 
					strncat(tramabix, &pch[3],2); 
					strncat(tramabix, &pch[0],2);
				} 
			//Número de la última Factura
				else if (cont == 2) strcat(tramabix, pch);	
			//Fecha de la última factura
				else if (cont == 3) {strncat(tramabix, &pch[8],2); strncat(tramabix, &pch[3],2); strncat(tramabix, &pch[0],2);} 
			//Hora de la última factura
				else if (cont == 4) {strncat(tramabix, &pch[0],2); strncat(tramabix, &pch[3],2);}
			//Totales
				else if (cont > 4)
				{
					lenpch = strlen(pch);
					for(i=0; i<lenpch ; i++)				//Ventas Tasa General
					{
						strncpy(letra, &pch[i],1);
						if (strcmp(letra, ",") != 0)  
						{
							strcat(numero, letra);
						}	
					}
					lenumero = strlen(numero);
					if (lenumero == 3) {strcat(numerofinal, "0000000"); strcat(numerofinal, numero); memset(numero,0,1024);}
					if (lenumero == 4) {strcat(numerofinal, "000000"); strcat(numerofinal, numero); memset(numero,0,1024);}
					if (lenumero == 5) {strcat(numerofinal, "00000"); strcat(numerofinal, numero); memset(numero,0,1024);}
					if (lenumero == 6) {strcat(numerofinal, "0000"); strcat(numerofinal, numero); memset(numero,0,1024);}
					if (lenumero == 7) {strcat(numerofinal, "000"); strcat(numerofinal, numero); memset(numero,0,1024);}
					if (lenumero == 8) {strcat(numerofinal, "00"); strcat(numerofinal, numero); memset(numero,0,1024);}
					if (lenumero == 9) {strcat(numerofinal, "0"); strcat(numerofinal, numero); memset(numero,0,1024);}
					strcat(tramabix, numerofinal);
					memset(numerofinal,0,1024);
				}
				++cont;
				pch = strtok (NULL, "\t");
			}
		FILE *destino = fopen(file,"w");
		fprintf(destino, "%s\n", tramabix);
		fclose(destino);
		retval = true;
/*		/////////// Pruebas
		FILE *destino1 = fopen(archivodepruebaZ,"a");
		fprintf(destino1, "%s\n", tramabix);
		fclose(destino1);
*/
	}
	else 
	{
		strcpy(tramabix, "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
		FILE *destino = fopen(file,"a");
		fprintf(destino, "%s\n", tramabix);
		fclose(destino);
/*		/////////// Pruebas
		FILE *destino1 = fopen(archivodepruebaZ,"a");
		fprintf(destino1, "%s\n", tramabix);
		fclose(destino1);
*/
		retval = true;
	}

	ReadFpStatus(status, error);

/*	FILE *Funcion = fopen(archivofuncion,"a+");
	fprintf(Funcion, "\nFunción UploadReportCmd Comando: %s File: %s Status: %i Error: %i\n", cmd, file, *status, *error);
	fclose(Funcion);
*/
/*
	free(cmdQP);
//	free(bufferQP);
	free(fechaQP);
//	free(tramaqp);
	free(tramabix);
	free(letra);
	free(numero);
	free(numerofinal);
	free(cmd1);
	free(diaQP);
	free(mesQP);
	free(anoQP);
	free(Campo20);
	free(Campo21);
	free(Campo22);
//	free(linea);
*/
	return retval;
}

_declspec(dllexport) bool _stdcall UploadStatusCmd(LPINT status, LPINT error, LPCSTR cmd, LPCSTR file)
{
	char * cmdStatus = (char *)malloc(10 * sizeof(char));
	memset(cmdStatus,0,10);
	char * cmdQP = (char *)malloc(10 * sizeof(char));
	memset(cmdQP,0,10);
	char * bufferQP = (char *)malloc(1024 * sizeof(char));
	memset(bufferQP,0,1024);
	char * tramaStatusBix = (char *)malloc(1024 * sizeof(char));
	memset(tramaStatusBix,0,1024);
	char * Campo2 = (char *)malloc(4 * sizeof(char));
	char * Campo17 = (char *)malloc(15 * sizeof(char));
	char * Campo18 = (char *)malloc(15 * sizeof(char));
	char * Campo19 = (char *)malloc(15 * sizeof(char));
	char * Campo21 = (char *)malloc(15 * sizeof(char));
	char * Campo22 = (char *)malloc(8 * sizeof(char));
	char * Campo23 = (char *)malloc(15 * sizeof(char));
	char * Campo26 = (char *)malloc(15 * sizeof(char));
	char * Campo27 = (char *)malloc(15 * sizeof(char));
	char * Campo28 = (char *)malloc(15 * sizeof(char));
	char * Campo29 = (char *)malloc(15 * sizeof(char));
	char * Campo30 = (char *)malloc(15 * sizeof(char));
	char * Campo31 = (char *)malloc(15 * sizeof(char));
	char * Campo32 = (char *)malloc(15 * sizeof(char));
	memset(Campo2,0,4);
	memset(Campo17,0,15);
	memset(Campo18,0,15);
	memset(Campo19,0,15);
	memset(Campo21,0,15);
	memset(Campo22,0,8);
	memset(Campo23,0,15);
	memset(Campo26,0,15);
	memset(Campo27,0,15);
	memset(Campo28,0,15);
	memset(Campo29,0,15);
	memset(Campo30,0,15);
	memset(Campo31,0,15);
	memset(Campo32,0,15);
	char * fechaQP = (char *)malloc(8 * sizeof(char));
	memset(fechaQP,0,8);
	char * horaQP = (char *)malloc(6 * sizeof(char));
	memset(horaQP,0,6);
	char * linea = (char *)malloc(1024 * sizeof(char));
	memset(linea,0,1024);
	char * strBI = (char *)malloc(500 * sizeof(char));
	memset(strBI,0,500);
	char * Base_I = (char *)malloc(500 * sizeof(char));
	memset(Base_I,0,500);
	char * strIVA = (char *)malloc(500 * sizeof(char));
	memset(strIVA,0,500);
	char * IVA_Total = (char *)malloc(500 * sizeof(char));
	memset(IVA_Total,0,500);
	char * strPagar = (char *)malloc(500 * sizeof(char));
	memset(strPagar,0,500);
	char * TotalPagar = (char *)malloc(500 * sizeof(char));
	memset(TotalPagar,0,500);
	char * Tasa1 = (char *)malloc(6 * sizeof(char));
	memset(Tasa1,0,6);
	char * Tasa2 = (char *)malloc(6 * sizeof(char));
	memset(Tasa2,0,6);
	char * Tasa3 = (char *)malloc(6 * sizeof(char));
	memset(Tasa3,0,6);
	char * Serial = (char *)malloc(15 * sizeof(char));
	memset(Serial,0,15);
	char * pch;
	int BIG = 0;
	int BIR = 0;
	int BIA = 0;
	int Exen = 0;
	int BI = 0;
	int cont = 0;
	int IVAG = 0;
	int IVAR = 0;
	int IVAA = 0;
	int IVA = 0;
	int Pagar = 0;
	strcpy(puertoConexion, strPort);
	strcpy(cmdStatus, cmd);

//Obtener Campos de F0;3 QPrint
	strcpy(cmdQP, "F0;3");
	print.fncSendCommand(reinterpret_cast<BYTE*>(cmdQP), reinterpret_cast<BYTE*>(bufferQP));
	printf("bufferQP %s\n", bufferQP);
	if (strcmp(bufferQP, "") != 0)
	{
		pch = strtok (bufferQP,"|");
		while (pch != NULL)
		{
			if(cont == 2) strcpy(Campo2, pch);
			else if(cont == 17) strcpy(Campo17, pch);	// Serial
			else if(cont == 18)							// Fecha
			{
				strcpy(Campo18, pch);
				strncat(fechaQP, &Campo18[0], 2);
				strncat(fechaQP, &Campo18[3], 2);
				strncat(fechaQP, &Campo18[8], 2);
			}
			else if(cont == 19)							// Hora
			{
				strcpy(Campo19, pch);
				strncat(horaQP, &Campo19[0], 2);
				strncat(horaQP, &Campo19[3], 2);
				strcat(horaQP, "00");
			}
			else if(cont == 21) strcpy(Campo21, pch);	// Nro. última Factura
			else if(cont == 22) strcpy(Campo22, pch);	// Nro. última Z
			else if(cont == 23) strcpy(Campo23, pch);	// Nro. último DNF
			else if(cont == 26) strcpy(Campo26, pch);	// BI G
			else if(cont == 27) strcpy(Campo27, pch);	// IVA G
			else if(cont == 28) strcpy(Campo28, pch);	// BI R
			else if(cont == 29) strcpy(Campo29, pch);	// IVA R
			else if(cont == 30) strcpy(Campo30, pch);	// BI A
			else if(cont == 31) strcpy(Campo31, pch);	// IVA A
			else if(cont == 32) strcpy(Campo32, pch);	// Exento

			++cont;
			pch = strtok (NULL, "|");
		}
	}

	if (strcmp(Campo17, "") == 0) strcpy(Serial, "??????????");		//Sin Nro de Serial
	else 
	{
		strcpy(Serial, "Z1B");
		strncat(Serial, &Campo17[3], 7);
	}
	if (strcmp(fechaQP, "") == 0) strcpy(Campo18, "000000");
	if (strcmp(horaQP, "") == 0) strcpy(Campo19, "000000");
	if (strcmp(Campo21, "") == 0) strcpy(Campo21, "00000000");
	if (strcmp(Campo22, "") == 0) strcpy(Campo22, "0000");
	if (strcmp(Campo23, "") == 0) strcpy(Campo23, "00000000");
	if (strcmp(Campo26, "") == 0) strcpy(Campo26, "00000000");
	if (strcmp(Campo27, "") == 0) strcpy(Campo27, "00000000");
	if (strcmp(Campo28, "") == 0) strcpy(Campo28, "00000000");
	if (strcmp(Campo29, "") == 0) strcpy(Campo29, "00000000");
	if (strcmp(Campo30, "") == 0) strcpy(Campo30, "00000000");
	if (strcmp(Campo31, "") == 0) strcpy(Campo31, "00000000");
	if (strcmp(Campo32, "") == 0) strcpy(Campo32, "00000000");

//S1
	if (strcmp(cmd, "S1") == 0) 
		{
		//Completar tramaStatusBix
			strcpy(tramaStatusBix, "S100");				//S1 por defecto y 00 primer cajero de QPrint
			strcat(tramaStatusBix, "00000000000000000");//Total de Ventas diarias (NO QPRINT)
			strcat(tramaStatusBix, Campo21);			//Nro última factura
			strcat(tramaStatusBix, "00000");			//Cant. Fact. en el día (NO QPRINT)
			strcat(tramaStatusBix, Campo23);			//Nro último DNF
			strcat(tramaStatusBix, "00000");			//Cant. DNF en el día (NO QPRINT)
			strcat(tramaStatusBix, Campo22);			//Nro último DNF
			strcat(tramaStatusBix, "0000");				//Cant. Reportes de auditoria (NO QPRINT)
			strcat(tramaStatusBix, tramaRIF);			//RIF
			strcat(tramaStatusBix, Serial);				//Serial Equipo
			strcat(tramaStatusBix, horaQP);				//Hora
			strcat(tramaStatusBix, fechaQP);			//Fecha
			FILE *destino = fopen(file,"w");
			fprintf(destino, "%s\n", tramaStatusBix);
			fclose(destino);

/*			/////////// Pruebas
			FILE *destino2 = fopen(archivodepruebaS1,"a");
			fprintf(destino2, "__________________\nCampo2: %s\nCampo17: %s\nCampo18: %s\nCampo19: %s\nCampo21: %s\nCampo22: %s\nCampo23: %s\nCampo26: %s\nCampo27: %s\nCampo28: %s\nCampo29: %s\nCampo30: %s\nCampo31: %s\nCampo32: %s\n", Campo2, Campo17, Campo18, Campo19, Campo21, Campo22, Campo23, Campo26, Campo27, Campo28, Campo29, Campo30, Campo31, Campo32);
			fprintf(destino2, "UploadStatus1:\n%s\n", tramaStatusBix);
			fclose(destino2);
*/
		}

//S2
	if (strcmp(cmd, "S2") == 0) 
		{
			if (strcmp(Campo2, "R") != 0) 
			{
				BIG = atoi (Campo26);
				BIR = atoi (Campo28);
				BIA = atoi (Campo30);
				Exen = atoi (Campo32);

				IVAG = atoi (Campo27);
				IVAR = atoi (Campo29);
				IVAA = atoi (Campo31);
			}
			BI = BIG + BIR + BIA + Exen;
			IVA = IVAG + IVAR + IVAA;
			Pagar = BI + IVA;
			itoa(BI, strBI,10);
			itoa(IVA, strIVA,10);
			itoa(Pagar, strPagar,10);

			//Los montos deben ser de Longitud = 13
			int lenBI = strlen(strBI);
			if (lenBI == 1) strcat(Base_I, "000000000000"); 
			else if (lenBI == 2) strcat(Base_I, "00000000000"); 
			else if (lenBI == 3) strcat(Base_I, "0000000000"); 
			else if (lenBI == 4) strcat(Base_I, "000000000"); 
			else if (lenBI == 5) strcat(Base_I, "00000000");
			else if (lenBI == 6) strcat(Base_I, "0000000"); 
			else if (lenBI == 7) strcat(Base_I, "000000"); 
			else if (lenBI == 8) strcat(Base_I, "00000"); 
			else if (lenBI == 9) strcat(Base_I, "0000"); 
			else if (lenBI == 10) strcat(Base_I, "000"); 
			else if (lenBI == 11) strcat(Base_I, "00"); 
			else if (lenBI == 12) strcat(Base_I, "0");
			strcat(Base_I, strBI);

			int lenIVA = strlen(strIVA);
			if (lenIVA == 1) strcat(IVA_Total, "000000000000"); 
			else if (lenIVA == 2) strcat(IVA_Total, "00000000000");
			else if (lenIVA == 3) strcat(IVA_Total, "0000000000");
			else if (lenIVA == 4) strcat(IVA_Total, "000000000");
			else if (lenIVA == 5) strcat(IVA_Total, "00000000");
			else if (lenIVA == 6) strcat(IVA_Total, "0000000");
			else if (lenIVA == 7) strcat(IVA_Total, "000000");
			else if (lenIVA == 8) strcat(IVA_Total, "00000");
			else if (lenIVA == 9) strcat(IVA_Total, "0000");
			else if (lenIVA == 10) strcat(IVA_Total, "000");
			else if (lenIVA == 11) strcat(IVA_Total, "00");
			else if (lenIVA == 12) strcat(IVA_Total, "0");
			strcat(IVA_Total, strIVA);

			int lenPagar = strlen(strPagar);
			if (lenPagar == 1) strcat(TotalPagar, "000000000000"); 
			else if (lenPagar == 2) strcat(TotalPagar, "00000000000");
			else if (lenPagar == 3) strcat(TotalPagar, "0000000000");
			else if (lenPagar == 4) strcat(TotalPagar, "000000000");
			else if (lenPagar == 5) strcat(TotalPagar, "00000000");
			else if (lenPagar == 6) strcat(TotalPagar, "0000000");
			else if (lenPagar == 7) strcat(TotalPagar, "000000");
			else if (lenPagar == 8) strcat(TotalPagar, "00000");
			else if (lenPagar == 9) strcat(TotalPagar, "0000");
			else if (lenPagar == 10) strcat(TotalPagar, "000");
			else if (lenPagar == 11) strcat(TotalPagar, "00");
			else if (lenPagar == 12) strcat(TotalPagar, "0");
			strcat(TotalPagar, strPagar);
			//printf("TotalPagar %s\n", TotalPagar);
			

		//Completar tramaStatusBix
			strcpy(tramaStatusBix, "S2 ");						//S2
			strcat(tramaStatusBix, Base_I);						//Subtotal de Bases Imponibles 
			strcat(tramaStatusBix, " ");						//Carácter Espacio
			strcat(tramaStatusBix, IVA_Total);					//Subtotal de IVA
			strcat(tramaStatusBix, " 0000000000000000000 ");	//Carácter Espacio y Data Dummy
			strcat(tramaStatusBix, TotalPagar);					//Monto por Pagar 
			strcat(tramaStatusBix, "00000");					//Nro Pagos Realizados y Condición (NO QPRINT)
			FILE *destino = fopen(file,"w");
			fprintf(destino, "%s\n", tramaStatusBix);
			fclose(destino);
		}

//S3
	if (strcmp(cmd, "S3") == 0) 
	{
	//Obtener Alícuotas de Archivo de Texto
		cont = 0;
		std::ifstream in(archivoAlicuotas);
		while (in.good())
		{
			in.getline(linea, 1024);
		}
		pch = strtok (linea,"\t");
		while (pch != NULL)
		{
			if(cont == 0) strcpy(Tasa1, pch);
			if(cont == 1) strcpy(Tasa2, pch);
			if(cont == 2) strcpy(Tasa3, pch);
			++cont;
			pch = strtok (NULL, "\t");
		}

		
	//Completar tramaStatusBix
		strcpy(tramaStatusBix, "S32");					//S3 y Tipo de Tasa1
		strcat(tramaStatusBix, Tasa1);					//Tasa1
		strcat(tramaStatusBix, "2");					//Tipo de Tasa2
		strcat(tramaStatusBix, Tasa2);					//Tasa2
		strcat(tramaStatusBix, "2");					//Tipo de Tasa3
		strcat(tramaStatusBix, Tasa3);					//Tasa3
		strcat(tramaStatusBix, "00000000000000000000");	//System Flags 1-20 Bixolon (NO QPRINT)
		strcat(tramaStatusBix, "00000000000000000000");	//con longitud = 40
		FILE *destino = fopen(file,"w");
		fprintf(destino, "%s\n", tramaStatusBix);
		fclose(destino);
	}

//S4
	if (strcmp(cmd, "S4") == 0) 
	{
		strcpy(tramaStatusBix, "S4");					//S4 (NO QPRINT)
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 1
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 2
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 3
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 4
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 5
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 6
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 7
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 8
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 9
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 10
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 11
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 12
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 13
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 14
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 15
		strcat(tramaStatusBix, "000000000");			//Medio de Pago 16
		FILE *destino = fopen(file,"w");
		fprintf(destino, "%s\n", tramaStatusBix);
		fclose(destino);
	}

//S5
	if (strcmp(cmd, "S5") == 0) 
	{
	//Completar tramaStatusBix
		strcpy(tramaStatusBix, "S5");					//S5
		strcat(tramaStatusBix, tramaRIF);				//RIF
		strcat(tramaStatusBix, Serial);					//Serial del Equipo
		strcat(tramaStatusBix, "000000000000000000");	//Estados de la Memoria de Auditoria (NO QPRINT)
		FILE *destino = fopen(file,"w");
		fprintf(destino, "%s\n", tramaStatusBix);
		fclose(destino);
	}

	ReadFpStatus(status, error);

/*	FILE *Funcion = fopen(archivofuncion,"a+");
	fprintf(Funcion, "\nFunción UploadStatusCmd Comando: %s File: %s Status: %i Error: %i\n", cmd, file, *status, *error);
	fclose(Funcion);
*/
/*
	free (cmdStatus);
	free (cmdQP);
//	free (bufferQP);
	free (tramaStatusBix);
	free (Campo2);
	free (Campo17);
	free (Campo18);
	free (Campo19);
	free (Campo21);
	free (Campo22);
	free (Campo23);
	free (Campo26);
	free (Campo27);
	free (Campo28);
	free (Campo29);
	free (Campo30);
	free (Campo31);
	free (Campo32);
	free (fechaQP);
	free (horaQP);
//	free (linea);
	free (strBI);
	free (Base_I);
	free (strIVA);
	free (IVA_Total);
	free (strPagar);
	free (TotalPagar);
	free (Tasa1);
	free (Tasa2);
	free (Tasa3);
	free (Serial);
*/
	return 1;
}