#include "test_bcd.h"
#include "lib/bcd.h"


char test_bcd()
{
  uint8_t i=0;  
  uint8_t j;

  for(i=0; i<100u; i++) {
    j = toBCD(i);
    if(j != (i/10u)*16u + (i%10u) )
      return 1;
    if(fromBCD(toBCD(i)) != i )
      return 2;
  } 
  
  return 0;
}
