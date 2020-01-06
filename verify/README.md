## Sub-directory verify/

Programs to verify that the various algorithms used can be expected to produce, or have produced, correct results.

## Usage

    make

### 01.c, 01.h, stdlib_random_r.c

Verify that negative 32-bit seeds produce functionally identical results to positive seeds in the random_r TYPE_0 Linear Congruential Generator (LCG) of STDLIB's random_r as a Random Number Generator (RNG)


### 02.c

Verify that 15-bit LCG (a=20077,b=12345) pair does not repeat in less than 32,768 steps
Verify that 31-bit LCG (a=1103515245,b=12345) pair does not repeat in less than 2,147,483,648 steps


### 03.f

Emulate suspected anomalous behavior of [RSLogix Emualte500] when multiplying two 16-bit INTEGERs with overflow


### sin_check.f

Calculate 32-bit polynomial-based approximations for sine, and compare those results to that of the intrinsic SIN function


### ln_check.f

Calculate 32-bit polynomial-based approximations for natural logarithm, and compare those results to that of the intrinsic LOG function
