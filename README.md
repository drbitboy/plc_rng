# Random Number Generator (RNG) programs for Rockwell-Automation PLCs

This is an attempt, with much help from my brother and the plctalk.net website, to implement random number generator programs in RA/AB PLCs.

The code uses the [Linear Congruential Generators](https://en.wikipedia.org/wiki/Linear_congruential_generator) (LCG) for uniform-distribution RNGs, and the [Box-Muller Transform](https://en.wikipedia.org/wiki/Box%E2%80%93Muller_transform) for gaussian-distribution RNGs.

The plc_programs/ sub-directory contains PLC programs implementing the algorithms.

The verify/ sub-directory contains programs, written in C, Python, or Fortran, to verify that the various algorithms used can be expected to produce, or have produced, correct results.
