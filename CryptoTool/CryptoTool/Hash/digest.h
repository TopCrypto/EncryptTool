#ifndef DIGEST_H_
#define DIGEST_H_

#define DIGEST_BLOCK_SIZE 64
#define INPUT_BLOCK_SIZE 56

typedef struct  
{
	unsigned int *hash;
	int hash_len;
	unsigned int input_len;

	void (*block_operate)(const unsigned char *input, unsigned int hash[]);
	void (*block_finalize)(unsigned char *block, int length);

	// Temporary storage
	unsigned char block[ DIGEST_BLOCK_SIZE ];
	int block_len;
}digest_ctx;

#endif 