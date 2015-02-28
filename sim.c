

#pragma config IESO=OFF,FCMEN=OFF

#pragma config OSC=HS

#pragma config PWRT=OFF,BOREN=OFF,BORV=3 // SBORDIS

#pragma config WDTPS=4096,WDT=OFF

#pragma config MCLRE=ON, PBADEN=OFF, LPT1OSC=OFF
#pragma config STVREN=ON, LVP=OFF,XINST=OFF, DEBUG=OFF
#pragma config CPD=OFF,CPB=OFF,CP3=OFF,CP2=OFF,CP1=OFF,CP0=OFF
#pragma config WRT0=OFF,WRT1=OFF,WRT2=OFF,WRT3=OFF,WRTC=OFF,WRTB=OFF,WRTD=OFF
#pragma config EBTR0=OFF,EBTR1=OFF,EBTR2=OFF,EBTR3=OFF,EBTRB=OFF


#include <p18f4520.h>
#include <sys/types.h>


#include "lib/memcpymove.h"
#include "lib/strcmp.h"



uint8_t error=0;

char result[] = "----- RUNNING -----";

typedef char (*bsort_cmp)(void *e1, void *e2);

bsort_cmp fff;

void bsort(void *data, size_t length, unsigned char size, bsort_cmp );
void csort(void *data, size_t length, unsigned char size, bsort_cmp );

void assert(uint8_t test)
{
  if(!test) 
    error=1;
}

char cmpu8(uint8_t *p1,uint8_t *p2)
{
  if(*p1<*p2)
    return -1;
  if(*p1>*p2)
    return 1;
  return 0;
}

char cmpu16(uint16_t *p1,uint16_t *p2)
{
  if(*p1<*p2)
    return -1;
  if(*p1>*p2)
    return 1;
  return 0;
}

uint16_t x[200] = { 392,952,237,476,645,657,437,966,812,724,558,472,97,697,457,182,618,320,972,778,88,609,201,896,530,220,283,322,362,812,140,430,326,145,548,765,102,127,939,745,443,201,723,668,381,877,599,517,957,206,474,561,582,817,751,149,518,873,905,581,16,604,922,764,132,886,802,139,82,836,37,603,416,153,110,950,990,687,268,938,239,716,550,489,229,771,963,181,783,45,975,359,176,809,83,846,329,18,162,362,696,352,871,544,938,473,564,276,293,588,581,566,959,582,701,782,859,232,962,921,88,205,537,665,771,660,760,236,191,311,48,828,495,678,971,275,978,315,621,740,752,592,831,150,188,275,963,34,143,838,299,832,437,45,52,152,305,663,190,559,354,366,736,542,787,108,938,86,252,519,607,485,914,926,79,546,23,549,782,469,754,170,666,186,127,113,145,918,668,523,943,842,66,273,228,972,169,946,594,132
  };

struct str {
    int16_t v;
    char c;
};

struct str xs[10] = { {5,'l'},
             {-7,'e'},
             {156,'!'},
             {321,'!'},
             {-765,'H'},
             {88,'o'},
             {33,'l'},
             {123,' '} };
             
char cmpstr(struct str *s1, struct str *s2) {
    if(s1->v < s2->v)
      return -1;
    if(s1->v == s2->v)
      return 0;
    return 1;
}

uint8_t i;
uint8_t n=200;

int8_t main()
{
//   uint8_t u8;
//   uint16_t u16,r,offset;  
//   r=u8*u16+offset;


  csort(x,n,2,(bsort_cmp)cmpu16);
  for(i=0; i<n-2; i++) {
    if(x[i]>x[i+1]) {
      error=1; 
      break;
    }
  }
  if(error)
    strcpy(result,(char*)"*** ERROR ***");
  else
    strcpy(result,(char*)"***** OK ****");
//   csort(xs,8,sizeof(struct str),(bsort_cmp)cmpstr); 
#if 0  
  
  strcpy(s1,(char*)"0123456789");
  memmove(s1,s1+1,4);
  assert(0==strcmp(s1,(char *)"1234456789"));
  while(error);
  
  strcpy(s1,(char*)"0123456789");
  memmove(s1+1,s1,4);
  assert(0==strcmp(s1,(char *)"0012356789"));
  while(error);
  
  assert(strlen((char *)"abcd")==4);
  while(error);
  assert(strlen((char *)"")==0);
  while(error);
  assert(strcpy(s1,(char*)"abcdEFGH")==s1);
  while(error);
  assert(strcmp(s1,(char*)"abcdEFGH")==0);
  while(error);
  assert(strcmp((char *)"zuio",(char *)"zuio")==0);
  while(error);
  assert(strcmp((char*)"abcd",(char*)"abcd")==0);
  while(error);
  assert(strcmp((char*)"abcd",(char*)"abcD")==1);
  while(error);
  assert(strcmp((char*)"abcD",(char*)"abcd")==-1);
  while(error);
  assert(strcmp((char*)"abcd",(char*)"abcdef")==-1);
  while(error);
  assert(strcasecmp((char*)"aBCd",(char*)"abcd")==0);
  while(error); 
  assert(strcasecmp((char*)"aBCd",(char*)"abcF")==-1);
  while(error);
  assert(strcasecmp((char*)"aBCd",(char*)"abca")==1);
  while(error);
  
  assert(strncasecmp((char*)"aBCd",(char*)"abcd",4)==0);
  while(error); 
  assert(strncasecmp((char*)"aBCd",(char*)"abcF",4)==-1);
  while(error);
  assert(strncasecmp((char*)"aBCd",(char*)"abca",4)==1);

  assert(strncasecmp((char*)"aBCd",(char*)"abcd",3)==0);
  while(error); 
  assert(strncasecmp((char*)"aBCd",(char*)"abcF",3)==0);
  while(error);
  assert(strncasecmp((char*)"aBCd",(char*)"abca",3)==0);

  assert(strncmp((char*)"abcd",(char*)"abcd",4)==0);
  while(error); 
  assert(strncmp((char*)"abcd",(char*)"abcf",4)==-1);
  while(error);
  assert(strncmp((char*)"abcd",(char*)"abca",4)==1);

  assert(strncmp((char*)"abcd",(char*)"abcd",3)==0);
  while(error); 
  assert(strncmp((char*)"abcd",(char*)"abcf",3)==0);
  while(error);
  assert(strncmp((char*)"abcd",(char*)"abca",3)==0);
  
  assert(strcmp(strcat((char*)"XYZ",(char*)"xyz"),(char*)"XYZxyz")==0);
  while(error);
  assert(strcmp(strcat((char*)"XXYY",(char*)""),(char*)"XXYY")==0);
  while(error);
  //                0123456BCDEF
  strcpy(s1,(char*)"-----ABCDEFGHIJKLMNOP---------");
  xmemshift(s1,6,1,5,1); // offset=6,shift=+1, len=5, size=1
  assert(strcmp(s1,(char *)"-----ABBCDEFHIJKLMNOP---------")==0);
  while(error);
  //                      DDEEFFGG
  strcpy(s1,(char*)"----AABBCCDDEEFFGGHHIIJJ---------");
  xmemshift(s1,5,-2,4,2); // offset=5,shift=-2, len=4, size=2
  assert(strcmp(s1,(char *)"----AADDEEFFGGFFGGHHIIJJ---------")==0);
  while(error);
  
  if(error) 
    strcpy(result,(char*)"*** ERROR ***");
  else
    strcpy(result,(char*)"*** PASSED ***");
#endif   
  return 0 ;
  
}
