/*

  calculate_start_values.c
  
  gcc calculate_start_values.c && ./a.out
  
  Calculate values of the look up table for fast_sqrt.c

  Copyright (c) 2021, olikraus@gmail.com

  Redistribution and use in source and binary forms, with or without modification, are 
  permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this list of 
  conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice, this list of 
  conditions and the following disclaimer in the documentation and/or other materials 
  provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
  POSSIBILITY OF SUCH DAMAGE.


*/
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>




#define INPUT_COMMA 15
#define INPUT_ONE (1UL<<INPUT_COMMA)
#define INTERNAL_COMMA 14
#define INTERNAL_ONE (1UL<<INTERNAL_COMMA)

#define SQRT_START_BITS 4
#define SQRT_START_CNT (1<<SQRT_START_BITS)


#ifdef __GNUC__
#define USE_BUILDIN_CLZ
#endif

static uint16_t sqrt_start_values[SQRT_START_CNT];


#ifndef USE_BUILDIN_CLZ    
// find the log base 2 of 32-bit v
int get_highest_1_bit_position(uint32_t v)
{
  // source: http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogDeBruijn
  
  static const int MultiplyDeBruijnBitPosition[32] = 
  {
    0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
    8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
  };

  v |= v >> 1; // first round down to one less than a power of 2 
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;

  return MultiplyDeBruijnBitPosition[(uint32_t)(v * 0x07C4ACDDU) >> 27];
}
#endif


int iterations;
int leading_zeros;
int highest_bit_position;
int number_up_shift;
uint16_t result_before_shift;

uint32_t sqrt_for_init(int32_t number)
{
  uint32_t temp;
  uint32_t x;
  uint32_t xx;
  int shift = 0;
  int start_index;

  result_before_shift = 0;
  
#ifndef USE_BUILDIN_CLZ
  highest_bit_position = get_highest_1_bit_position(number);
#else
  highest_bit_position = INPUT_COMMA;
  if ( number > 0 )
    highest_bit_position  = 31-__builtin_clz(number);
#endif
  
  if ( INPUT_COMMA >= highest_bit_position + 2 )
  {
    number_up_shift = INPUT_COMMA - highest_bit_position - 2;         // upshift must be at least 2
    number_up_shift &= 0x0fe;                           // we must be able to deivide by 2 without reminder
    number <<= number_up_shift;                         // upscale the number, for example if this is 6, then...
    number_up_shift /= 2;                                       // scale the result down by 3 (half of 6)
  }

  start_index = number >> (INPUT_COMMA - SQRT_START_BITS);
  
  assert( number < INPUT_ONE );
  assert( start_index < SQRT_START_CNT );
  
  x = (number>>(INPUT_COMMA - INTERNAL_COMMA))/2+1;
  assert(x < INTERNAL_ONE);
  
  /* 
    inverse square root (https://www.jjj.de/fxt/fxtbook.pdf, page 568)
    x := x + x*(1-d*x*x)/2 
    x := x * ( 1 + (1-d*x*x)/2 )
    x := x * ( 1 + 0.5 - d*x*x/2 )
    x := x * ( 1.5 - d*x*x/2 )
  */
  for( iterations = 0; iterations < 50; iterations++ )
  {
    xx = x;
    temp = x;
    temp *= x;
    temp >>= INTERNAL_COMMA;
    
    temp *= number;
    temp >>= INPUT_COMMA+1;
    
    temp = INTERNAL_ONE + (INTERNAL_ONE>>1) - temp;
    x *= temp;
    x >>= INTERNAL_COMMA;
    
    if ( x == xx )
      break;
  }
  
  result_before_shift = x;
  
  return (x*number)>>(INTERNAL_COMMA+number_up_shift);
}

void calculate_sqrt_start_values(void)
{
  uint16_t i, j;
  for( i = 0; i < SQRT_START_CNT ; i++ )
  {
    sqrt_for_init((i<<(INPUT_COMMA-SQRT_START_BITS)) + 0x0ff);
    /* adding INTERNAL_ONE /16 will ensure that sqrt(0x7fff) will be 0x7fff again (otherwise 0x8000 is returned) */ 
    sqrt_start_values[i] = result_before_shift + INTERNAL_ONE /16;
  }
}

void show_sqrt_start_values(void)
{
  uint16_t i;
  printf("static uint16_t sqrt_start_values[%d] = {", SQRT_START_CNT);
  for( i = 0; i < SQRT_START_CNT ; i++ )
  {
    if ( i > 0 ) printf(", ");
    printf("%d", sqrt_start_values[i]);
  }  
  printf("};\n");
}

void main(void)
{
  calculate_sqrt_start_values();
  show_sqrt_start_values();
}