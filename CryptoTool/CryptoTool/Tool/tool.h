#ifndef _TOOL_H_
#define _TOOL_H_

unsigned long HexCharsToStdChars(const unsigned char *pHexChar, unsigned char *pStdChar, unsigned long StdCharLen);
unsigned long StdCharsToHexChars(const unsigned char *pStdChar, unsigned char *pHexChar, unsigned long StdCharLen);

void PrintSend(BYTE bCLA, BYTE bINS, BYTE bP1, BYTE bP2, BYTE bLc, BYTE *pData);
void PrintRecv(BYTE * pRecv, DWORD dwRLen, BYTE bSW1, BYTE bSW2);

void PrintSend(BYTE *pData, DWORD dwSLen);
void PrintRecv(BYTE *pData, DWORD dwRLen);

#endif
