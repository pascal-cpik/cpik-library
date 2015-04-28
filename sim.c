// **************************************************************************************
// **                                                                                  **
// **  Test suite for assembler libraries                                              **
// **                                                                                  **
// **  The individual tests are invoked by setting the appropriate defines below       **
// **  I run thus test suite using gpsim and watch the results string in memory        **
// **  view, which will contain "***** OK *****" if the suite passes, or               **
// **  "!!! SUITE: err !!!" if it fails (err being the return code of the test         **
// **  function, e.g. "!!! BCD: 002 !!!").                                             **
// **                                                                                  **
// **  Pascal A. Niklaus, 28.04.2015                                                   **
// **                                                                                  **
// **************************************************************************************
// **                                                                                  **
// ** TEST SUITE SWITCHES                                                              **

#define TEST_STRING  1
#define TEST_MEMMOVE 1
#define TEST_SORT    1
#define TEST_BCD     1

// ** END OF TEST SUITE SWITCHES                                                       **
// **                                                                                  **
// **************************************************************************************


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

char result[] = "----- RUNNING -----     ";

#include "sim.h"
#include "test_sort.h"
#include "test_memcpymove.h"
#include "test_strcmp.h"
#include "test_bcd.h"

#include "lib/strcmp.h"

void genresult(char *txt, uint8_t n)
{
    uint8_t div;
    uint8_t digit;
    char *p;
    strcpy(result,txt);
    p = result;
    while(*p) 
      p++;
    for(div = 100u; div>0u; div /= 10u) {
      digit = n/div;
      *p++ = '0'+digit;
      n -= digit * div;
    }
    *p=0;
    strcat(result,(char *)" !!!");
}

int8_t main()
{
  uint8_t r;
#if TEST_BCD
  if(r = test_bcd()) {
    genresult((char *)"!!! BCD: ",r);
    return 0;    
  }
#endif
#if TEST_STRING
  if(r = test_strcmp()) {
    genresult((char *)"!!! STRING: ",r);
    return 0;
  }
#endif 
#if TEST_MEMMOVE
  if(r = test_memcpymove()) {
    genresult((char *)"!!! MEMCPYMV: ",r);
    return 0;
  }  
#endif   
#if TEST_SORT
  if(r = test_sort()) {
    genresult((char *)"!!! SORT: ",r);
    return 0;
  }  
#endif     

  for(r=0u; r<13u; r++)   // generatre string in "cryptic" way so that the 
    result[r] = '*';      // text constant is not visible in RAM (and confounded with the result)
  result[5]=result[8]=' ';
  result[6]='O';
  result[7]='K';

//   strcpy(result,(char *)"***** OK ****");
  return 0 ;
}
