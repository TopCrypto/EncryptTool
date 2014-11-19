#ifndef ALGORITHM_MD5_H
#define ALGORITHM_MD5_H


#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "digest.h"

#define MD5_RESULT_SIZE  4
int md5_hash(const unsigned char *input, int len, unsigned int hash[MD5_RESULT_SIZE]);

#endif 