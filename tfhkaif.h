#ifndef _DLL_TFHKAIF_H_
#define _DLL_TFHKAIF_H_
#include <iostream>

void LoadDictionary();
void LoadSeniat();

/* QPrint */

__declspec(dllexport) int __stdcall GetVer(char* ver);

__declspec(dllexport) int __stdcall HelloWorld(char* name, char* resp);

__declspec(dllexport) int __stdcall SetComSettings(WORD comPort, WORD baudRate, WORD wordSize, WORD reg);

__declspec(dllexport) int __stdcall SetIPSettings(BYTE ip0, BYTE ip1, BYTE ip2, BYTE ip3, WORD reg = 0);

__declspec(dllexport) int __stdcall GetComSettings(int index);

__declspec(dllexport) int __stdcall GetIPSettings(int index);

__declspec(dllexport) int __stdcall OpenPort(void);

__declspec(dllexport) int __stdcall ClosePort(void);

__declspec(dllexport) int __stdcall OpenComPort(WORD comPort, WORD baudRate);

__declspec(dllexport) int __stdcall CloseComPort(void);

__declspec(dllexport) int __stdcall OpenIPPort(BYTE ip0, BYTE ip1, BYTE ip2, BYTE ip3, WORD reg = 0);

__declspec(dllexport) int __stdcall CloseIPPort(void);

__declspec(dllexport) int __stdcall SendCommand(BYTE *rec, BYTE *weft);

__declspec(dllexport) int __stdcall ReadData(BYTE *rx);

__declspec(dllexport) int _stdcall WeftLength();

/* Bixolon */

_declspec(dllexport) bool _stdcall OpenFpctrl(char* lpPortName);

_declspec(dllexport) bool _stdcall CloseFpctrl();

_declspec(dllexport) bool _stdcall SendCmd(int* status, int* error, char* cmd);

_declspec(dllexport) bool _stdcall UploadStatusCmd(int* status, int* error, char* cmd, char* file);

/* Bixolon -> Tramas */

__declspec(dllexport) int __stdcall Translate(BYTE *cmdbx, BYTE *cmdqp);



#endif