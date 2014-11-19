#include "stdafx.h"
#include "algorithm_sha1.h"




static const int k[] = {
    0x5a827999,    // 0 <= t <=19
    0x6ed9eba1,    // 20 <= t <=39
    0x8f1bbcdc,    // 40 <=t <=59
    0xca62c1d6     // 60 <=t <=79
};

// f t = 0 -19
unsigned int ch(unsigned int x, unsigned y, unsigned int z)
{
  return (x & y) | (~x & z);
}


// f t = 20-39 & t = 60 - 79
unsigned int parity(unsigned int x, unsigned int y, unsigned int z)
{
  return x ^ y ^ z;
}

// f t = 40 - 59
unsigned int maj(unsigned int x, unsigned int y, unsigned int z)
{
	return ( x & y ) | ( x & z ) | ( y & z );
}

void sha1_block_operate(const unsigned char *block, unsigned int hash[SHA1_RESULT_SIZE])
{
   unsigned int W[ 80 ];
   unsigned int t = 0;
   unsigned int a, b, c, d, e, T;

   // First 16 blocks of W are the original 16 blocks of the input 
   for( t = 0; t < 80; t++ )
   {
      if( t < 16 )
	  {
		  W[ t ] = ( block[ ( t * 4 ) ] << 24)  | ( block[ ( t * 4 ) + 1 ] << 16 ) | ( block[ t * 4 + 2] << 8 ) | ( block[ ( t * 4 ) + 3 ] );
	  }
	  else
	  {
		  W[t] = W[ t - 3 ] ^ W[ t - 8 ] ^ W[ t - 14 ] ^ W[ t - 16 ];
		  W[t] = ( W[t] << 1 ) | ( ( W[ t ] & 0x80000000 ) >> 31 );

	  }

   }
  

   hash[ 0 ] = ntohl( hash[ 0 ] );
   hash[ 1 ] = ntohl( hash[ 1 ] );
   hash[ 2 ] = ntohl( hash[ 2 ] );
   hash[ 3 ] = ntohl( hash[ 3 ] );
   hash[ 4 ] = ntohl( hash[ 4 ] );

   a = hash[ 0 ];
   b = hash[ 1 ];
   c = hash[ 2 ];
   d = hash[ 3 ];
   e = hash[ 4 ];

   for( t = 0; t < 80; t++)
   {
     T = ( ( a << 5) | ( a >> 27 ) ) + e +W[ t ] + k [ t / 20 ];

     if( t <= 19 )
	 {
		T += ch( b, c, d );
	 }else if( t <= 39 )
	 {
		 T += parity( b, c, d );
	 }else if( t <= 59 )
	 {
		 T += maj( b, c, d );
	 }
	 else
	 {
		 T += parity( b, c, d );
	 }
     
	 e = d;
	 d = c;
	 c = ( ( b << 30) | ( b >> 2) );
	 b = a;
	 a = T;
   }

   hash[ 0 ] += a;
   hash[ 1 ] += b;
   hash[ 2 ] += c;
   hash[ 3 ] += d;
   hash[ 4 ] += e;

   hash[ 0 ] = htonl( hash[ 0 ] );
   hash[ 1 ] = htonl( hash[ 1 ] );
   hash[ 2 ] = htonl( hash[ 2 ] );
   hash[ 3 ] = htonl( hash[ 3 ] );
   hash[ 4 ] = htonl( hash[ 4 ] );
}

#define SHA1_INPUT_BLOCK_SIZE 56
#define SHA1_BLOCK_SIZE 64

unsigned int sha1_initial_hash[ ] = { 
	0x01234567,
	0x89abcdef,
	0xfedcba98,
	0x76543210,
	0xf0e1d2c3
};	


int sha1_hash(unsigned char *input, int len, unsigned int hash[ SHA1_RESULT_SIZE])
{
	unsigned char padded_block[ SHA1_BLOCK_SIZE ];
	int length_in_bits = len * 8;

	hash[ 0 ] = sha1_initial_hash[ 0 ];
	hash[ 1 ] = sha1_initial_hash[ 1 ];
	hash[ 2 ] = sha1_initial_hash[ 2 ];
	hash[ 3 ] = sha1_initial_hash[ 3 ];
	hash[ 4 ] = sha1_initial_hash[ 4 ];

    while( len >= SHA1_INPUT_BLOCK_SIZE )
	{
       if( len < SHA1_BLOCK_SIZE )
	   {
		   memset(padded_block, 0, sizeof(padded_block) );
		   memcpy(padded_block, input, len);
		   padded_block[ len ] = 0x80;
		   sha1_block_operate(padded_block, hash);

		   input += len;
		   len = -1;
	   }
	   else
	   {
           sha1_block_operate(input, hash);

		   input += SHA1_BLOCK_SIZE;
		   len -= SHA1_BLOCK_SIZE;

	   }
	}

    memset(padded_block, 0, sizeof(padded_block));
	if(len >= 0)
	{
		memcpy(padded_block, input, len);
		padded_block[ len ] = 0x80;
	}

	padded_block[ SHA1_BLOCK_SIZE - 4 ] = ( length_in_bits & 0xFF000000 ) >> 24;
	padded_block[ SHA1_BLOCK_SIZE - 3 ] = ( length_in_bits & 0x00FF0000 ) >> 16;
	padded_block[ SHA1_BLOCK_SIZE - 2 ] = ( length_in_bits & 0x0000FF00 ) >> 8;
	padded_block[ SHA1_BLOCK_SIZE - 1 ] = ( length_in_bits & 0x000000FF );

    sha1_block_operate(padded_block, hash);

	return 0;
}


void sha1_finalize( unsigned char *padded_block, int length_in_bits )
{
   padded_block[ SHA1_BLOCK_SIZE - 4 ] = ( length_in_bits & 0xFF000000 ) >> 24;
   padded_block[ SHA1_BLOCK_SIZE - 3 ] = ( length_in_bits & 0x00FF0000 ) >> 16;
   padded_block[ SHA1_BLOCK_SIZE - 2 ] = ( length_in_bits & 0x0000FF00 ) >> 8;
   padded_block[ SHA1_BLOCK_SIZE - 1 ] = ( length_in_bits & 0x000000FF );
}

void new_sha1_digest(digest_ctx *context)
{
  context->hash_len = 5;
  context->input_len = 0;
  context->block_len = 0;
  context->hash = (unsigned int *)malloc(context->hash_len * sizeof(unsigned int));
  memset(context->block, '\0', DIGEST_BLOCK_SIZE);
  context->block_operate = sha1_block_operate;
  context->block_finalize = sha1_finalize;
}

