#ifndef _QUORION_H_
#define _QUORION_H_

#define Q_NET	1       /* set to 1 to include ethernet */

#if Q_NET == 1
#pragma comment(lib, "wsock32.lib")
#include <winsock2.h>

#define UDP_COMP	2030            /* IP port for computer */

#endif

#include "stdafx.h"

namespace Quorion {

class Printer
{
public:
    Printer();

    virtual ~Printer();

	int fncGetQError();

	int fncGetBStatus();

	void fncAnalyzeStatus(int error, char* weft);

	int fncGetVer(char* ver);

	int fncHelloWorld(char* name, char* resp);

	int fncSetComSettings(WORD comPort, WORD baudRate, WORD wordSize, WORD reg);

	int fncSetIPSettings(BYTE ip0, BYTE ip1, BYTE ip2, BYTE ip3, WORD reg = 0);

	int fncGetComSettings(int index);

	int fncGetIPSettings(int index);

#if Q_NET == 1
	
	int fncSetIPaddress(void);

	int fncOpenWinsock(void);

	void fncCloseWinsock(void);

#endif

	void fncShowRecord(int type, char *rec, int len);

	void fncResetCommError(void);

	int fncOpenPort(void);

	int fncClosePort(void);

	int fncOpenComPort(WORD comPort, WORD baudRate);

	int fncCloseComPort(void);

	int fncOpenIPPort(BYTE ip0, BYTE ip1, BYTE ip2, BYTE ip3, WORD reg = 0);

	int fncCloseIPPort(void);

	WORD fncUpdateCrc(WORD crc, BYTE b);

	WORD fncCalculateCrc(WORD crc, BYTE *p, WORD len);

	int fncSend232(BYTE ch);

	int fncRxdData(void);

	int fncTxdData(BYTE *p, WORD length);

	int fncSendRecord(BYTE *rec, int recsize, DWORD timeout);

	int fncUploadData(BYTE *rec, WORD len);

	int fncSendCommand(BYTE *rec, BYTE *trama);

	int fncReadData(BYTE *rx);

	int fncWeftLength();

	int fncDownloadData(BYTE *rec, WORD len);

	int fncRegistrarLog(int error, char * trama, char * traduccion);

	int	banderita ;
	
	char Campo17[1024];

/*
	bool fncOpenFpctrl(char* lpPortName);

	bool fncCloseFpctrl();

	bool fncCheckFprinter();

	bool fncReadFpStatus(LPINT status, LPINT error);

	int fncSendNCmd(LPINT status, LPINT error, LPCSTR buffer);

	int fncSendFileCmd(LPINT status, LPINT error, LPCSTR file);

	bool fncUploadReportCmd(LPINT status, LPINT error, LPCSTR cmd, LPCSTR file);
*/
private:
	int qp_error;
	int bx_status;
};

} // namespace Quorion

#endif // _QUORION_H_