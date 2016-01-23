#include "test_strcmp.h"
#include "lib/strcmp.h"

char s1[50];


ROM_ENTRY(rom_string)
{
  ROM_TXT("string\0");
}

ROMF_TXT(rxs_string, "axs\0")

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
  if(strcmp((char*)"abcdef",(char*)"abcd")!=1)
    return 12;
  
  if(strcasecmp((char*)"aBCd",(char*)"abcd")!=0)
    return 13;

  if(strcasecmp((char*)"aBCd",(char*)"abcde")!=-1)
    return 14;
  if(strcasecmp((char*)"aBCde",(char*)"abcd")!=1)
    return 15;

  
  if(strcasecmp((char*)"aBCd",(char*)"abcF")!=-1)
    return 16;
  
  if(strcasecmp((char*)"aBCd",(char*)"abca")!=1)
    return 17;
  
  if(strncasecmp((char*)"aBCd",(char*)"abcd",4)!=0)
    return 18;
  
  if(strncasecmp((char*)"aBCd",(char*)"abcF",4)!=-1)
    return 19;
  
  if(strncasecmp((char*)"aBCd",(char*)"abca",4)!=1)
    return 20;

  if(strncasecmp((char*)"aBCd",(char*)"abcda",5)!=-1)
    return 21;
  if(strncasecmp((char*)"aBCde",(char*)"abcd",5)!=1)
    return 22;

  
  if(strncasecmp((char*)"aBCd",(char*)"abcd",3)!=0)
    return 23;
  if(strncasecmp((char*)"aBCd",(char*)"abcF",3)!=0)
    return 24;
  if(strncasecmp((char*)"aBCd",(char*)"abca",3)!=0)
    return 25;

  if(strncmp((char*)"abcd",(char*)"abcd",4)!=0)
    return 26;
  if(strncmp((char*)"abcd",(char*)"abcf",4)!=-1)
    return 27;
  if(strncmp((char*)"abcd",(char*)"abca",4)!=1)
    return 28;

  if(strncmp((char*)"abcd",(char*)"abcd",3)!=0)
    return 29;
  if(strncmp((char*)"abcd",(char*)"abcf",3)!=0)
    return 30;
  if(strncmp((char*)"abcd",(char*)"abca",3)!=0)
    return 31;
  if(strncmp((char*)"abcd",(char*)"abcde",5)!=-1)
    return 32;
  if(strncmp((char*)"abcde",(char*)"abcd",5)!=1)
    return 33;
  
  if(strcmp(strcat((char*)"XYZ",(char*)"xyz"),(char*)"XYZxyz")!=0)
    return 34;
  if(strcmp(strcat((char*)"XXYY",(char*)""),(char*)"XXYY")!=0)
    return 35;

  
  // embedded ROM functions

  ROMstrcmp((char *)"zuio","zuio");
  if(ROM_result_char())
    return 36;
  ROMstrcmp((char*)"abcd","abcd");
  if(ROM_result_char())
    return 37;
  ROMstrcmp((char*)"abcd","abcD");
  if(ROM_result_char()!=1)
    return 38;
  ROMstrcmp((char*)"abcD","abcd");
  if(ROM_result_char()!=-1)
    return 39;
  ROMstrcmp((char*)"abcd","abcdef");
  if(ROM_result_char()!=-1)
    return 40;

  ROMstrcpy(s1,"abc");
  if(strcmp(s1,(char *)"abc"))
    return 41;

  ROMstrcat(s1,"def");
  if(strcmp(s1,(char *)"abcdef"))
    return 42;

  ROMstrcat(s1,"\0");
  if(strcmp(s1,(char *)"abcdef"))
    return 43;

  ROMstrcpy(s1,"\0");
  if(s1[0])
    return 44;
  
  // ROM pointer versions

  RPstrcpy(s1,rom_string);
  if(strcmp(s1,(char *)"string"))
    return 45;

  strcpy(s1,(char *)"abcd");
  RPstrcat(s1,rom_string);
  if(strcmp(s1,(char *)"abcdstring"))
    return 46;
  
  // ROM accessor versions

  RFstrcpy(s1,rxs_string);
  if(strcmp(s1,(char *)"axs"))
    return 47;

  RPstrcpy(s1,rom_string);
  RFstrcat(s1,rxs_string);
  if(strcmp(s1,(char *)"stringaxs"))
    return 48;

  return 0;
}
