#include "stdafx.h"
#include "algorithm_crc32.h"


static unsigned int  CRC32[256];
static char  init = 0;



static void init_table()
{
	int   i,j;
	unsigned int    crc;
	for(i = 0;i < 256;i++)
	{
		crc = i;
		for(j = 0;j < 8;j++)
		{
			if(crc & 1)
			{
				crc = (crc >> 1) ^ 0xEDB88320;
			}
			else
			{
				crc = crc >> 1;
			}
		}
		CRC32[i] = crc;
	}
}



int crc32_hash(unsigned char *input, int len, unsigned int hash[CRC32_RESULT_SIZE])
{
  unsigned int ret = 0xFFFFFFFF;
  int i;

  if(!init)
  {
	  init_table();
	  init = 1;
  }

  for(i = 0; i < len; i++)
  {

    ret = CRC32[((ret & 0xFF) ^ input[i])] ^ (ret >> 8);

  }
  
  ret = ~ret;
  hash[0] = ret;
  
  return 0;
}

