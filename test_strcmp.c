#include "test_strcmp.h"
#include "lib/strcmp.h"

char s1[50];

char test_strcmp()
{
  
  if(strlen((char *)"abcd") != 4)
    return 3;

  if(strlen((char *)"")!=0)
    return 4;

  if(strcpy(s1,(char*)"abcdEFGH")!=s1)
    return 5;
  
  if(strcmp(s1,(char*)"abcdEFGH"))
    return 6;
  
  if(strcmp((char *)"zuio",(char *)"zuio"))
    return 7;;
  if(strcmp((char*)"abcd",(char*)"abcd"))
    return 8;
  
  if(strcmp((char*)"abcd",(char*)"abcD")!=1)
    return 9;
  
  if(strcmp((char*)"abcD",(char*)"abcd")!=-1)
    return 10;
  
  if(strcmp((char*)"abcd",(char*)"abcdef")!=-1)
    return 11;
  
  if(strcasecmp((char*)"aBCd",(char*)"abcd")!=0)
    return 12;
  
  if(strcasecmp((char*)"aBCd",(char*)"abcF")!=-1)
    return 13;
  
  if(strcasecmp((char*)"aBCd",(char*)"abca")!=1)
    return 14;
  
  if(strncasecmp((char*)"aBCd",(char*)"abcd",4)!=0)
    return 15;
  
  if(strncasecmp((char*)"aBCd",(char*)"abcF",4)!=-1)
    return 16;
  
  if(strncasecmp((char*)"aBCd",(char*)"abca",4)!=1)
    return 17;

  if(strncasecmp((char*)"aBCd",(char*)"abcd",3)!=0)
    return 18; 
  if(strncasecmp((char*)"aBCd",(char*)"abcF",3)!=0)
    return 19;
  if(strncasecmp((char*)"aBCd",(char*)"abca",3)!=0)
    return 20;

  if(strncmp((char*)"abcd",(char*)"abcd",4)!=0)
    return 21; 
  if(strncmp((char*)"abcd",(char*)"abcf",4)!=-1)
    return 22;
  if(strncmp((char*)"abcd",(char*)"abca",4)!=1)
    return 23;

  if(strncmp((char*)"abcd",(char*)"abcd",3)!=0)
    return 24; 
  if(strncmp((char*)"abcd",(char*)"abcf",3)!=0)
    return 25;
  if(strncmp((char*)"abcd",(char*)"abca",3)!=0)
    return 26;
  
  if(strcmp(strcat((char*)"XYZ",(char*)"xyz"),(char*)"XYZxyz")!=0)
    return 27;
  if(strcmp(strcat((char*)"XXYY",(char*)""),(char*)"XXYY")!=0)
    return 28;
  
  return 0;  
}
