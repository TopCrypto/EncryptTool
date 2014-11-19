#ifndef ALGORITHM_CRC32_H
#define ALGORITHM_CRC32_H

#define CRC32_RESULT_SIZE 1

#define POLY 0x04C11DB7L   //CRC32生成多项式

int crc32_hash(unsigned char *input, int len, unsigned int hash[CRC32_RESULT_SIZE]);

#endif 

