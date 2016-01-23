#include "test_memcpymove.h"
#include "lib/memcpymove.h"
#include "lib/strcmp.h"

char s2[50];

char test_memcpymove()
{
  strcpy(s2,(char*)"0123456789");
  memmove(s2,s2+1,4);
  if(strcmp(s2,(char *)"1234456789"))
    return 1;
    
  strcpy(s2,(char*)"0123456789");
  memmove(s2+1,s2,4);
  if(strcmp(s2,(char *)"0012356789"))
    return 2;

  //                0123456BCDEF
  strcpy(s2,(char*)"-----ABCDEFGHIJKLMNOP---------");
  xmemshift(s2,6,1,5,1); // offset=6,shift=+1, len=5, size=1
  if(strcmp(s2,(char *)"-----ABBCDEFHIJKLMNOP---------")!=0)
    return 3;

  //                      DDEEFFGG
  strcpy(s2,(char*)"----AABBCCDDEEFFGGHHIIJJ---------");
  xmemshift(s2,5,-2,4,2); // offset=5,shift=-2, len=4, size=2
  if(strcmp(s2,(char *)"----AADDEEFFGGFFGGHHIIJJ---------")!=0)
    return 4;
  
  return 0;
}
