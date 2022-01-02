/*

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

#include <stdint.h>
#include <stdio.h>

#define INPUT_COMMA 15
#define INPUT_ONE (1UL<<INPUT_COMMA)
#define INTERNAL_COMMA 14
#define INTERNAL_ONE (1UL<<INTERNAL_COMMA)

extern uint16_t fast_sqrt(int16_t number);

void test_fast_sqrt(int16_t number)
{
  int16_t r = fast_sqrt(number);
  int16_t rr = ((int32_t)r*(int32_t)r) >> INPUT_COMMA;
  int16_t rr_diff = rr - number;
  
  printf("%d: root=%d root^2=%d diff=%d\n", number, r, rr, rr_diff);
}

void main(void)
{
  int16_t i;
  for( i = 0; i < INPUT_ONE; i++ )
    test_fast_sqrt(i);
}

