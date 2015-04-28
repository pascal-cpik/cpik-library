#include "test_memcpymove.h"
#include "lib/memcpymove.h"
#include "lib/strcmp.h"

char test_memcpymove()
{
  strcpy(s1,(char*)"0123456789");
  memmove(s1,s1+1,4);
  if(strcmp(s1,(char *)"1234456789"))
    return 1;
    
  strcpy(s1,(char*)"0123456789");
  memmove(s1+1,s1,4);
  if(strcmp(s1,(char *)"0012356789"))
    return 2;

  //                0123456BCDEF
  strcpy(s1,(char*)"-----ABCDEFGHIJKLMNOP---------");
  xmemshift(s1,6,1,5,1); // offset=6,shift=+1, len=5, size=1
  if(strcmp(s1,(char *)"-----ABBCDEFHIJKLMNOP---------")!=0)
    return 3;

  //                      DDEEFFGG
  strcpy(s1,(char*)"----AABBCCDDEEFFGGHHIIJJ---------");
  xmemshift(s1,5,-2,4,2); // offset=5,shift=-2, len=4, size=2
  if(strcmp(s1,(char *)"----AADDEEFFGGFFGGHHIIJJ---------")!=0)
    return 4;
  
  return 0;
}
