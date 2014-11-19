#ifndef ALGORITHM_SHA1_H
#define ALGORITHM_SHA1_H

#include <stdlib.h>
#include <string.h>

#ifdef WIN32
#include <winsock.h>
#include <windows.h>
#else
#include <arpa/inet.h>
#endif

#include "digest.h"


#define SHA1_INPUT_BLOCK_SIZE 56
#define SHA1_BLOCK_SIZE 64

#define SHA1_RESULT_SIZE  5
#define SHA1_BYTE_SIZE SHA1_RESULT_SIZE * sizeof( int )

void sha1_block_operate(const unsigned char *block, unsigned int hash[SHA1_RESULT_SIZE]);
void sha1_finalize(unsigned char *padded_block, int length_in_bits);
void new_sha1_digest(digest_ctx *context);
int sha1_hash(unsigned char *input, int len, unsigned int hash[ SHA1_RESULT_SIZE]);

#endif 
