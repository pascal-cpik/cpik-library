

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
#include "lib/sort.h"
#include "lib/bcd.h"


uint8_t error=0;

char result[] = "----- RUNNING -----";
char s1[50];

typedef char (*bsort_cmp)(void *e1, void *e2);

bsort_cmp fff;


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
   
uint16_t x[400] = {
8742,8180,7067,3567,6451,8731,2530,1619,5010,795,8098,3732,2901,462,5166,8745,7661,2280,7159,6042,2840,2500,898,6719,1690,8423,2982,4448,6893,8405,1953,8872,5704,175,5963,7902,4888,6133,3471,1975,1265,3676,940,9326,1325,7191,7770,1212,9821,1477,7027,8665,5928,7992,1021,3203,8819,8079,9484,7867,7191,9665,855,5730,3213,1494,6102,863,8611,4341,5574,1289,6962,2166,8324,4654,2993,7460,2611,2951,6553,49,8470,3904,2184,8006,9337,637,2961,9484,5173,9953,3009,3467,8792,6518,7048,3644,7887,1265,181,9997,9089,6628,2120,1558,5704,5354,4420,3096,3580,1842,3971,5662,8611,4032,2853,9187,7030,1104,2167,1564,1419,9017,7636,9782,369,5213,3161,8763,7049,743,9259,5478,8452,9931,8720,6173,7929,1821,4729,304,9418,8532,3644,9575,4525,7673,3324,4530,3489,2770,8859,4768,2756,7004,4691,3715,6793,3623,5208,1894,6130,4422,8074,4218,621,8747,9059,2251,4075,2809,6623,8575,1996,9509,5431,5986,5536,4501,4022,5432,7517,8345,2868,453,6277,5254,9479,5192,3080,2397,3871,802,4348,2740,3265,7477,3932,2753,5659,4078,8997,8062,2051,2785,3720,5200,2604,2880,8039,8657,6155,2071,1848,3160,9136,5896,1,557,5594,6080,7394,1736,5025,9057,9873,6766,7571,1535,8516,8728,4542,7580,2845,71,9006,3362,3975,1845,5369,3628,7953,4004,17,9684,3853,9396,5009,2822,7706,4060,5220,6698,1595,7634,5857,6742,9379,242,745,763,497,8936,2125,2814,3848,5144,9099,9820,4992,2017,1740,6555,5614,4355,8213,414,8255,669,460,7230,8841,6698,8965,6238,7645,4364,9704,4904,2603,5687,8821,6944,4026,1628,9887,2279,1955,8007,7095,3881,1700,1180,2843,7450,2780,557,7988,6918,2041,3747,9440,5092,9716,7681,9822,8674,8786,2751,4404,3357,4581,5433,284,9562,9049,7942,6752,1151,1385,5605,1812,1864,6227,6110,3325,8729,2188,55,2254,4006,9878,6397,3939,8395,2509,5849,3056,4523,7895,5475,9508,4137,2497,9994,24,8198,7391,7519,4215,9476,4447,8298,822,5906,9395,5515,4272,2705,4026,7951,8437,9261,2551,8404,9674,6831,1701,6899,4821,9175,9576,3786,8751,9800,3971,825,1745,3640,8410,2895,5440,3548,6795,2536,4418,7747,2325,5088
};

uint8_t i;
uint8_t n=200;
uint8_t j;

int8_t main()
{
#if 0
  i=0;
  for(i=0; i<100u; i++) {
    j = toBCD(i);
    assert(j == (i/10u)*16u + (i%10u) );
    assert(fromBCD(toBCD(i)) == i );        
  } 
  
  if(error)
    strcpy(result,(char*)"*** ERROR ***");
  else
    strcpy(result,(char*)"***** OK ****");
#endif
#if 1
   ssort(x,n,sizeof(uint16_t),(bsort_cmp)cmpu16); 
   
   for(i=1;i<n; i++)
     if(x[i-1] > x[i])
       error=1;
  if(error)
    strcpy(result,(char*)"*** ERROR ***");
  else
    strcpy(result,(char*)"*** SORTED **");
#endif 
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
