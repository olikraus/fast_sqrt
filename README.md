# fast_sqrt
Fast Square Root Calculation for 16 Bit Fix-Point values from 0 to 1 (1.15) 


## Problem Description
 * Calculate square root for a value between 0 and 1, return 0 for negative values
 * Intended for embeddes systems without FPU
 * Pure integer calculation
 * 16 bit signed integer as input and output data type
 * Integer format is 1.15 fix point for input and output
 * No code dependencies for simple integration 

## Example Values for 1.15 Fix Point

  | 1.15 value hex | 1.15 value dec | Interpretation |
  |---|---|---|
  | 0x8000 | 32768 | -1 |
  | 0x8001 | 32769 | -0.999969483 |
  | 0x8401 | 33793 | -0.968719483 |
  | 0xffff | 65535 | -0.000030518 |
  | 0x0000 | 0 | 0 |
  | 0x0001 | 1 |  0.000030517 |
  | 0x2803 | 10243 | 0.312591552 |
  | 0x7fff | 32767 | 0.999969482 |

## Usage

Download file https://github.com/olikraus/fast_sqrt/blob/main/fast_sqrt.c and add this code to your project.

Add the prototype `intt16_t fast_sqrt(int16_t number)` to your project and call "fast_sqrt" to calculate the square root of a 1.15 16 bit value.

## Implementation Details

 * Instead of calculation of `sqrt(n)` directly, the code will do an iterative approximation of the value `1/sqrt(n)`. `sqrt(n)` is calculated by `n/sqrt(n)` (see end of the code). The approximation `x=1/sqrt(n)` is done by repeated calculation of `x := x + x*(1-n*x*x)/2`. 

## References

 * Mathematical Background for the square root calculation: https://www.jjj.de/fxt/#fxtbook
 * Q15 SQRT procedure from ARM CMSIS DSP library: https://github.com/ARM-software/CMSIS_5/blob/develop/CMSIS/DSP/Source/FastMathFunctions/arm_sqrt_q15.c 
