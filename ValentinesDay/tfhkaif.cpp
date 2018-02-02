// tfhkaif.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include "protocol.h"

//#include <stdio.h>
//#include <assert.h>
//#include <WTypes.h>
//#include <oleauto.h>
//#include <comutil.h>
//#include <tchar.h>
//#include <stdlib.h>
#include <assert.h>
#include <map>
//#include <iostream>
//#include <sstream>
//#include <istream>
//#include <string>
//#include <iomanip>
//#include <strstream>

#include "char_array_buffer.hpp"
//#include "output_buffer.hpp"

//using namespace std;
using namespace Quorion;

#define Q_NET	1       /* set to 1 to include ethernet */

#if Q_NET == 1
#pragma comment(lib, "wsock32.lib")
#include <winsock2.h>

#define UDP_COMP	2030            /* IP port for computer */

#endif

/*
#define _TEXT(t) L ## t

#if defined(_UNICODE) 
	#define _T(x) L ##x 
#else 
	#define _T(x) x 
#endif 
*/

char Version[] = {"Release v1.00 12/03/2012"};

#define COM_RETRY   3		//5
#define CMD_RETRY   2		//5
#define COM_TIMER   2000    /* response time in msec (2000) */
#define COMPRESS    1       /* MUST always be SET !! */

#define NUL         0x00
#define SOH         0x01
#define STX         0x02
#define ETX         0x03
#define EOT         0x04
#define ENQ         0x05
#define ACK         0x06
#define BEL         0x07
#define BS          0x08
#define HT          0x09
#define LF          0x0a
#define VT          0x0b
#define FF          0x0c
#define CR          0x0d
#define SO          0x0e
#define SI          0x0f
#define DLE         0x10
#define DC1         0x11
#define DC2         0x12
#define DC3         0x13
#define DC4         0x14
#define NAK         0x15
#define SYN         0x16
#define ETB         0x17
#define CAN         0x18
#define EM          0x19
#define SUB         0x1a
#define ESC         0x1b
#define FS          0x1c
#define GS          0x1d
#define RS          0x1e
#define US          0x1f


int TIMEOUTS[9] = {
    COM_TIMER * 5,      /* dummy */
    COM_TIMER * 5,      /* 1200 baud */
    COM_TIMER * 4,      /* 2400 baud */
    COM_TIMER * 3,      /* 4800 baud */
    COM_TIMER * 3,      /* 9600 baud */
    COM_TIMER * 2,      /* 19200 baud */
    COM_TIMER,      /* 38400 baud */
    COM_TIMER,      /* 57600 baud */
    COM_TIMER,      /* 115200 baud */
};

DWORD BAUDRATE[8] = {
    CBR_1200,	/* bixolon */
    CBR_2400,
    CBR_4800,
    CBR_9600,
    CBR_19200,
    CBR_38400,
    CBR_57600,	/* qprint */
    CBR_115200,
};

LPCTSTR COMPORT[8] = {
    L"COM1",
    L"COM2",
    L"COM3",
    L"COM4",
    L"COM5",
    L"COM6",
    L"COM7",
    L"COM8",
};

        //WORD MBAUDRATE(int baudRate)
        //{
        //    WORD retval = 3;
        //    switch (baudRate)
        //    {
        //        case 1200: retval = 0; break;
        //        case 2400: retval = 1; break;
        //        case 4800: retval = 2; break;
        //        case 9600: retval = 3; break;
        //        case 19200: retval = 4; break;
        //        case 38400: retval = 5; break;
        //        case 57600: retval = 6; break;
        //        case 115200: retval = 7; break;
        //    }
        //    return retval;
        //}

char WORDSIZE[12][3] = {
    {8, NOPARITY, ONESTOPBIT},		/* 8 data, no parity, 1 stop */
    {8, NOPARITY, TWOSTOPBITS},		/* 8 data, no parity, 2 stop */
    {8, EVENPARITY, ONESTOPBIT},	/* 8 data, even parity, 1 stop */
    {8, EVENPARITY, TWOSTOPBITS},	/* 8 data, even parity, 2 stop */
    {8, ODDPARITY, ONESTOPBIT},		/* 8 data, odd parity, 1 stop */
    {8, ODDPARITY, TWOSTOPBITS},	/* 8 data, odd parity, 2 stop */
    {7, NOPARITY, ONESTOPBIT},		/* 7 data, no parity, 1 stop */
    {7, NOPARITY, TWOSTOPBITS},		/* 7 data, no parity, 2 stop */
    {7, EVENPARITY, ONESTOPBIT},	/* 7 data, even parity, 1 stop */
    {7, EVENPARITY, TWOSTOPBITS},	/* 7 data, even parity, 2 stop */
    {7, ODDPARITY, ONESTOPBIT},		/* 7 data, odd parity, 1 stop */
    {7, ODDPARITY, TWOSTOPBITS},	/* 7 data, odd parity, 2 stop */
};

//---------------------------------------------------------------------------
struct SETTINGS {
    WORD ComPort;
    WORD BaudRate;
    WORD WordSize;
    WORD Register;
    BYTE IP[4];
} Settings;


BYTE
    RxBuffer[1024], weft[1024];
int
    RxCount = 0,
    RxStat = 0,
    RxCrc,
	_rxcount;

HANDLE
    hComFile;       /* handle for comm port */

#if Q_NET == 1

SOCKET Q_Socket;
SOCKADDR_IN Q_Addr;
SOCKADDR_IN Q_RemoteAddr;
int Q_RemoteAddrLen;

#endif

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

typedef std::map<char*, char*, ltstr> mid; //Map ID
mid translator;

typedef std::map<int, char*, ltint> mfits; //Map From Int To String
mfits errQprint;
mfits errBixolon;

typedef std::multimap<int, int, ltint> mmid; //MultiMap ID
mmid mapErrors;

Protocol Lexer;

void LoadDictionary()
{
	//
	translator.insert(mid::value_type("I0Z", "F3;1"));		// reporte Z
	translator.insert(mid::value_type("I0X", "F3;1;1"));	// reporte X
	//
	//errQprint.insert(mfits::value_type(0, "NO ERROR");
	//
	//errBixolon.insert(mfits::value_type(0, "NO ERROR");
	//
	mapErrors.insert(mmid::value_type(0, 0));
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

//extern "C" __declspec(dllexport) int SetSettings(WORD comPort, WORD baudRate, WORD wordSize, WORD reg);
//extern "C" __declspec(dllexport) int GetSettings(int index);
//extern "C" __declspec(dllexport) int OpenPort(void);
//extern "C" __declspec(dllexport) int ClosePort(void);
//extern "C" __declspec(dllexport) int UploadData(BYTE *rec, WORD len);
//extern "C" __declspec(dllexport) char* HelloWorld(char* name);

__declspec(dllexport) int __stdcall GetVer(char* ver)
{
	assert(ver);
	strcpy(ver, Version);
	return 1;
}

__declspec(dllexport) int __stdcall HelloWorld(char* name, char* resp)
//char* HelloWorld(char* name)
{
	int i = 0;
	while (*name != '\0')
	{
		i++;
		name++;
	}
	char* nameManArr = new char[i];
	name -= i;
	i = 0;
	while (*name != '\0')
	{
		nameManArr[i] = *name;
		name++;
		i++;
	}
	nameManArr[i] = '\0';
	name -= i;

	strncpy(resp, nameManArr, i);

	/*
	// reserve memory for the OLECHAR-string
	OLECHAR *sOleText=new OLECHAR[strlen(nameManArr)+1];

	// convert the char-string to OLECHAR-string
	mbstowcs(sOleText,nameManArr,strlen(nameManArr)+1); // +1 means: don't forget the terminating null character
	*resp = ::SysAllocString(sOleText);
	*/

	/*
	CComBSTR val("Hello World");
	int cw = lstrlenW(val);
	int cc = ::WideCharToMultiByte(CP_ACP,0,val,cw,NULL,0,NULL,NULL);
	resp = new char[cc+1];
	cc=WideCharToMultiByte(CP_ACP,0,val,cw,resp,cc,NULL,NULL);
	resp[cc]='\0';
	*/

	/*
	bstrStart = new _bstr_t(_TEXT("HOLA"));
	resp = static_cast<char *>(*bstrStart);
	*/

	//wchar_t mystring[] = _TEXT("flipcode");
	//resp = reinterpret_cast<char *>(&mystring[0]);	
	
	/*
	WCHAR *wszBuff = NULL;
	wszBuff = _com_util::ConvertStringToBSTR(name);

	//_bstr_t bstrStart(_T(name));
	bstrStart.Assign(_com_util::ConvertStringToBSTR(name));
	TCHAR szFinal[255];
	_stprintf(szFinal, _T("%s"), (LPCTSTR)bstrStart);

    // Create the CComBSTR object
	CComBSTR bstrString("Hello World");
	// Convert the string to uppercase
	bstrString.ToUpper();
	// Return a copy of the string.
	//return bstrString.CopyTo(bstrStringPtr);

	//resp = (char*)malloc(255 * sizeof(char));
	wcstombs(resp,_com_util::ConvertStringToBSTR(name),255);

	//resp = _com_util::ConvertStringToBSTR(name);
	//resp = reinterpret_cast<char *>(&bstrString.m_str);
	//resp = static_cast<char *>(bstrStart);
	//strcpy(resp,(char *)bstrStart);

	//resp = ::SysAllocString(L"Hola");
	//strncpy(resp, nameManArr,i);
	//_bstr_t bstrIntermediate(name);
	// reserve memory for the OLECHAR-string
	OLECHAR *sOleText=new OLECHAR[i+1];

	// convert the char-string to OLECHAR-string
	mbstowcs(sOleText,name,i+1); // +1 means: don't forget the terminating null character

	BSTR bstrStart = ::SysAllocString(sOleText); 
	TCHAR szFinal[255];
	_stprintf(szFinal, _T("%s"), (LPCTSTR)bstrStart);

	resp = (char*)malloc(255 * sizeof(char));

	#ifndef _UNICODE
	strcpy(resp, szFinal);
	#else
	//Convert wchar_t* to char*
	WideCharToMultiByte(...); 
	#endif

	_bstr_t indata = _bstr_t("Din Saveme konto behøver din opmærksomhed");
	*/	

	return i;
}

/*
__declspec(dllexport) char* __stdcall HelloWorld(char* name)
//char* HelloWorld(char* name)
{
   int i = 0;
   while (*name != '\0')
   {
      i++;
      name++;
   }
   char* nameManArr = new char[i];
   name -= i;
   i = 0;
   while (*name != '\0')
   {
      nameManArr[i] = *name;
      name++;
      i++;
   }
   nameManArr[i] = '\0';
   return nameManArr;
}
*/


/* Funciones QComms */

//int GetSettings(int read)
//{
//    TFileName SettingsFile;
//    HANDLE hsetfile;       /* handle for settings file */
//
//    DWORD   BytesWritten;
//
//    SettingsFile = ChangeFileExt(Application->ExeName,".SET");
//
//    if (read)
//    {
//        hsetfile = CreateFile(SettingsFile.c_str(), GENERIC_READ, 0,
//                            NULL, OPEN_EXISTING, 0, NULL);
//        if(hsetfile == INVALID_HANDLE_VALUE)
//        {
//            Settings.BaudRate = 6;
//            Settings.ComPort = 0;
//            Settings.WordSize = 0;
//            Settings.Register = 0;
//            Settings.IP[0] = 0;
//            Settings.IP[1] = 0;
//            Settings.IP[2] = 0;
//            Settings.IP[3] = 0;
//        }
//        else
//        {
//            ReadFile(hsetfile, &Settings, sizeof(Settings), &BytesWritten, NULL);
//            if (Settings.BaudRate > 7)
//                Settings.BaudRate = 7;
//#if Q_NET == 1
//            if (Settings.ComPort > 8)
//#else
//            if (Settings.ComPort > 7)
//#endif
//                Settings.ComPort = 0;
//            if (Settings.WordSize > 11)
//                Settings.WordSize = 0;
//            if (Settings.Register > 24)
//                Settings.Register = 0;
//
//            CloseHandle(hsetfile);
//            return 1;
//        }
//    }
//
//    hsetfile = CreateFile(SettingsFile.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
//                            NULL, CREATE_ALWAYS, 0, NULL);
//    if(hsetfile == INVALID_HANDLE_VALUE)
//    {
//        Application->MessageBox(SettingsFile.c_str(),"File Create Error",MB_OK|MB_ICONERROR);
//        return 0;
//    }
//    if (!WriteFile(hsetfile, &Settings, sizeof(Settings), &BytesWritten, NULL))
//        Application->MessageBox(SettingsFile.c_str(),"File Read Error",MB_OK|MB_ICONERROR);
//
//    CloseHandle(hsetfile);
//    return 1;
//}

//---------------------------------------------------------------------------

//void ShowRecord(int type, char *rec, int len)
//{
//    AnsiString data_str;
//    int count;
//
//    if (type == 3)
//    {
//        data_str = "-- DUPLICATE RECORD RECEIVED --";
//    }
//    else if (type == 4)
//    {
//        data_str = "-- RETRY --";
//    }
//    else if (type == 5)
//    {
//        data_str = "-- TIME OUT --";
//    }
//    else
//    {
//        data_str = GetTickCount();
//        if (type == 1)  /* valid record received */
//            data_str += String(" RX<-- ");
//        else if (type == 2)     /* record with CRC error received */
//            data_str += String(" RX<-CRC-ERROR- ");
//        else
//        {
//            data_str += String(" TX--> ");
//            if (Settings.Register && Settings.ComPort != 8)   /* sent via register network */
//            {
//                data_str += String("#")+String(Settings.Register/10)+String(Settings.Register%10);
//            }
//        }
//        if (rec[0] > US)        /* data field contains ascii */
//            data_str += String(rec);
//        else if (rec[0] == ACK)
//        {
//            data_str += String("[ACK]");
//            if (type == 1)      /* RX then second byte is status code */
//                data_str += String("[")+String((unsigned char)rec[1])+String("]");
//        }
//        else if (rec[0] == NAK)
//            data_str += String("[NAK]");
//        else if (rec[0] == EOT)
//            data_str += String("[EOT]");
//        else if (rec[0] == SYN)
//            data_str += String("[SYN]");
//        else
//            data_str += String("Invalid Data");
//    }
//    count = MainForm->Memo1->Lines->Count;
//    MainForm->Memo1->Lines->Append(data_str);
//    if (count == MainForm->Memo1->Lines->Count)
//    {                                        /* clear Memo when full */
//        MainForm->Memo1->Clear();
//        MainForm->Memo1->Lines->Append(data_str);   /* add again */
//    }
//}

//void SetSettings(WORD portName, WORD baudRate, int databits, Parities parity, StopBit stopBit)
//{
//}

__declspec(dllexport) int __stdcall SetComSettings(WORD comPort, WORD baudRate, WORD wordSize, WORD reg)
{
	Settings.BaudRate = baudRate > 7 ? 7 : baudRate;
#if Q_NET == 1
    if (comPort > 8)
#else
    if (comPort > 7)
#endif
		comPort = 0;
	Settings.ComPort = comPort;
	Settings.WordSize = wordSize > 11 ? 0 : wordSize;
	Settings.Register = reg > 24 ? 0 : reg;

    Settings.IP[0] = 0;
    Settings.IP[1] = 0;
    Settings.IP[2] = 0;
    Settings.IP[3] = 0;
	return 1;
}

__declspec(dllexport) int __stdcall SetIPSettings(BYTE ip0, BYTE ip1, BYTE ip2, BYTE ip3, WORD reg = 0)
{
	Settings.BaudRate = 6;
	Settings.ComPort  = 8;
	Settings.WordSize = 0;
	Settings.Register = reg;

    Settings.IP[0] = ip0;
    Settings.IP[1] = ip1;
    Settings.IP[2] = ip2;
    Settings.IP[3] = ip3;
	return 1;
}

__declspec(dllexport) int __stdcall GetComSettings(int index)
{
	int retval = -1;
	switch(index)
	{
	case 0: retval = (int)Settings.ComPort; break;
	case 1: retval = (int)Settings.BaudRate; break;
	case 2: retval = (int)Settings.WordSize; break;
	case 3: retval = (int)Settings.Register; break;
	}
	return retval;
}

__declspec(dllexport) int __stdcall GetIPSettings(int index)
{
	if(index >= 0 && index <= 3)
		return Settings.IP[index];
	else if(index == 4)
		return Settings.Register;
	else return -1;
}

void ShowRecord(int type, char *rec, int len)
{
}

#if Q_NET == 1

int SetIPaddress(void)
{
	char tmp_addr[20];
    BYTE mcno;

    mcno = Settings.IP[3];
    if (Settings.Register > 1)      /* register is BASE + (register-1) */
        mcno += Settings.Register-1;
    sprintf(tmp_addr, "%d.%d.%d.%d", Settings.IP[0], Settings.IP[1], Settings.IP[2], mcno);

    Q_Addr.sin_addr.s_addr = inet_addr(tmp_addr);
    if (Q_Addr.sin_addr.s_addr == INADDR_NONE)
    {
        //Application->MessageBox(COMPORT[Settings.ComPort], "Invalid IP address",MB_OK|MB_ICONWARNING);
		printf("%s Invalid IP address", COMPORT[Settings.ComPort]);
        return 0;
    }
    else
        return 1;
}

int OpenWinsock(void)
{
	//std::string addr;
    WSADATA wsa;
    int RecvTimeout = 2000;

    if (!SetIPaddress())        /* no valid IP address */
        return 0;
    if (WSAStartup(MAKEWORD(2,0), &wsa))
    {
        //Application->MessageBox(COMPORT[Settings.ComPort], "Error Opening",MB_OK|MB_ICONWARNING);
		printf("%s Error Opening", COMPORT[Settings.ComPort]);
        return 0;       /* error opening */
    }
	//Create UDP Socket

    Q_RemoteAddrLen = sizeof(SOCKADDR_IN);
    Q_Socket = socket(AF_INET, SOCK_DGRAM,0);
    if(Q_Socket == INVALID_SOCKET)
    {
        WSACleanup();
        //Application->MessageBox(COMPORT[Settings.ComPort], "Invalid Socket",MB_OK|MB_ICONWARNING);
		printf("%s Invalid Socket", COMPORT[Settings.ComPort]);
        return 0;
    }

    setsockopt(Q_Socket, SOL_SOCKET, SO_RCVTIMEO,(char*)&RecvTimeout, sizeof(RecvTimeout));
    Q_Addr.sin_family = AF_INET;
    Q_Addr.sin_port = htons(UDP_COMP);
    return 1;
}

void CloseWinsock(void)
{
  closesocket(Q_Socket);
  WSACleanup();
}

#endif

//---------------------------------------------------------------------------
void ResetCommError(void)
{
    DCB dcb;
    DWORD com_error;

    /* clear TX and RX Buffers */
    PurgeComm(hComFile, PURGE_TXABORT+PURGE_RXABORT+PURGE_TXCLEAR+PURGE_RXCLEAR);
    /* clear error Status */
    ClearCommError(hComFile, &com_error, NULL);//clears the device's error flag to enable
    /* re-init port else comms is halted */
    GetCommState(hComFile, &dcb);
    SetCommState(hComFile, &dcb);
}

//---------------------------------------------------------------------------

__declspec(dllexport) int __stdcall OpenPort(void)
{
    COMMTIMEOUTS Commtimeouts;
    DCB dcb;

#if Q_NET == 1
    if (Settings.ComPort == 8)      /* ethernet the open socket */
    {
        return (OpenWinsock());
    }
#endif
    hComFile = CreateFile(COMPORT[Settings.ComPort], GENERIC_READ | GENERIC_WRITE, 0,
                            NULL, OPEN_EXISTING, 0, NULL);

    if(hComFile == INVALID_HANDLE_VALUE)
    {
        //Application->MessageBox(COMPORT[Settings.ComPort],"COM Error",MB_OK|MB_ICONWARNING);
		printf("%d COM Error", COMPORT[Settings.ComPort]);
        return 0;
    }

    GetCommState(hComFile, &dcb);
    dcb.BaudRate = BAUDRATE[Settings.BaudRate];
    dcb.ByteSize = WORDSIZE[Settings.WordSize][0];
    dcb.Parity = WORDSIZE[Settings.WordSize][1];
    if (WORDSIZE[Settings.WordSize][1] == NOPARITY)
        dcb.fParity = false;
    else
        dcb.fParity = true;
    dcb.StopBits = WORDSIZE[Settings.WordSize][2];
    dcb.fBinary = true;
    dcb.fOutxDsrFlow = true;      /* Register uses DTR for handshaking must be used */
                                  /* else slow register misses characters */
    dcb.fOutxCtsFlow = false;    /* not connected at register side */

    dcb.fDtrControl = DTR_CONTROL_ENABLE;
    dcb.fDsrSensitivity = false;
    dcb.fTXContinueOnXoff = true;
    dcb.fOutX = false;
    dcb.fInX = false;
    dcb.fErrorChar = false;
    dcb.fNull = false;
    dcb.fRtsControl = RTS_CONTROL_ENABLE;
    dcb.fAbortOnError = false;
    if (dcb.XoffChar == dcb.XonChar)
        dcb.XoffChar++;

    SetCommState(hComFile, &dcb);

    GetCommTimeouts(hComFile, &Commtimeouts);
    Commtimeouts.ReadIntervalTimeout = MAXDWORD;
    Commtimeouts.ReadTotalTimeoutMultiplier = 0;
    Commtimeouts.ReadTotalTimeoutConstant = 0;       /* set to 50 msec timeout */
    Commtimeouts.WriteTotalTimeoutMultiplier = 0;
    Commtimeouts.WriteTotalTimeoutConstant = 50;
    SetCommTimeouts(hComFile, &Commtimeouts);
    return 1;
}

__declspec(dllexport) int __stdcall ClosePort(void) 
{
#if Q_NET == 1
    if (Settings.ComPort == 8)
        CloseWinsock();
    else
#endif
    CloseHandle(hComFile);
	return 1;
}

__declspec(dllexport) int __stdcall OpenComPort(WORD comPort, WORD baudRate)
{
	SetComSettings(comPort-1, baudRate, 0, 0);	
	return OpenPort();
}

__declspec(dllexport) int __stdcall CloseComPort(void)
{
	return ClosePort();
}

__declspec(dllexport) int __stdcall OpenIPPort(BYTE ip0, BYTE ip1, BYTE ip2, BYTE ip3, WORD reg = 0)
{
	SetIPSettings(ip0, ip1, ip2, ip3, reg);
	return OpenPort();
}

__declspec(dllexport) int __stdcall CloseIPPort(void)
{
	return ClosePort();
}

//---------------------------------------------------------------------------

/* tabel used for CRC-16 calcutlation according to 8005 Poly (x16+x15+x2+1) */

WORD CRC_Table[] =
{
	0x0000, 0xCC01,	0xD801,	0x1400,	0xF001,	0x3C00,	0x2800,	0xE401,
	0xA001,	0x6C00,	0x7800,	0xB401,	0x5000,	0x9C01,	0x8801,	0x4400,
};

WORD UpdateCrc(WORD crc, BYTE b)
{
    WORD ch;

    ch = b;
	crc = CRC_Table[(ch ^ crc) & 15] ^ (crc >> 4);
	crc = CRC_Table[((ch >> 4) ^ crc) & 15] ^ (crc >> 4);
    return crc;
}

WORD CalculateCrc(WORD crc, BYTE *p, WORD len)
{
    while ( len )
    {
        crc = UpdateCrc(crc, *p);
        p++;
        len--;
    }
    return crc;
}

//---------------------------------------------------------------------------

int Send232(BYTE ch)
{
    DWORD BytesWritten;

    if (WriteFile(hComFile, &ch, 1, &BytesWritten, NULL)
            && BytesWritten == 1)
        return 1;
    ClearCommError(hComFile, &BytesWritten, NULL);//clears the device's error flag to enable
    return 0;               //additional input and output (I/O) operations
}

int RxdData(void)
{
    DWORD BytesRead;
    BYTE b;

#if Q_NET == 1
    if (Settings.ComPort == 8)        /* ethernet */
    {
        RxCount = recvfrom(Q_Socket, reinterpret_cast<char*>(RxBuffer), sizeof(RxBuffer), 0,
                (SOCKADDR*)&Q_RemoteAddr,&Q_RemoteAddrLen);
        if (RxCount == SOCKET_ERROR)
            RxCount = 0;
        else
            ShowRecord(1, reinterpret_cast<char*>(RxBuffer), RxCount);
        return RxCount;
    }
#endif
    while (ReadFile(hComFile, &b, 1, &BytesRead, NULL))
    {
        if (BytesRead != 1)
            return 0;
        if ( RxStat == 1 )      /* Previous character was DLE ? */
        {
            RxStat = 0;
            if ( b == STX || b == EOT)     /* start or abort of record  */
            {
                RxCount = 0;
                continue;
            }
            if ( b == ETX )     /* end of record ? */
            {
                RxStat = 2;     /* set next byte is BCC */
                continue;
            }
        }
        else if ( RxStat == 2 )
        {
            RxStat = 3;
            RxCrc = b;            /* first high byte */
            RxCrc *= 0x0100;
            continue;
        }
        else if ( RxStat == 3 )
        {
            RxStat = 0;
            RxCrc += b;
            if ( CalculateCrc(0xffff, RxBuffer, RxCount) == RxCrc)
            {
                ShowRecord(1, reinterpret_cast<char*>(RxBuffer), RxCount);
                return RxCount;       /* valid record */
            }
            else
                ShowRecord(2, reinterpret_cast<char*>(RxBuffer), RxCount);
            RxCount = 0;
            continue;
        }
#if COMPRESS == 1
        else if ( RxStat == 4 )
        {
            while (b > 1)
            {
                RxBuffer[RxCount] = 0; /* fill with zeroes */
                RxCount++;
                if ( RxCount > sizeof(RxBuffer)-1 )
                    RxCount = 0;
                b--;
            }
            RxStat = 0;
            continue;
        }
        else if ( RxStat == 5 )
        {
            while (b > 1)
            {
                RxBuffer[RxCount] = 0xff; /* fill with zeroes */
                RxCount++;
                if ( RxCount > sizeof(RxBuffer)-1 )
                    RxCount = 0;
                b--;
            }
            RxStat = 0;
            continue;
        }
#endif
        else if ( b == DLE )
        {
            RxStat = 1;
            continue;
        }
#if COMPRESS == 1
        else if (b == 0)    /* special compression of zeroes */
        {
            RxStat = 4;
        }
        else if (b == 0xff)    /* special compression of 0xff*/
        {
            RxStat = 5;
        }
#endif
        RxBuffer[RxCount] = b;
        RxCount++;
        if (RxCount > sizeof(RxBuffer)-1 )
            RxCount = 0;
    }
    ClearCommError(hComFile, &BytesRead, NULL);//clears the device's error flag to enable
    return 0;               //additional input and output (I/O) operations
}

int TxdData(BYTE *p, WORD length)
{
    WORD txcrc;
    WORD count;

    ShowRecord(0, reinterpret_cast<char*>(p), length);

#if Q_NET == 1
    if (Settings.ComPort == 8)        /* ethernet */
    {
        if (sendto(Q_Socket, reinterpret_cast<char*>(p), length, 0,
                (SOCKADDR*)&Q_Addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
            return 0;
        else
            return 1;
    }
#endif
    txcrc = 0xffff;
    if (Settings.Register)
    {
        txcrc = UpdateCrc(txcrc, '#');
        txcrc = UpdateCrc(txcrc, (Settings.Register / 10) + '0');
        txcrc = UpdateCrc(txcrc, (Settings.Register % 10) + '0');
    }
    txcrc = CalculateCrc(txcrc, p, length);
    Send232(DLE);
    Send232(STX);
    if (Settings.Register)
    {
        Send232('#');
        Send232((Settings.Register / 10) + '0');
        Send232((Settings.Register % 10) + '0');
    }
    while(length)
    {
        if (!Send232(*p))
            return 0;
#if COMPRESS == 1
        if(!*p )       /* special compression of zeroes */
        {
            count = 0;
            while (!*p && count < 0x00ff && length)
            {
                count++;
                p++;
                length--;
            }
            Send232(count);
        }
        else if(*p == 0xff )       /* special compression of 0xff */
        {
            count = 0;
            while (*p == 0xff && count < 0x00ff && length)
            {
                count++;
                p++;
                length--;
            }
            Send232(count);
        }
        else
#endif
        {
            if ( *p == DLE )
                Send232(DLE);
            p++;
            length--;
        }
    }
    Send232(DLE);
    Send232(ETX);
    Send232(txcrc / 0x0100);      /* send high low */
    Send232(txcrc & 0x00ff);
    return 1;
}

//---------------------------------------------------------------------------
int SendRecord(BYTE *rec, int recsize, DWORD timeout)
/*
    rec points to rec which must be transmitted
    recsize is the size of he record to be transmitted
    return 1 when transmitted OK
*/
{
    int txretry, rxcount, cmd_retry, result;
    DWORD rx_timer;//, b_count;

#if Q_NET == 1
    if (Settings.ComPort == 8)      /* ethernet */
        timeout = COM_TIMER;   /* minimal timer */
    else
#endif
    {
        /* clear receive buffer for correct answer */
        while (ReadFile(hComFile, &txretry, 1, &rx_timer, NULL) && rx_timer == 1);
    }
    txretry = COM_RETRY;
    cmd_retry = CMD_RETRY;
    rx_timer = 0;
    result = 0;
    for(;;)
    {
        if (GetTickCount() > rx_timer)
        {
            if (!txretry)
            {
                result = 5;
                ShowRecord(5, 0, 0);     /* time out */
                break;
            }
            else
            {
                if ( txretry != COM_RETRY)
                {                        /* clear buffers and errors */
#if Q_NET == 1
                    if (Settings.ComPort != 8)        /* ethernet */
#endif
                    {
                        ResetCommError();
                        Send232(DLE);
                        Send232(EOT);       /* send EOT to re-sync */
                    }
                    ShowRecord(4, 0, 0);     /* retry  */
                }
                txretry--;
                if (recsize)
                {
                    memset(RxBuffer, 0, sizeof(RxBuffer));
                    RxCount = 0;
                    TxdData(rec, recsize);
                    if (recsize == 1 && *rec == ACK)        /* sending ACK */
                        *rec = NAK; /* sen NAK next time */
                }
                rx_timer = GetTickCount() + timeout;
            }
        }
        rxcount = RxdData();
        if ( rxcount )
        {
            if (RxBuffer[0] == NAK)
                rx_timer = 0;   /* force resend */
            else if (RxBuffer[0] == EOT)
            {
                if (recsize != 1 && cmd_retry > 1)
                {
                    cmd_retry--;        /* try 5 times to be sure not out of sync */
                    txretry = COM_RETRY;
                    rx_timer = 0;
                }
                else        /* invalid command */
                {
                    result = 4;
                    ShowRecord(5, 0, 0);     /* time out */
                    break;
                }
            }
            else if (RxBuffer[0] == SYN)    /* sync then reset timer */
            {
                rx_timer = GetTickCount() + timeout;
            }
            else        /* all records are oke as answer */
      	        break;
        }
        else if (!RxCount)      /* not in the middle of record */
        {
            Sleep(5);
            //---- Application->ProcessMessages();
        }
    }
    if (!result && RxBuffer[0] != EOT)
        return rxcount;
    else
        return 0;
}

//---------------------------------------------------------------------------
int UploadData(BYTE *rec, WORD len)
{
    if (SendRecord(rec, len, TIMEOUTS[Settings.BaudRate] + COM_TIMER*2))  /* sent command */
    {
        if (RxBuffer[0] == ACK )        /* ended correctly */
            return (RxBuffer[1]);       /* return result code must be zero */
    }
    return -1;
}

//---------------------------------------------------------------------------
__declspec(dllexport) int __stdcall SendCommand(BYTE *rec, BYTE *trama)
{
    int len = 0;
    while (*rec != '\0')
    {
       len++;
       rec++;
    }
	rec -= len;

	_rxcount = -1;
	BYTE rx;
	int length = 0;
	char numchar[10];
	memset(numchar, 0, 10);

	int bError = UploadData(rec, len);	

	if(bError >= 0)
	{
		_rxcount = RxCount;
		memset(weft, 0, 1024);

		for(int i = 0; i < RxCount; i++)
		{
			rx = RxBuffer[i];

			if(i==0)
			{
				if(rx == 6)
				{
					strcat(reinterpret_cast<char*>(weft), "ACK");					
				}
				else if(rx == 21)
				{
					strcat(reinterpret_cast<char*>(weft), "NACK");
				}
			}
			else if(i == 2)
			{
                if(rx == 88)
				{
                    strcat(reinterpret_cast<char*>(weft), "X");
				}
                else if(rx == 82)
				{
                 	strcat(reinterpret_cast<char*>(weft), "R");
				}
                else if(rx == 79)
				{
					strcat(reinterpret_cast<char*>(weft), "O");
				}
                else if(rx == 83)
				{
					strcat(reinterpret_cast<char*>(weft), "S");
				}
                else if(rx == 78)
				{
					strcat(reinterpret_cast<char*>(weft), "N");
				}
                else if(rx == 67)
				{
					strcat(reinterpret_cast<char*>(weft), "C");
				}
			}
			else
			{
				itoa(rx, numchar, 10);				
	
				if(i < 18)
				{
					if(i == 16 || i == 17)
					{
						numchar[0] = rx;
						numchar[1] = '\0';
						strcat(reinterpret_cast<char*>(weft), numchar);
					}
					else
						strcat(reinterpret_cast<char*>(weft), numchar);
				}
				else
				{
					if(rx != 32)
					{
						numchar[0] = rx;
						numchar[1] = '\0';
						strcat(reinterpret_cast<char*>(weft), numchar);
					}
				}
			}

			if(i + 1 < RxCount) 
			{	
				if(i > 15 && i < 17) continue; // toma desde 16 hasta 16 
				if(i > 17 && i < 34) continue; // toma desde 18 hasta 33 
				if(i > 34 && i < 44) continue; // toma desde 35 hasta 43
				if(i > 44) continue;		   // toma desde 45
				strcat(reinterpret_cast<char*>(weft), "|");				
			}			
		}
		strcpy(reinterpret_cast<char*>(trama), reinterpret_cast<char*>(weft));
	}

    return bError;
}

__declspec(dllexport) int __stdcall ReadData(BYTE *rx)
{
	if(_rxcount < 0) return -1;
	*rx = RxBuffer[RxCount - _rxcount];
	return --_rxcount;
}

_declspec(dllexport) int _stdcall WeftLength()
{
	return RxCount;
}

//---------------------------------------------------------------------------
int DownloadData(BYTE *rec, WORD len)
{
    BYTE lastrecord[sizeof(RxBuffer)], ack_rec[4];
    int ack_len;

    if (!SendRecord(rec, len, TIMEOUTS[Settings.BaudRate] + COM_TIMER*2))  /* sent report or ack command */
        return 0;
    memset(lastrecord, 0, sizeof(lastrecord));
    for(;;)
    {
        if (RxBuffer[0] == ACK )        /* ended correctly */
            return (RxBuffer[1]);       /* return result code must be zero */
        if (memcmp(lastrecord, RxBuffer, RxCount))  /* new record */
        {
            memcpy(lastrecord, RxBuffer, RxCount);
            /* process valid record, for example store to disk */
        }
        else
        {
            ShowRecord(3, 0, 0);        /* Indicate Duplicate record and forget */
        }
        ack_rec[0] = ACK;       /* can be aborted by sending EOT instead of ACK */
        ack_len = 1;
        if (!SendRecord(ack_rec, ack_len, TIMEOUTS[Settings.BaudRate] + COM_TIMER*2))  /* sent report or ack command */
            break;
    }
    return -1;
}

/********************* bixolon *********************/

_declspec(dllexport) bool _stdcall OpenFpctrl(char* lpPortName)
{
	if(!strlen(lpPortName)) 
		return false;

	int comPort = 0;

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
	
	return OpenComPort(comPort, 6) == 1 ? true : false;
}

_declspec(dllexport) bool _stdcall CloseFpctrl()
{
	return CloseComPort() == 1 ? true : false;
}


__declspec(dllexport) int __stdcall Translate(BYTE *cmdbx, BYTE *cmdqp)
{
	//Protocol Lexer;
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
	strcpy(reinterpret_cast<char*>(cmdqp), Lexer.QPrint());
	return Lexer.QPLeng();
}


_declspec(dllexport) bool _stdcall SendCmd(int* status, int* error, char* cmd)
{
	*status = 0;
	*error = 0;
	bool retval = true;
	BYTE qprint_cmd[1024];
	BYTE trama[1024];
	memset(trama, 0, 1024);
	
	try
	{
		// envìo de comando
		//qprint_cmd = reinterpret_cast<BYTE*>(translator[cmd]);
		int len = Translate(reinterpret_cast<BYTE*>(cmd), qprint_cmd);
		*error = SendCommand(qprint_cmd, trama);
		if(*error != 0) retval = false;
		/*
		// manejo de errores
		mmid::const_iterator iter;
		iter = mapErrors.find(bError);
		*error = iter->second;
		if(*error != 0) retval = false;
		*/
		// liberar memoria
		//free(trama);
	}
	catch(...)
	{
		*error = -1;
		return false;
	}

	return retval;
}


