/*

  Copyright (c) 2021, olikraus@gmail.com
  
  Test code for fast_sqrt.c
  
  gcc test_fast_sqrt.c fast_sqrt.c && ./a.out

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

#include <stdint.h>
#include <stdio.h>

#define INPUT_COMMA 15
#define INPUT_ONE (1UL<<INPUT_COMMA)
#define INTERNAL_COMMA 14
#define INTERNAL_ONE (1UL<<INTERNAL_COMMA)

int16_t fast_sqrt(int16_t number);

uint16_t eq2_cnt = 0;
uint16_t ge3_cnt = 0;


void test_fast_sqrt(int16_t number)
{
  int16_t r = fast_sqrt(number);
  int16_t rr = ((int32_t)r*(int32_t)r) >> INPUT_COMMA;
  int16_t rr_diff = number-rr;
  
  
  //int16_t rr_half_diff = rr_diff > 1 || rr_diff < -1  ? rr_diff>>1 : 0;
  //int16_t rr_half_diff = 0;
  //int16_t f_r = r + rr_half_diff;
  //int16_t f_rr = ((int32_t)f_r*(int32_t)f_r) >> INPUT_COMMA;
  //int16_t f_rr_diff = number - f_rr;

  if ( rr_diff == -2 ) eq2_cnt++;
  if ( rr_diff == 2 ) eq2_cnt++;
  
  if ( rr_diff <= -3 ) ge3_cnt++;
  if ( rr_diff >= 3 ) ge3_cnt++;
  
  //if ( f_rr_diff >= 2 || f_rr_diff <= -2)
  //printf("%d: root=%d root^2=%d diff=%d - root=%d root^2=%d diff=%d \n", number, r, rr, rr_diff, f_r, f_rr, f_rr_diff);
  printf("%d: root=%d root^2=%d diff=%d \n", number, r, rr, rr_diff);
}

void main(void)
{
  int16_t i;
  for( i = 0; i < INPUT_ONE; i++ )
    test_fast_sqrt(i);
  printf("no of deviations equal to 2: %u\n", eq2_cnt);
  printf("no of deviations greater equal to 3: %u\n", ge3_cnt);
}

