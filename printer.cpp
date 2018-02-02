
#include "printer.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <map>


namespace Quorion {


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

/* tabel used for CRC-16 calcutlation according to 8005 Poly (x16+x15+x2+1) */

WORD CRC_Table[] =
{
	0x0000, 0xCC01,	0xD801,	0x1400,	0xF001,	0x3C00,	0x2800,	0xE401,
	0xA001,	0x6C00,	0x7800,	0xB401,	0x5000,	0x9C01,	0x8801,	0x4400,
};

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

//int	banderita = 0;
//char Campo17[1024];

#if Q_NET == 1

SOCKET Q_Socket;
SOCKADDR_IN Q_Addr;
SOCKADDR_IN Q_RemoteAddr;
int Q_RemoteAddrLen;

#endif

	Printer::Printer() 
	{
		//qp_error = 567;
		//printf("Printer Init Error: %d\n",qp_error);
	}

	Printer::~Printer() {}

	int Printer::fncGetQError()
	{
		return qp_error;
	}

	int Printer::fncGetBStatus()
	{
		return bx_status;
	}

	void Printer::fncAnalyzeStatus(int error, char* weft)
	{
		qp_error = error;

		char *cmd = (char *)malloc(1024 * sizeof(char));
		memset(cmd,0,1024);
		char *_weft = (char *)malloc(1024 * sizeof(char));
		memset(_weft,0,1024);
		char *buffer = (char *)malloc(1024 * sizeof(char));
		memset(buffer,0,1024);
		char *_buffer = (char *)malloc(1024 * sizeof(char));
		memset(_buffer,0,1024);
		char * pch;
		char * Campo2 = (char *)malloc(1024 * sizeof(char));
		memset(Campo2,0,1024);
		//char * Campo17 = (char *)malloc(1024 * sizeof(char));

		int _error = 0;
		int cont = 0;
		int status1 = 0;
		int status2 = 0;
		int status3 = 0;
		strcpy(_weft, weft);
		
		// Si se envía "F0;1" despues de hacer una configuración, la QPrint enviará solo
		// 15 campos de respuesta. La solución que se consideró fue enviar dos veces la trama
		// de "F0;3" para obtener todos los valores del status.
		if (strcmp(_weft, "conf") == 0) 
		{
			strcpy(cmd, "F0;1");
			fncSendCommand(reinterpret_cast<BYTE*>(&cmd[0]), reinterpret_cast<BYTE*>(_buffer));
		}

		if (banderita != 1)
		{
			memset(Campo17,0,1024);
			strcpy(cmd, "F0;1");
			try
			{
				fncSendCommand(reinterpret_cast<BYTE*>(&cmd[0]), reinterpret_cast<BYTE*>(_buffer));
				printf("NO_ERROR cmd %s buffer %s\n", cmd, _buffer);
			}
			catch(...)
			{
				printf("ERROR cmd %s buffer %s\n", cmd, _buffer);
			}

			pch = strtok (_buffer,"|");
			while (pch != NULL)
			{
				if(cont == 17) {strcpy(Campo17, pch); printf("Campo17 %s\n", Campo17); break;}
				++cont;
				pch = strtok (NULL, "|");
			}
			banderita = 1;
		}

		if (strcmp(Campo17, "") == 0) status1 = 1;
		else status1 = 2;

		cont = 0;
		if (strcmp(_weft, "conf") != 0)
		{								
			pch = strtok (_weft,"|");
			while (pch != NULL)
			{
				if(cont == 2) {strcpy(Campo2, pch); break;}
				++cont;
				pch = strtok (NULL, "|");
			}
			if (strcmp(Campo2, "R") == 0) status2 = 1;		//En Espera
			else if (strcmp(Campo2, "O") == 0) status2 = 2;	//Documento Fiscal
			else if (strcmp(Campo2, "N") == 0) status2 = 3;	//Documento No Fiscal
			else status2 = 0;
		} else status2 = 1;

		_error = error;

		if (error == 129) status3 = 1;
		if (error == 174) status3 = 2;
		else status3 = 0;

		if (status1 == 1 && status2 == 1 && status3 == 0) bx_status = 1;		//Modo Prueba, Espera
		else if (status1 == 1 && status2 == 2 && status3 == 0) bx_status = 2;	//Modo Prueba, Doc. Fiscales
		else if (status1 == 1 && status2 == 3 && status3 == 0) bx_status = 3;	//Modo Prueba, DNF
		else if (status1 == 2 && status2 == 1 && status3 == 0) bx_status = 4;	//Modo Fiscal, Espera
		else if (status1 == 2 && status2 == 2 && status3 == 0) bx_status = 5;	//Modo Fiscal, Doc. Fiscales
		else if (status1 == 2 && status2 == 3 && status3 == 0) bx_status = 6;	//Modo Fiscal, DNF
		else if (status1 == 2 && status2 == 1 && status3 == 2) bx_status = 7;	//Modo Fiscal, Cercana Carga MF, Espera
		else if (status1 == 2 && status2 == 2 && status3 == 2) bx_status = 8;	//Modo Fiscal, Cercana Carga MF, Doc. Fiscales
		else if (status1 == 2 && status2 == 3 && status3 == 2) bx_status = 9;	//Modo Fiscal, Cercana Carga MF, DNF
		else if (status1 == 2 && status2 == 1 && status3 == 1) bx_status = 10;	//Modo Fiscal, Carga Completa MF, Espera
		else if (status1 == 2 && status2 == 2 && status3 == 1) bx_status = 11;	//Modo Fiscal, Carga Completa MF, Doc. Fiscales
		else if (status1 == 2 && status2 == 3 && status3 == 1) bx_status = 12;	//Modo Fiscal, Carga Completa MF, DNF
		else bx_status = 0;														//Status Desconocido
	}

	int Printer::fncGetVer(char* ver)
	{	
		assert(ver);
		strcpy(ver, Version);
		return 1;
	}

	int Printer::fncHelloWorld(char* name, char* resp)
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
		return i;
	}

	int Printer::fncSetComSettings(WORD comPort, WORD baudRate, WORD wordSize, WORD reg)
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

	int Printer::fncSetIPSettings(BYTE ip0, BYTE ip1, BYTE ip2, BYTE ip3, WORD reg)
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

	int Printer::fncGetComSettings(int index)
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

	int Printer::fncGetIPSettings(int index)
	{
		if(index >= 0 && index <= 3)
			return Settings.IP[index];
		else if(index == 4)
			return Settings.Register;
		else return -1;
	}

#if Q_NET == 1

	int Printer::fncSetIPaddress(void)
	{
		char tmp_addr[20];
		BYTE mcno;

		mcno = Settings.IP[3];
		if (Settings.Register > 1)      // register is BASE + (register-1) 
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

	int Printer::fncOpenWinsock(void)
	{
		//std::string addr;
		WSADATA wsa;
		int RecvTimeout = 2000;

		if (!fncSetIPaddress())        // no valid IP address 
			return 0;
		if (WSAStartup(MAKEWORD(2,0), &wsa))
		{
			//Application->MessageBox(COMPORT[Settings.ComPort], "Error Opening",MB_OK|MB_ICONWARNING);
			printf("%s Error Opening", COMPORT[Settings.ComPort]);
			return 0;				// error opening 
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

	void Printer::fncCloseWinsock(void)
	{
	  closesocket(Q_Socket);
	  WSACleanup();
	}

#endif

	void Printer::fncResetCommError(void)
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

	int Printer::fncOpenPort(void)
	{
		COMMTIMEOUTS Commtimeouts;
		DCB dcb;

	#if Q_NET == 1
		if (Settings.ComPort == 8)      /* ethernet the open socket */
		{
			return (fncOpenWinsock());
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

	int Printer::fncClosePort(void) 
	{
	#if Q_NET == 1
		if (Settings.ComPort == 8)
			fncCloseWinsock();
		else
	#endif
		CloseHandle(hComFile);
		return 1;
	}

	int Printer::fncOpenComPort(WORD comPort, WORD baudRate)
	{
		fncSetComSettings(comPort-1, baudRate, 0, 0);	
		return fncOpenPort();
	}

	int Printer::fncCloseComPort(void)
	{
		return fncClosePort();
	}

	int Printer::fncOpenIPPort(BYTE ip0, BYTE ip1, BYTE ip2, BYTE ip3, WORD reg)
	{
		fncSetIPSettings(ip0, ip1, ip2, ip3, reg);
		return fncOpenPort();
	}

	int Printer::fncCloseIPPort(void)
	{
		return fncClosePort();
	}

	WORD Printer::fncUpdateCrc(WORD crc, BYTE b)
	{
		WORD ch;

		ch = b;
		crc = CRC_Table[(ch ^ crc) & 15] ^ (crc >> 4);
		crc = CRC_Table[((ch >> 4) ^ crc) & 15] ^ (crc >> 4);
		return crc;
	}

	WORD Printer::fncCalculateCrc(WORD crc, BYTE *p, WORD len)
	{
		while ( len )
		{
			crc = fncUpdateCrc(crc, *p);
			p++;
			len--;
		}
		return crc;
	}

	int Printer::fncSend232(BYTE ch)
	{
		DWORD BytesWritten;

		if (WriteFile(hComFile, &ch, 1, &BytesWritten, NULL)
				&& BytesWritten == 1)
			return 1;
		ClearCommError(hComFile, &BytesWritten, NULL);//clears the device's error flag to enable
		return 0;               //additional input and output (I/O) operations
	}

	int Printer::fncRxdData(void)
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
				fncShowRecord(1, reinterpret_cast<char*>(RxBuffer), RxCount);
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
				if ( fncCalculateCrc(0xffff, RxBuffer, RxCount) == RxCrc)
				{
					fncShowRecord(1, reinterpret_cast<char*>(RxBuffer), RxCount);
					return RxCount;       /* valid record */
				}
				else
					fncShowRecord(2, reinterpret_cast<char*>(RxBuffer), RxCount);
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

	int Printer::fncTxdData(BYTE *p, WORD length)
	{
		WORD txcrc;
		WORD count;

		fncShowRecord(0, reinterpret_cast<char*>(p), length);

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
			txcrc = fncUpdateCrc(txcrc, '#');
			txcrc = fncUpdateCrc(txcrc, (Settings.Register / 10) + '0');
			txcrc = fncUpdateCrc(txcrc, (Settings.Register % 10) + '0');
		}
		txcrc = fncCalculateCrc(txcrc, p, length);
		fncSend232(DLE);
		fncSend232(STX);
		if (Settings.Register)
		{
			fncSend232('#');
			fncSend232((Settings.Register / 10) + '0');
			fncSend232((Settings.Register % 10) + '0');
		}
		while(length)
		{
			if (!fncSend232(*p))
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
				fncSend232(count);
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
				fncSend232(count);
			}
			else
	#endif
			{
				if ( *p == DLE )
					fncSend232(DLE);
				p++;
				length--;
			}
		}
		fncSend232(DLE);
		fncSend232(ETX);
		fncSend232(txcrc / 0x0100);      /* send high low */
		fncSend232(txcrc & 0x00ff);
		return 1;
	}

	//---------------------------------------------------------------------------
	int Printer::fncSendRecord(BYTE *rec, int recsize, DWORD timeout)
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
					fncShowRecord(5, 0, 0);     /* time out */
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
							fncResetCommError();
							fncSend232(DLE);
							fncSend232(EOT);       /* send EOT to re-sync */
						}
						fncShowRecord(4, 0, 0);     /* retry  */
					}
					txretry--;
					if (recsize)
					{
						memset(RxBuffer, 0, sizeof(RxBuffer));
						RxCount = 0;
						fncTxdData(rec, recsize);
						if (recsize == 1 && *rec == ACK)        /* sending ACK */
							*rec = NAK; /* sen NAK next time */
					}
					rx_timer = GetTickCount() + timeout;
				}
			}
			rxcount = fncRxdData();
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
						fncShowRecord(5, 0, 0);     /* time out */
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
	int Printer::fncUploadData(BYTE *rec, WORD len)
	{
		if (fncSendRecord(rec, len, TIMEOUTS[Settings.BaudRate] + COM_TIMER*2))  /* sent command */
		{
			if (RxBuffer[0] == ACK)        /* ended correctly */
				return (RxBuffer[1] == 163 ? 0 : RxBuffer[1]);       /* return result code must be zero */
			else 
				return -2;
		}
		return -1;
	}

	//---------------------------------------------------------------------------
	int Printer::fncSendCommand(BYTE *rec, BYTE *trama)
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

		int bError = fncUploadData(rec, len);	

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

	int Printer::fncReadData(BYTE *rx)
	{
		if(_rxcount < 0) return -1;
		*rx = RxBuffer[RxCount - _rxcount];
		return --_rxcount;
	}

	int Printer::fncWeftLength()
	{
		return RxCount;
	}

	//---------------------------------------------------------------------------
	int Printer::fncDownloadData(BYTE *rec, WORD len)
	{
		BYTE lastrecord[sizeof(RxBuffer)], ack_rec[4];
		int ack_len;

		if (!fncSendRecord(rec, len, TIMEOUTS[Settings.BaudRate] + COM_TIMER*2))  /* sent report or ack command */
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
				fncShowRecord(3, 0, 0);        /* Indicate Duplicate record and forget */
			}
			ack_rec[0] = ACK;       /* can be aborted by sending EOT instead of ACK */
			ack_len = 1;
			if (!fncSendRecord(ack_rec, ack_len, TIMEOUTS[Settings.BaudRate] + COM_TIMER*2))  /* sent report or ack command */
				break;
		}
		return -1;
	}

	void Printer::fncShowRecord(int type, char *rec, int len)
	{	
	}

//---------------------------------------------------------------------------
	int Printer::fncRegistrarLog(int error, char * trama, char * traduccion)
	{
/*		FILE *Funcion = fopen("QPrint\\QP_SendCmd.txt","a+");
		fprintf(Funcion, "%s\n", traduccion);
		fclose(Funcion);
*/
		char * cmdQP = (char *)malloc(1024 * sizeof(char));
		memset(cmdQP, 0, 1024);
		char * bufferQP = (char *)malloc(1024 * sizeof(char));
		memset(bufferQP, 0, 1024);
		char * pch;
		char * fechaQP = (char *)malloc(20 * sizeof(char));
		memset(fechaQP, 0, 20);
		char * horaQP = (char *)malloc(20 * sizeof(char));
		memset(horaQP, 0, 20);
		int cont = 0;
		int _error = 0;
		_error = error;

/*		if (_error != 0)
		{
		// Determinar Fecha y Hora
			strcpy(cmdQP, "F0;1");
			fncSendCommand(reinterpret_cast<BYTE*>(&cmdQP[0]), reinterpret_cast<BYTE*>(bufferQP));

			pch = strtok (bufferQP,"|");
			while (pch != NULL)
				{
					if (cont == 18) strcpy(fechaQP, pch);
					if (cont == 19) strcpy(horaQP, pch);
					++cont;
					pch = strtok (NULL, "|");
				}

			FILE *destino = fopen("Qprint\\QPrint Errores Generado.txt","a+");
			fprintf(destino, "Error QP: %i, Fecha: %s, Hora: %s, Ubicación: %s\n", _error, fechaQP, horaQP, trama);
			fclose(destino);

		}
*/
		return 0;
	}

}	