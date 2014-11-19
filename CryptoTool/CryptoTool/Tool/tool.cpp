#include "stdafx.h"
#include "tool.h"
unsigned long HexCharsToStdChars(const unsigned char *pHexChar, unsigned char *pStdChar, unsigned long StdCharLen)
{
	unsigned long count = 0;
	unsigned char *pCpyHexChar = 0;
	unsigned int i = 0, iH = 0, iL = 0;
	
	if(!StdCharLen) return 0;
	
	pCpyHexChar = (unsigned char *)malloc(StdCharLen * 2);
	memcpy(pCpyHexChar, pHexChar, StdCharLen * 2);
	for(i=0; i<(StdCharLen*2); i++)
	{
		if((pCpyHexChar[i] >= 'a') && (pCpyHexChar[i] <= 'f'))
		{
			pCpyHexChar[i] -= ('a' - 'A');
		}
		if(
			((pCpyHexChar[i] < '0') || (pCpyHexChar[i] > 'F')) ||
			((pCpyHexChar[i] > '9') && (pCpyHexChar[i] < 'A'))
			)
		{
			free(pCpyHexChar);
			return count;
		}
	}
	
	for(i=0; i<StdCharLen; ++i)
	{
		if((pCpyHexChar[i*2] >= '0') && (pCpyHexChar[i*2] <= '9'))
		{
			iH = pCpyHexChar[i*2] - '0';
		}
		else if((pCpyHexChar[i*2] >= 'A') && (pCpyHexChar[i*2] <= 'F'))
		{
			iH = pCpyHexChar[i*2] - 'A' + 10;
		}
		if((pCpyHexChar[i*2+1] >= '0') && (pCpyHexChar[i*2+1] <= '9'))
		{
			iL = pCpyHexChar[i*2+1] - '0';
		}
		else if((pCpyHexChar[i*2+1] >= 'A') && (pCpyHexChar[i*2+1] <= 'F'))
		{
			iL = pCpyHexChar[i*2+1] - 'A' + 10;
		}
		pStdChar[i] = iH * 16 + iL;
		count += 1;
	}
	
	free(pCpyHexChar);
	
	return count;
}

unsigned long StdCharsToHexChars(const unsigned char *pStdChar, unsigned char *pHexChar, unsigned long StdCharLen)
{
	unsigned long count = 0;
	unsigned char *pCpyHexChar = 0;
	unsigned long i = 0;
	
	if(!StdCharLen) return 0;
	
	pCpyHexChar = (unsigned char *)malloc(StdCharLen * 2 + 1);
	for(i=0; i<StdCharLen; i++)
	{
		count += sprintf((char *)(pCpyHexChar + i * 2), "%.2X", pStdChar[i]);
	}
	memcpy(pHexChar, pCpyHexChar, count);
	free(pCpyHexChar);
	i=count;
	return count;
}



#define LOG_FILE_PATH	"c:\\testLOG.TXT"
void DEBUG_Printf_fun(char *format, ...)
{
	va_list ap;
	int n;
	FILE * fp;

	fp = fopen(LOG_FILE_PATH, "ab+");
	if (fp == NULL)
	{
		return;
	}
	va_start(ap, format);
	n = vfprintf(fp, format, ap);
	fclose(fp);
	va_end(ap);
}

void PrintSend(BYTE bCLA, BYTE bINS, BYTE bP1, BYTE bP2, BYTE bLc, BYTE *pData)
{
	BYTE pTemp[1024] = {0};
	DWORD dwSLen = 0;
	pTemp[0] = bCLA;
	pTemp[1] = bINS;
	pTemp[2] = bP1;
	pTemp[3] = bP2;
	pTemp[4] = bLc;
	memcpy(pTemp + 5, pData, bLc);
	dwSLen = 5 + bLc;

	StdCharsToHexChars(pTemp, pTemp, dwSLen);
	pTemp[dwSLen*2] = 0x00;
	DEBUG_Printf_fun("CMD[%d]:%s\r\n", dwSLen, pTemp);
	return;
}
void PrintSend(BYTE *pData, DWORD dwSLen)
{
	BYTE pTemp[1024] = {0};

	StdCharsToHexChars(pData, pTemp, dwSLen);
	pTemp[dwSLen*2] = 0x00;
	DEBUG_Printf_fun("CMD[%d]:%s\r\n", dwSLen, pTemp);
	return;
}

void PrintRecv(BYTE * pRecv, DWORD dwRLen, BYTE bSW1, BYTE bSW2)
{
	BYTE pTemp[1024] = {0};
	memcpy(pTemp, pRecv, dwRLen);
	pTemp[dwRLen + 0] = bSW1;
	pTemp[dwRLen + 1] = bSW2;
	dwRLen += 2;

	StdCharsToHexChars(pTemp, pTemp, dwRLen);
	pTemp[dwRLen*2] = 0x00;
	DEBUG_Printf_fun("Resp[%d]:%s\r\n", dwRLen - 2, pTemp);
	return;
}


void PrintRecv(BYTE *pData, DWORD dwRLen)
{
	BYTE pTemp[1024] = {0};

	StdCharsToHexChars(pData, pTemp, dwRLen);
	pTemp[dwRLen*2] = 0x00;
	DEBUG_Printf_fun("Resp[%d]:%s\r\n", dwRLen - 2, pTemp);
	return;
}