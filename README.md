# fast_sqrt
Fast Square Root Calculation for 16 Bit Fix-Point values from 0 to 1 (1.15) 


## Problem Description
 * Calculate square root for a value between 0 and 1 
 * Intended for embeddes systems without FPU
 * Pure integer calculation
 * 16 bit signed integer as input and output data type
 * Integer format is 1.15 fix point for input and output

## Examples values for 1.15 fix point

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
  
 
