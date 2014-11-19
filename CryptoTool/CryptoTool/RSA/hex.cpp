#include "stdafx.h"
#include "hex.h"

/** 
 * Check to see if the input starts with "0x"; if it does, return the decoded
 * bytes of the following data (presumed to be hex coded). If not, just return
 * the contents. This routine allocates memory, so has to be free'd.
 */
int hex_decode( const unsigned char *input, unsigned char **decoded )
{  
  int i;
  int len;
    
  if ( strncmp( "0x", (const char *)input, 2 ) )
  {
    len = strlen((const char *) input ) + 1;
    *decoded =(unsigned char *) malloc( len );
    strcpy( (char *)*decoded, (const char *)input );
    len--;
  }
  else
  {
    len = ( strlen((const char*) input ) >> 1 ) - 1;
    *decoded =(unsigned char *) malloc( len );
    for ( i = 2; i < (int)strlen((const char *) input ); i += 2 )
    {
      (*decoded)[ ( ( i / 2 ) - 1 ) ] =
        ( ( ( input[ i ] <= '9' ) ? input[ i ] - '0' : 
        ( ( tolower( input[ i ] ) ) - 'a' + 10 ) ) << 4 ) |
        ( ( input[ i + 1 ] <= '9' ) ? input[ i + 1 ] - '0' : 
        ( ( tolower( input[ i + 1 ] ) ) - 'a' + 10 ) );
    }
  } 
 
  return len;
}

void show_hex( const unsigned char *array, int length )
{
  while ( length-- )
  {
    printf( "%.02x", *array++ );
  }
  printf( "\n" );
}
